#include "nmea_parser.hpp"
#include "../util/util.hpp"
#include "../framework.hpp"
//#include "gps_module.hpp"

NmeaParser::NmeaParser(){
    m_last_imu_acc_frame = ImuFrame_ptr(new ImuFrame());
    m_last_imu_gyro_frame = ImuFrame_ptr(new ImuFrame());
    m_last_imu_mag_frame = ImuFrame_ptr(new ImuFrame());
    m_last_imu_angle_frame = ImuFrame_ptr(new ImuFrame());
    m_last_gga_frame = GGAFrame_ptr(new GGAFrame());
    m_last_rmc_frame = RMCFrame_ptr(new RMCFrame());
    m_last_can_frame = CanFrame_ptr(new CanFrame());
}
void NmeaParser::parseBuffer(){
    if(m_bufferIndLast > 1){
        if(m_buffer[0] == 'V'){
            parseVersion();
        } else if(m_buffer[0] == 'G'){
            if(m_buffer[1] == 'N' || m_buffer[1] == 'P'){
                if(m_buffer[2] == 'G' && m_buffer[3] == 'G' && m_buffer[4] == 'A'){
                    if(checkBuffer()){
                        return parseGGA();
                    }
                } else if(m_buffer[2] == 'R' && m_buffer[3] == 'M' && m_buffer[4] == 'C'){
                    if(checkBuffer()){
                        return parseRMC();
                    }
                } else if(m_buffer[2] == 'V' && m_buffer[3] == 'T' && m_buffer[4] == 'G'){
                    return parseVTG();
                }
            }
        } else if(m_buffer[0] == 'P' && m_buffer[1] == 'A' && m_buffer[2] == 'T' && m_buffer[2] == 'T'){
            return parseATT();
        } else if(m_buffer[0] == 'C' && m_buffer[1] == 'S' && m_buffer[2] == 'Q'){
            std::string s = "";
            for(size_t i =0; i < m_bufferIndLast; ++i){
                s += m_buffer[i];
            }
            m_last_csq = s;
        } else if(m_buffer[0] == 'I' && m_buffer[1] == 'M' && m_buffer[2] == 'U' && m_buffer[3] == '_'){
            if( m_buffer[4] == 'A' && m_buffer[5] == 'C'  && m_buffer[6] == 'C' ){
                return parseImuAcc();
            }
            if( m_buffer[4] == 'G' && m_buffer[5] == 'Y'  && m_buffer[6] == 'R'  && m_buffer[7] == 'O' ){
                return parseImuGyro();
            }
            if( m_buffer[4] == 'A' && m_buffer[5] == 'N'  && m_buffer[6] == 'G'  && m_buffer[7] == 'L' ){
                return parseImuAngle();
            }
            if( m_buffer[4] == 'M' && m_buffer[5] == 'A'  && m_buffer[6] == 'G' ){
                return parseImuMag();
            }
        } else if(m_buffer[0] == 'J' && m_buffer[1] == 'D' && m_buffer[2] == '_'){
            if( m_buffer[3] == 'P' && m_buffer[4] == 'O'  && m_buffer[5] == 'S' ){
                return parseJDPos();
            }
            if( m_buffer[3] == 'I' && m_buffer[4] == 'M'  && m_buffer[5] == 'U' ){
                return parseJDImu();
            }
            if( m_buffer[3] == 'C' && m_buffer[4] == 'A'  && m_buffer[5] == 'P' ){
                return parseJDCapVit();
            }
        } else if(m_buffer[0] == 'L' && m_buffer[1] == 'E' && m_buffer[2] == 'M' && m_buffer[3] == 'C' && m_buffer[4] == 'A' ){
            if(m_buffer[5] == '1' ){
                return parseLemca1();
            }
            if(m_buffer[5] == '2' ){
                return parseLemca2();
            }
            if(m_buffer[5] == '3' ){
                return parseLemca3();
            }
        } else if(m_buffer[0] == 'C' && m_buffer[1] == 'F' && m_buffer[2] == 'G' && m_buffer[3] == '_'){
            if(m_buffer[4] == 'E' && m_buffer[5] == 'K' && m_buffer[6] == 'F'){
                return parseCfgEkf();
            }
        } else if(m_buffer[0] == 'C' && m_buffer[1] == 'A' && m_buffer[2] == 'N'){
            return parseCan();
        }  else {
            error();
        }
    }
}

bool NmeaParser::checkBuffer(){
    int checksum = 0;
    for(size_t i =0; i < m_bufferIndLast; ++i){
        const char c = m_buffer[i];
        if (c == '*'){
            if(i < m_bufferIndLast+2){
                char c1 = m_buffer[i+1];
                char c2 = m_buffer[i+2];
                
                int i = getHexIntWithChar(c1)*16+getHexIntWithChar(c2);
                if(i == checksum){
                    return true;
                }
            }
            break;
        }
        checksum = checksum ^ c;
    }
    m_error_read++;
    return false;
}


//GNRMC,124450.80,A,4925.15859,N,00400.48455,E,0.006,,070620,,,A*63
void NmeaParser::parseRMC(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    m_last_rmc_str = s;
    
    RMCFrame_ptr rmc_frame = RMCFrame_ptr(new RMCFrame());
    readUntilCommat();
    rmc_frame->m_time = readDouble();
    char c = readNextCharAndCommat();
    rmc_frame->m_latitude = readDeg();
    char c1 = readNextCharAndCommat();
    rmc_frame->m_longitude = readDeg();
    char c2 = readNextCharAndCommat();
    rmc_frame->m_vitesse_noeud = readDouble();
    rmc_frame->m_vitesse_kmh = rmc_frame->m_vitesse_noeud * 1.852;
    rmc_frame->m_cap_deg = readDouble();
    rmc_frame->m_date = readInt();
    rmc_frame->m_cap2_deg = readDouble();
    //INFO(m_lastRMCEvent->m_cap_deg);
    rmc_frame->m_cap_rad = rmc_frame->m_cap_deg/180.0*3.14;
    rmc_frame->m_cap2_rad = rmc_frame->m_cap2_deg/180.0*3.14;
    rmc_frame->m_timeHour = getTimeHour(rmc_frame->m_time);
    
    if(c == 'A' && c1 == 'N' && c2 == 'E'){
        rmc_frame->m_isOk = true;
    } else {
        rmc_frame->m_isOk = false;
    };
    
    m_last_rmc_frame = rmc_frame;
}

//$GNGGA,110138.80,4902.71554,N,00324.04388,E,1,07,1.94,46.6,M,46.3,M,,*71
void NmeaParser::parseGGA(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    m_last_gga_str = s;
    
    GGAFrame_ptr gga_frame = GGAFrame_ptr(new GGAFrame());
    readUntilCommat();
    gga_frame->m_time = readDouble();
    gga_frame->m_latitude = readDeg();
    char c1 = readNextCharAndCommat();
    gga_frame->m_longitude = readDeg();
    char c2 = readNextCharAndCommat();
    gga_frame->m_fix = readInt();
    gga_frame->m_nbrSat = readInt();
    gga_frame->m_hdop = readDouble();
    gga_frame->m_altitude = readDouble();
    
    gga_frame->m_timeHour = getTimeHour(gga_frame->m_time);
    
    if(gga_frame->m_fix > 0 && c1 == 'N' && c2 == 'E'){
        gga_frame->m_isOk = true;
    } else {
        gga_frame->m_isOk = false;
    };
    
    m_last_gga_frame = gga_frame;
}

//GPVTG,054.7,T,034.4,M,005.5,N,010.2,K
void NmeaParser::parseVTG(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    m_last_vtg_str = s;
    
    VTGFrame_ptr vtg_frame = VTGFrame_ptr(new VTGFrame());
    readUntilCommat();
    vtg_frame->m_cap_mag_deg = readDouble();
    char c1 = readNextCharAndCommat();
    vtg_frame->m_cap_real_deg = readDouble();
    char c2 = readNextCharAndCommat();
    vtg_frame->m_vitesse_noeud = readDouble();
    char c3 = readNextCharAndCommat();
    vtg_frame->m_vitesse_kmh = readDouble();
    char c4 = readNextCharAndCommat();
    
    if(c1 == 'T' && c2 == 'M' && c3 == 'N' && c4 == 'K'){
        vtg_frame->m_isOk = true;
    } else {
        vtg_frame->m_isOk = false;
    };
    
    //f.m_position_module.onVTGFrame(vtg_frame);
    //f.onGGAFrame(gga_frame);
}

//$PATT,345.9640,0.0390,-0.9052,..
// head  , pitch,  roll
void NmeaParser::parseATT(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    m_last_att_str = s;
    
    ATTFrame_ptr att_frame = ATTFrame_ptr(new ATTFrame());
    readUntilCommat();
    att_frame->m_head = -readDouble();
    att_frame->m_pitch = readDouble();
    att_frame->m_roll = readDouble();
    
    //f.m_position_module.onATTFrame(att_frame);
}

void NmeaParser::parseImuAcc(){
    ImuFrame_ptr imu_frame = ImuFrame_ptr(new ImuFrame());
    readUntilCommat();
    imu_frame->m_ax = readNegDouble();
    imu_frame->m_ay = readNegDouble();
    imu_frame->m_az = readNegDouble();
    
    m_last_imu_acc_frame = imu_frame;
}

void NmeaParser::parseImuGyro(){
    ImuFrame_ptr imu_frame = ImuFrame_ptr(new ImuFrame());
    readUntilCommat();
    imu_frame->m_ax = readNegDouble();
    imu_frame->m_ay = readNegDouble();
    imu_frame->m_az = readNegDouble();
    
    m_last_imu_gyro_frame = imu_frame;
}

void NmeaParser::parseImuAngle(){
    ImuFrame_ptr imu_frame = ImuFrame_ptr(new ImuFrame());
    readUntilCommat();
    imu_frame->m_ax = readNegDouble();
    imu_frame->m_ay = readNegDouble();
    imu_frame->m_az = readNegDouble();
    
    m_last_imu_angle_frame = imu_frame;
}

void NmeaParser::parseImuMag(){
    ImuFrame_ptr imu_frame = ImuFrame_ptr(new ImuFrame());
    readUntilCommat();
    imu_frame->m_ax = readNegDouble();
    imu_frame->m_ay = readNegDouble();
    imu_frame->m_az = readNegDouble();
    
    m_last_imu_mag_frame = imu_frame;
}



void NmeaParser::parseJDCapVit(){
    readUntilCommat();
    m_last_jd_cap_vit.m_cap_deg = readNegDouble();
    m_last_jd_cap_vit.m_v_km_h = readNegDouble();
}
void NmeaParser::parseJDPos(){
    readUntilCommat();
    m_last_jd_pos.m_lat = readNegDouble();
    m_last_jd_pos.m_lon = readNegDouble();
}
void NmeaParser::parseJDImu(){
    readUntilCommat();
    m_last_jd_imu.m_roll = readNegDouble();
    m_last_jd_imu.m_yaw_acc = readNegDouble();
}

void NmeaParser::parseLemca1(){
    readUntilCommat();
    m_lemca_debug_1.m_value1 = readNegDouble();
    m_lemca_debug_1.m_value2 = readNegDouble();
    m_lemca_debug_1.m_value3 = readNegDouble();
}

void NmeaParser::parseLemca2(){
    readUntilCommat();
    m_lemca_debug_2.m_value1 = readNegDouble();
    m_lemca_debug_2.m_value2 = readNegDouble();
    m_lemca_debug_2.m_value3 = readNegDouble();
}

void NmeaParser::parseLemca3(){
    readUntilCommat();
    m_lemca_debug_3.m_value1 = readNegDouble();
    m_lemca_debug_3.m_value2 = readNegDouble();
    m_lemca_debug_3.m_value3 = readNegDouble();
}

void NmeaParser::parseVersion(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    m_version = s;
}

void NmeaParser::parseCfgEkf(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    m_last_cfg_ekf = s;
    
    readUntilCommat();
    m_cfg_ekf.m_lissage_ekf_xy = readDouble();
    m_cfg_ekf.m_lissage_ekf_cap = readDouble();
    m_cfg_ekf.m_lissage_ekf_a_cap = readDouble();
    m_cfg_ekf.m_lissage_ekf_v = readDouble();
    m_cfg_ekf.m_lissage_ekf_a_v = readDouble();
    m_cfg_ekf.m_lissage_ekf_roll = readDouble();
}

void NmeaParser::parseCan(){
    std::string s = "";
    for(size_t i =0; i < m_bufferIndLast; ++i){
        s += m_buffer[i];
    }
    
    readUntilCommat();
    m_last_can_frame->m_can_id = readHexaInt();
    for(int i =0; i< 8; ++i){
        m_last_can_frame->m_data[i] = readHexaInt();
    }
    m_last_can_frame->m_png = readHexaInt();
    m_last_can_frame->m_message = s;
    
    Framework & f = Framework::Instance();
    f.onCanMessage(m_last_can_frame);
    
    
}

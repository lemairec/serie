#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "../util/parser.hpp"
#include <cmath>

struct GpsPoint {
    double m_altitude;
    
    double m_latitude = 0.0;
    double m_longitude = 0.0;
    
    double m_x = 0.0;
    double m_y = 0.0;
    
    double m_time = 0.0;
    double m_timeHour;
    
    bool m_isOk = false;
    
    double distanceCarre(GpsPoint & p2){
        return (p2.m_x - m_x)*(p2.m_x - m_x) + (p2.m_y - m_y)*(p2.m_y - m_y);
    }
    
    double distance(GpsPoint & p2){
        return std::sqrt((p2.m_x - m_x)*(p2.m_x - m_x) + (p2.m_y - m_y)*(p2.m_y - m_y));
    }
    
    double distanceCarre(double x, double y){
        return (x - m_x)*(x - m_x) + (y - m_y)*(y - m_y);
    }
};

struct GpsPointCap : public GpsPoint{
    double m_cap_deg;
    double m_vitesse_m_s;
};

struct GGAFrame {
    double m_time = 0.0;
    double m_timeHour;
    
    double m_altitude;
    double m_latitude;
    double m_longitude;
    
    int m_fix;
    int m_nbrSat;
    double m_hdop;

    bool m_isOk = false;
    
    bool isOk(){
        return m_fix > 0;
    }
};

struct ATTFrame {
    double m_head;
    double m_roll;
    double m_pitch;

    bool isOk(){
        return m_head != 0;
    }
};

struct RMCFrame {
    double m_latitude;
    double m_longitude;
    
    double m_time = 0.0;
    double m_timeHour;
    
    double m_vitesse_noeud;
    double m_cap_deg;
    double m_cap2_deg;
    int m_date;
    
    double m_vitesse_kmh;
    double m_cap_rad;
    double m_cap2_rad;
    
    bool m_isOk = false;
};

struct VTGFrame {
    double m_cap_real_deg;
    double m_cap_mag_deg;
    
    double m_vitesse_noeud;
    double m_vitesse_kmh;
    
    bool m_isOk = false;
};

typedef std::shared_ptr<GGAFrame> GGAFrame_ptr;
typedef std::shared_ptr<RMCFrame> RMCFrame_ptr;
typedef std::shared_ptr<GpsPoint> GpsPoint_ptr;
typedef std::shared_ptr<GpsPointCap> GpsPointCap_ptr;
typedef std::shared_ptr<VTGFrame> VTGFrame_ptr;
typedef std::shared_ptr<ATTFrame> ATTFrame_ptr;

struct ImuFrame {
    double m_ax;
    double m_ay;
    double m_az;
};

typedef std::shared_ptr<ImuFrame> ImuFrame_ptr;

struct JDCapVit {
    double m_cap_deg;
    double m_v_km_h;
};

struct JDPos {
    double m_lat;
    double m_lon;
};

struct JDImu {
    double m_roll;
    double m_pitch;
    double m_yaw_acc;
};

struct LemcaDebug {
    double m_value1;
    double m_value2;
    double m_value3;
};

struct CfgEkf {
    double m_lissage_ekf_xy;
    double m_lissage_ekf_cap;
    double m_lissage_ekf_a_cap;
    double m_lissage_ekf_v;
    double m_lissage_ekf_a_v;
    double m_lissage_ekf_roll;
};

struct CanFrame {
    int m_can_id;
    int m_png;
    
    short m_data[8];
    std::string m_message;
};
typedef std::shared_ptr<CanFrame> CanFrame_ptr;


class NmeaParser : public Parser {
public:
    std::string m_last_gga_str = "";
    std::string m_last_rmc_str = "";
    std::string m_last_vtg_str = "";
    std::string m_last_att_str = "";
    
    std::string m_last_csq;
    RMCFrame_ptr m_last_rmc_frame;
    GGAFrame_ptr m_last_gga_frame;
    
    ImuFrame_ptr m_last_imu_acc_frame;
    ImuFrame_ptr m_last_imu_gyro_frame;
    ImuFrame_ptr m_last_imu_angle_frame;
    ImuFrame_ptr m_last_imu_mag_frame;
    
    JDCapVit m_last_jd_cap_vit;
    JDPos m_last_jd_pos;
    JDImu m_last_jd_imu;
    
    LemcaDebug m_lemca_debug_1;
    LemcaDebug m_lemca_debug_2;
    LemcaDebug m_lemca_debug_3;
    
    CanFrame_ptr m_last_can_frame;
    
    std::string m_version = "";
    
    NmeaParser();
    
    std::string m_last_cfg_ekf = "";
    CfgEkf m_cfg_ekf;
protected:
    int m_error_read = 0;
    void parseBuffer();
    bool checkBuffer();
    
    void parseGGA();
    void parseRMC();
    void parseVTG();
    void parseATT();
    
    void parseImuAcc();
    void parseImuGyro();
    void parseImuAngle();
    void parseImuMag();
    
    void parseJDCapVit();
    void parseJDPos();
    void parseJDImu();
    
    void parseLemca1();
    void parseLemca2();
    void parseLemca3();
    
    void parseVersion();
    void parseCfgEkf();
    
    void parseCan();
};

#endif //GPS_H

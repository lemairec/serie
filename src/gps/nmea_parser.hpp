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


class NmeaParser : public Parser {
public:
    std::string m_last_gga_str = "";
    std::string m_last_rmc_str = "";
    std::string m_last_vtg_str = "";
    std::string m_last_att_str = "";
    
    std::string m_last_csq;
    RMCFrame_ptr m_last_rmc_frame;
    GGAFrame_ptr m_last_gga_frame;
    
    ImuFrame_ptr m_last_imu_gyro_frame;
protected:
    int m_error_read = 0;
    void parseBuffer();
    bool checkBuffer();
    
    void parseGGA();
    void parseRMC();
    void parseVTG();
    void parseATT();
    
    void parseImuGyro();
};

#endif //GPS_H

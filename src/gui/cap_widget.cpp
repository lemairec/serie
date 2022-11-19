#include "cap_widget.hpp"
#include "../framework.hpp"

class EkfModule {
public:
    double m_lissage_gps_ekf_xy = 0.9;
    double m_lissage_gps_ekf_v = 0.9;
    double m_lissage_gps_ekf_cap = 0.95;
    double m_lissage_gps_ekf_s_s = 0.9;
    double m_h = 0;

    double m_old_x;
    double m_old_y;
    double m_old_v;
    double m_old_cap_deg;
    double m_old_a_v;
    double m_old_a_cap;

    double m_new_x;
    double m_new_y;
    double m_new_v;
    double m_new_cap_deg;
    double m_new_a_v;
    double m_new_a_cap;
    double m_new_pitch_y_deg;

    double m_calc_v;
    double m_calc_a_v;
    double m_calc_cap_deg;
    double m_calc2_cap_deg;
    double m_calc_a_cap;

    double m_lat_ref;
    double m_lon_ref;

    void reset(){
        m_old_x = 0;
        m_old_y = 0;
        m_new_x = 0;
        m_new_y = 0;
    }

    void normalizeDeg(double & d){
        if(d < -180){
            d = d + 2*180;
        }
        if(d > 180){
            d = d - 2*180;
        }
        if(d < -180){
            d = d + 2*180;
        }
        if(d > 180){
            d = d - 2*180;
        }
    }

    double m_imu_a_x = 0;
    double m_imu_a_y = 0;
    double m_imu_a_z = 0;

    void onNewImuAcc(double a_x, double a_y, double a_z){
        m_imu_a_x = a_x;
        m_imu_a_y = a_y;
        m_imu_a_z = a_z;
    };

    double m_imu_a_roll_x_deg = 0;
    double m_imu_a_pitch_y_deg = 0;
    double m_imu_a_yaw_z_deg = 0;
    void onNewImuAccAng(double a_roll_x_deg, double a_pitch_y_deg, double a_yaw_z_deg){
        m_imu_a_roll_x_deg = a_roll_x_deg;
        m_imu_a_pitch_y_deg = a_pitch_y_deg;
        m_imu_a_yaw_z_deg = a_yaw_z_deg;
    };

    double m_imu_roll_x_deg = 0;
    double m_imu_pitch_y_deg = 0;
    double m_imu_yaw_z_deg = 0;
    void onNewImuGyro(double roll_x_deg, double pitch_y_deg, double yaw_z_deg){
        m_imu_roll_x_deg = roll_x_deg;
        m_imu_pitch_y_deg = pitch_y_deg;
        m_imu_yaw_z_deg = yaw_z_deg;
    };


    void workRMC(double lat, double lon, double z, double vitesse_kmh, double angle_deg){

        if(abs(lat-m_lat_ref) > 0.1){
            reset();
            m_lat_ref = lat;
            m_lon_ref = lon;
        }

        double a = 6378249.2;
        double latitude_ref = m_lat_ref;
        double longitude_ref = m_lon_ref;
        double acosLat_ref = a * cos(0.01745329251*latitude_ref);

        double lat1 = 0.01745329251*(lat - latitude_ref);
        double lon1 = 0.01745329251*(lon - longitude_ref);
        double x1 = acosLat_ref * lon1;
        double y1 = a * lat1;

        work(x1, y1, z, vitesse_kmh, angle_deg);
    }

    void work(double x, double y, double z, double vitesse_kmh, double angle_deg){
        double d_t = 0.1;
        m_new_x = x;
        m_new_y = y;

        m_new_v = vitesse_kmh*1000/3600;
        if(vitesse_kmh > 0.5){
            m_new_cap_deg = angle_deg;
        }
        m_new_a_cap = -m_imu_a_yaw_z_deg;
        m_new_a_v = m_imu_a_y;
        m_new_pitch_y_deg = m_imu_pitch_y_deg;
        //m_new_z = z;

        if(m_old_x == 0){
            m_old_x = m_new_x;
            m_old_y = m_new_y;
            m_old_v = m_new_v;
            m_old_cap_deg = m_new_cap_deg;
        }

        double cap = m_old_cap_deg/180*M_PI;
        double pitch = m_new_pitch_y_deg/180*M_PI;
        //INFO(sin(pitch)*m_h);

        m_new_x += cos(cap)*sin(pitch)*m_h;
        m_new_y += -sin(cap)*sin(pitch)*m_h;

        m_calc_v = (sqrt((m_old_x-m_new_x)*(m_old_x-m_new_x)+(m_old_y-m_new_y)*(m_old_y-m_new_y)))/d_t;
        m_calc_cap_deg = (atan2(-(m_old_x-m_new_x),-(m_old_y-m_new_y)))*180/M_PI;
        m_calc_a_v = (m_new_v-m_old_v)/d_t;
        m_calc_a_cap = (m_new_cap_deg-m_old_cap_deg)/d_t;

        m_new_cap_deg = angle_deg;

        m_old_x = m_old_x + sin(cap)*m_old_v*d_t;
        m_old_y = m_old_y + cos(cap)*m_old_v*d_t;
        m_old_v = m_old_v + m_old_a_v*d_t;
        m_calc2_cap_deg =  m_old_cap_deg + m_old_a_cap*d_t;
        m_old_cap_deg = m_old_cap_deg + m_old_a_cap*d_t;
        normalizeDeg(m_old_cap_deg);


        m_old_x = m_lissage_gps_ekf_xy*m_old_x+(1.0-m_lissage_gps_ekf_xy)*m_new_x;
        m_old_y = m_lissage_gps_ekf_xy*m_old_y+(1.0-m_lissage_gps_ekf_xy)*m_new_y;

        m_old_v = m_lissage_gps_ekf_v*m_old_v+(1.0-m_lissage_gps_ekf_v)*m_new_v;

        double diff = m_new_cap_deg-m_old_cap_deg;
        normalizeDeg(diff);
        m_old_cap_deg = m_old_cap_deg+(1.0-m_lissage_gps_ekf_cap)*(diff);
        normalizeDeg(m_old_cap_deg);

        m_old_a_v = m_lissage_gps_ekf_s_s*m_old_a_v+(1.0-m_lissage_gps_ekf_s_s)*m_new_a_v;
        m_old_a_cap = m_lissage_gps_ekf_s_s*m_old_a_cap+(1.0-m_lissage_gps_ekf_s_s)*m_new_a_cap;
    }
};

EkfModule m_ekf_module;


CapWidget::CapWidget(){
};

void CapWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
};

int x_cercle;
int y_cercle;
int r_cercle;

int y;
int inter_y;

void CapWidget::drawAngle(double angle, const QString & s, const QColor &color){
    int a = 0.5;
    m_painter->setBrush(color);
    m_painter->setPen(color);
    m_painter->drawPie(x_cercle-r_cercle, y_cercle-r_cercle, 2*r_cercle, 2*r_cercle, 16*(90+angle+a), -2*16*a);
    
    m_painter->drawText(m_width*0.5, y, s);
    m_painter->drawText(m_width*0.6, y, QString::number(angle));
    m_painter->drawText(m_width*0.65, y, "°");
    y+=inter_y;
}

void CapWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8, RAYON_ROUNDED, RAYON_ROUNDED);
    
    Framework & f = Framework::Instance();
    
    double cap_rmc = 0;
    double cap_jd = 0;
    double cap_imu = 0;
    if(f.m_nmea_parser.m_last_rmc_frame){
        cap_rmc = f.m_nmea_parser.m_last_rmc_frame->m_cap_deg;
        auto rmc = f.m_nmea_parser.m_last_rmc_frame;
        
        m_ekf_module.onNewImuGyro(0, 0, f.m_nmea_parser.m_last_imu_angle_frame->m_az);
        m_ekf_module.onNewImuAccAng(0, 0, f.m_nmea_parser.m_last_imu_gyro_frame->m_az);
        m_ekf_module.workRMC(rmc->m_latitude, rmc->m_longitude, 0, rmc->m_vitesse_kmh, rmc->m_cap_deg);
    }
    cap_jd = f.m_nmea_parser.m_last_jd_cap_vit.m_cap_deg;
    if(f.m_nmea_parser.m_last_imu_angle_frame){
        cap_imu = -f.m_nmea_parser.m_last_imu_angle_frame->m_az;
    }
    
    x_cercle = 0.5*m_height;
    y_cercle = 0.5*m_height;
    r_cercle = 0.3*m_height;
    
    y = m_height*0.2;
    inter_y = 0.05*m_height;
    
    m_painter->drawEllipse(x_cercle-r_cercle, y_cercle-r_cercle, 2*r_cercle, 2*r_cercle);
    //drawAngle(cap_jd, "JD", Qt::green);
    drawAngle(cap_rmc, "RMC", Qt::red);
    drawAngle(cap_imu, "IMU", Qt::blue);
    drawAngle(m_ekf_module.m_old_cap_deg, "JD_calc", Qt::green);
    
    
    m_painter->drawText(m_width*0.5, y, "acc imu Z");
    m_painter->drawText(m_width*0.6, y, QString::number(m_ekf_module.m_old_a_cap));
    m_painter->drawText(m_width*0.65, y, "°/s");
    y+=inter_y;
    
    m_painter->drawText(m_width*0.5, y, "acc calc Z");
    m_painter->drawText(m_width*0.6, y, QString::number(m_ekf_module.m_calc_a_cap));
    m_painter->drawText(m_width*0.65, y, "°/s");
    y+=inter_y;
   
    
};
int CapWidget::onMouse(int x, int y){
    return 0;
    
};

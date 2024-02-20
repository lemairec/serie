#include "nmea_widget.hpp"
#include "../../framework.hpp"


NMEAWidget::NMEAWidget(){
};

void NMEAWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_x = 10;
    m_y = 10;
    m_width2 = 0.88*width;
    m_height2 = 1*height-20;
};

void NMEAWidget::draw(){
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_x, m_y, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    Framework & f = Framework::Instance();
    
    int y = m_height*0.2;
    int inter_y = 0.05*m_height;
    int inter = 0.08*m_width;
    
    y = m_height*0.2;
    m_painter->drawText(m_width*0.1, y, "GGA");
    y += inter_y;
    if(f.m_nmea_parser.m_last_gga_frame){
        QString s = "Time : "+QString::number(f.m_nmea_parser.m_last_gga_frame->m_time);
        m_painter->drawText(m_width*0.1, y, s);
        y += inter_y;
        s = "Sat  : "+QString::number(f.m_nmea_parser.m_last_gga_frame->m_nbrSat);
        m_painter->drawText(m_width*0.1, y, s);
    }
    
    y = m_height*0.2;
    QString s = "CSQ : " + QString::fromStdString(f.m_nmea_parser.m_last_csq);
    
    m_painter->drawText(m_width*0.8, y, s);
    
    
    y = m_height*0.2;
    m_painter->drawText(m_width*0.5, y, "RMC");
    
    y += inter_y;
    if(f.m_nmea_parser.m_last_rmc_frame){
        int x = m_width*0.5;
        QString s = QString::number(f.m_nmea_parser.m_last_rmc_frame->m_latitude);
        m_painter->drawText(m_width*0.5, y, s);
        x += inter*2;
        s = QString::number(f.m_nmea_parser.m_last_rmc_frame->m_longitude);
        m_painter->drawText(x, y, s);
        y += inter_y;
        x = m_width*0.5;
        s = "vit : " + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_vitesse_kmh) + " km/h";
        m_painter->drawText(x, y, s);
        x += inter*2;
        s = "cap : " + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_cap_deg) + " °";
        m_painter->drawText(x, y, s);
    }
    
    y = m_height*0.50;
    
    if(f.m_nmea_parser.m_last_imu_gyro_frame){
        int x = 0.06*m_width;
        m_painter->drawText(x, y, "Gyro");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_gyro_frame->m_ax));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_gyro_frame->m_ay));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_gyro_frame->m_az));
        x+= inter;
        m_painter->drawText(x, y, "°/s");
       
    }
    y += inter_y;
    if(f.m_nmea_parser.m_last_imu_acc_frame){
        int x = 0.06*m_width;
        m_painter->drawText(x, y, "Acc");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_acc_frame->m_ax));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_acc_frame->m_ay));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_acc_frame->m_az));
        x+= inter;
        m_painter->drawText(x, y, "m/s^2");
       
    }
    y += inter_y;
    if(f.m_nmea_parser.m_last_imu_angle_frame){
        int x = 0.06*m_width;
        m_painter->drawText(x, y, "Angle");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_angle_frame->m_ax));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_angle_frame->m_ay));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_angle_frame->m_az));
        x+= inter;
        m_painter->drawText(x, y, "°");
       
    }
    y += inter_y;
    if(f.m_nmea_parser.m_last_imu_mag_frame){
        int x = 0.06*m_width;
        m_painter->drawText(x, y, "Mag");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_mag_frame->m_ax));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_mag_frame->m_ay));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_imu_mag_frame->m_az));
        x+= inter;
        
        double angle = atan2(-f.m_nmea_parser.m_last_imu_mag_frame->m_ay, f.m_nmea_parser.m_last_imu_mag_frame->m_ax);
        double angle_deg = angle/3.14*180;
        y += inter_y;
        x = 0.06*m_width;
        x+= inter;
        m_painter->drawText(x, y, QString::number(angle_deg));
        x+= inter;
        m_painter->drawText(x, y, "°");
    }
    
    y = m_height*0.50;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "JD_CAP");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_cap_vit.m_cap_deg));
        x+= inter;
        m_painter->drawText(x, y, "°");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_cap_vit.m_v_km_h));
        x+= inter;
        m_painter->drawText(x, y, "km/h");
       
    }
    
    y += inter_y;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "JD_POS");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_pos.m_lat));
        x+= inter;
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_pos.m_lon));
        
       
    }
    y += inter_y;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "");
        x+= inter;
        m_painter->drawText(x, y, "roll °");
        x+= inter;
        m_painter->drawText(x, y, "pitch °");
        x+= inter;
        m_painter->drawText(x, y, "yaw acc °/s");
        x+= inter;
       
    }
    y += inter_y;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "JD_IMU");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_imu.m_roll));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_imu.m_pitch));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_last_jd_imu.m_yaw_acc));
        x+= inter;
       
    }
    
    y += inter_y;
    y += inter_y;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "LEMCA1");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_1.m_value1));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_1.m_value2));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_1.m_value3));
        x+= inter;
       
    }
    y += inter_y;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "LEMCA2");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_2.m_value1));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_2.m_value2));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_2.m_value3));
        x+= inter;
       
    }
    y += inter_y;
    if(true){
        int x = 0.5*m_width;
        m_painter->drawText(x, y, "LEMCA3");
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_3.m_value1));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_3.m_value2));
        x+= inter;
        m_painter->drawText(x, y, QString::number(f.m_nmea_parser.m_lemca_debug_3.m_value3));
        x+= inter;
       
    }
    
    
    
};
int NMEAWidget::onMouse(int x, int y){
    return 0;
    
};

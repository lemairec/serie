#include "nmea_widget.hpp"
#include "../framework.hpp"


NMEAWidget::NMEAWidget(){
};

void NMEAWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
};

void NMEAWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8, RAYON_ROUNDED, RAYON_ROUNDED);
    
    Framework & f = Framework::Instance();
    
    int y = m_height*0.2;
    int inter_y = 0.05*m_height;
    
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
        QString s = "lat : " + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_latitude);
        m_painter->drawText(m_width*0.5, y, s);
        y += inter_y;
        s = "lon : " + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_longitude);
        m_painter->drawText(m_width*0.5, y, s);
        y += 1.5*inter_y;
        s = "vit : " + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_vitesse_kmh) + " km/h";
        m_painter->drawText(m_width*0.5, y, s);
        y += inter_y;
        s = "cap : " + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_cap_deg) + " °";
        m_painter->drawText(m_width*0.5, y, s);
    }
    
    y = m_height*0.65;
    
    int inter = 0.08*m_width;
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
    
};
int NMEAWidget::onMouse(int x, int y){
    return 0;
    
};

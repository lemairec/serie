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
    
    int y = m_height*0.2;
    m_painter->drawText(m_width*0.1, y, "GGA");
    
    Framework & f = Framework::Instance();
    if(f.m_nmea_parser.m_last_gga_frame){
        y = m_height*0.3;
        QString s = "Sat"+QString::number(f.m_nmea_parser.m_last_gga_frame->m_nbrSat);
        m_painter->drawText(m_width*0.1, y, s);
    }
    
    y = m_height*0.2;
    QString s = "CSQ : " + QString::fromStdString(f.m_nmea_parser.m_last_csq);
    
    m_painter->drawText(m_width*0.8, y, s);
    
    
    y = m_height*0.2;
    m_painter->drawText(m_width*0.5, y, "RMC");
    
    if(f.m_nmea_parser.m_last_rmc_frame){
        y = m_height*0.3;
        QString s = QString::number(f.m_nmea_parser.m_last_rmc_frame->m_latitude) + "," + QString::number(f.m_nmea_parser.m_last_rmc_frame->m_longitude);
        m_painter->drawText(m_width*0.5, y, s);
    }
    
    y = m_height*0.5;
    
    int inter = 0.1*m_width;
    int x = 0.06*m_width;
    if(f.m_nmea_parser.m_last_imu_gyro_frame){
        y = m_height*0.5;
        
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
    if(f.m_nmea_parser.m_last_imu_acc_frame){
        y = m_height*0.6;
        
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
    if(f.m_nmea_parser.m_last_imu_angle_frame){
        y = m_height*0.7;
        
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
    
};
int NMEAWidget::onMouse(int x, int y){
    return 0;
    
};

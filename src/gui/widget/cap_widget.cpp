#include "cap_widget.hpp"
#include "../../framework.hpp"




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
    drawAngle(cap_jd, "JD", Qt::green);
    drawAngle(cap_rmc, "RMC", Qt::red);
    drawAngle(cap_imu, "IMU", Qt::blue);
};
int CapWidget::onMouse(int x, int y){
    return 0;
    
};

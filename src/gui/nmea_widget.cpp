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
    
};
int NMEAWidget::onMouse(int x, int y){
    return 0;
    
};

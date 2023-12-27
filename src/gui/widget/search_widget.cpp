#include "search_widget.hpp"
#include "../../framework.hpp"




SearchWidget::SearchWidget(){
    m_img_plus = loadImage("/gui/plus.png");
    m_img_moins = loadImage("/gui/moins.png");
};

void SearchWidget::setPainter(QPainter * painter){
    BaseWidget::setPainter(painter);
}
void SearchWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_button_close.setResizeStd(m_width*0.75, m_height*0.7, "Close");
    m_button_search.setResizeStd(m_width*0.75, m_height*0.3, "Search");
};

void SearchWidget::draw(){
    Framework & f = Framework::Instance();
    
    
    
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8, RAYON_ROUNDED, RAYON_ROUNDED);
    
    
    int y = m_height*0.2;
    int inter = m_height*0.05;
    
    drawMessagesCan();
    drawButtonLabel2(m_button_search);
    drawButtonLabel2(m_button_close);
};

void SearchWidget::drawMessagesCan(){
    m_painter->setBrush(m_brush_white);
    
    int x = m_width*0.1;
    int w = m_width*0.6;
    int y = m_height*0.15;
    int h = m_height*0.7;
    m_painter->drawRect(x, y, w, h);
    
    int y2 = y-10+h;
    int inter = 16;
    
    Framework & f = Framework::Instance();
    int i = 0;
    for(auto serial : f.m_serial_port.m_serial_searchs){
        SerialSearch * serial_p = serial.second;
        drawText(serial_p->m_data_s, x+10, y2);
        y2+= -inter;
        drawText(serial_p->m_serial_s, x+10, y2);
        y2+= -inter;
        y2+= -inter;
        ++i;
        
    }
    
}



int SearchWidget::onMouse(int x, int y){
    if(m_button_search.isActive(x, y)){
        Framework::Instance().m_serial_port.searchBegin();
    }
    if(m_button_close.isActive(x, y)){
        m_close = true;
    }
    return 0;
    
};

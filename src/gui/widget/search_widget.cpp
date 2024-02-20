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
    
    m_x = 10;
    m_y = 10;
    m_width2 = 0.88*width;
    m_height2 = 1*height-20;
    
    m_button_close.setResizeStd(m_width*0.65, m_height*0.7, "Close");
    m_button_search.setResizeStd(m_width*0.65, m_height*0.3, "Search");
};

void SearchWidget::draw(){
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_x, m_y, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    
    drawMessagesCan();
    drawButtonLabel2(m_button_search);
    drawButtonLabel2(m_button_close);
};

void SearchWidget::drawMessagesCan(){
    m_painter->setBrush(m_brush_white);
    
    int x = 20;
    int w = m_width*0.6;
    int y = x;
    int h = m_height*1.0-2*y;
    m_painter->drawRect(x, y, w, h);
    
    int y2 = y-10+h;
    int inter = 16;
    
    Framework & f = Framework::Instance();
    int i = 0;
    for(auto serial : f.m_serial_port.m_serial_searchs){
        SerialSearch * serial_p = serial.second;
        drawText("-----", x+10, y2);
        y2+= -inter;
        drawText(serial_p->m_data_s, x+10, y2);
        y2+= -inter;
        drawText(serial_p->m_serial_s, x+10, y2);
        y2+= -inter;
        drawText("-----", x+10, y2);
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

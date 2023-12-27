#include "can_widget.hpp"
#include "../../framework.hpp"




CanWidget::CanWidget(){
    m_img_plus = loadImage("/gui/plus.png");
    m_img_moins = loadImage("/gui/moins.png");
};

void CanWidget::setPainter(QPainter * painter){
    BaseWidget::setPainter(painter);
    m_keypad_hexa_widget.setPainter(painter);
}
void CanWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_button_filtre_hexa.setResizeStd(m_width*0.75, m_height*0.7, "Hexa");
    m_keypad_hexa_widget.setSize(width, height);
};

void CanWidget::draw(){
    Framework & f = Framework::Instance();
    
    
    
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8, RAYON_ROUNDED, RAYON_ROUNDED);
    
    
    int y = m_height*0.2;
    int inter = m_height*0.05;
    
    y = m_height*0.2;
    {
        drawQText( "filtre hexa :", m_width*0.75, y);
    }
    y += inter;
    {
        char s[100];
        sprintf(s, "%4.4X", f.m_frame_filter);
        
        QString s2 = QString(s);;
        drawQText(s2, m_width*0.75, y);
    }
    y += inter;
    {
        drawQText( " int :", m_width*0.75, y);
    }
    y += inter;
    {
        QString s = QString::number(f.m_frame_filter);
        drawQText(s, m_width*0.75, y);
    }
    
    drawMessagesCan();
    drawButtonLabel2(m_button_filtre_hexa);
    
    if(m_keypad_hexa_widget.isOpen()){
        m_keypad_hexa_widget.draw();
    }
};

void CanWidget::drawMessagesCan(){
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
    for(auto s : f.m_messages_can){
        if(y2 < y){
            break;
        }
        drawText(s, x+10, y2);
        y2+= -inter;
        ++i;
        
    }
    
}



int CanWidget::onMouse(int x, int y){
    if(m_keypad_hexa_widget.isOpen()){
        if(m_keypad_hexa_widget.onMouse(x, y)){
            Framework & f = Framework::Instance();
            char s[100];
            sprintf(s, "--- new fiter png %4.4X %i", m_keypad_hexa_widget.m_res_int, m_keypad_hexa_widget.m_res_int);
            std::string s2(s);
            
            f.m_messages_can.push_front(s2);
            f.m_frame_filter = m_keypad_hexa_widget.m_res_int;
        };
    } else {
        if(m_button_filtre_hexa.isActive(x, y)){
            m_keypad_hexa_widget.open();
        }
    }
    return 0;
    
};

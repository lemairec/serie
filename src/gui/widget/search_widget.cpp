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
    m_button_search.setResizeStd(m_width*0.25, m_height*0.7, "Search");
};

void SearchWidget::draw(){
    Framework & f = Framework::Instance();
    
    
    
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
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
    drawButtonLabel2(m_button_search);
    drawButtonLabel2(m_button_close);
};

void SearchWidget::drawMessagesCan(){
    m_painter->setBrush(m_brushWhite);
    
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



int SearchWidget::onMouse(int x, int y){
    if(m_button_search.isActive(x, y)){
        //m_keypad_hexa_widget.open();
    }
    if(m_button_close.isActive(x, y)){
        m_close = true;
    }
    return 0;
    
};

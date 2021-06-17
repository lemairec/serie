#include "menu_widget.hpp"


MenuWidget::MenuWidget(){
    m_imgOk = loadImage("/images/ok.png");
    m_imgStop = loadImage("/images/close.png");
    m_imgOutil = loadImage("/images/outil_gris_gros.png");
    m_imgTractor = loadImage("/images/tracteur.png");
    m_imgParam = loadImage("/images/option_gris_gros.png");
    
}

void MenuWidget::setPainter(QPainter *s){
    BaseWidget::setPainter(s);
    m_options_widget.setPainter(s);
    
}

void MenuWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_options_widget.setSize(m_width, m_height);
    
    m_x = m_width*0.0;
    m_lg = m_width*1;
    m_buttonOk.setResize(m_x+m_lg/2, 0.7*m_height, m_gros_gros_button);
    
    m_buttonParam.setResize(m_x+1*m_lg/5, 0.5*m_height, m_gros_gros_button);
    m_buttonStop.setResize(m_x+4*m_lg/5, 0.5*m_height, m_gros_gros_button);
    
    
}


void MenuWidget::draw(){
    if(!m_options_widget.m_close){
        m_options_widget.draw();
    } else {
        m_painter->setPen(m_penBlack);
        m_painter->setBrush(m_brushWhiteAlpha);
        m_painter->drawRect(m_x, m_height*0.15, m_lg, m_height*0.7);
        
        {
            QString s = "Menu";
            drawQText(s, m_x + m_lg/2, 0.25*m_height, sizeText_big, true);
        }

        drawButtonImage(m_buttonOk, m_imgOk);
        drawButtonImage(m_buttonParam, m_imgParam);
        drawButtonImage(m_buttonStop, m_imgStop);
    
    }
}
void MenuWidget::onMouse(int x, int y){
    if(!m_options_widget.m_close){
        m_options_widget.onMouse(x, y);
    } else {
    
        if(m_buttonOk.isActive(x, y)){
            m_close = true;
        } else if(m_buttonStop.isActive(x, y)){
            exit(0);
        } else if(m_buttonParam.isActive(x, y)){
            m_options_widget.open();
            m_options_widget.m_close = false;
        }
    }
   
    
}

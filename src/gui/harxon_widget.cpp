#include "harxon_widget.hpp"
#include "../framework.hpp"

BaseWidgetSerie::BaseWidgetSerie(){
    m_imgClose = loadImage("/images/ok.png");
};

void BaseWidgetSerie::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    for(auto c : m_buttons){
        c->m_button.setResize(c->m_x*m_width, c->m_y*m_height,m_gros_button);
    }
};

void BaseWidgetSerie::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhiteAlpha);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8);
    m_painter->setBrush(m_brushDarkGray);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.1, m_height*0.8);
    
    drawButtonImage(m_button_close, m_imgClose);
    for(auto c : m_buttons){
        drawButton(c->m_button);
        drawText(c->m_label,c->m_x*m_width +50, c->m_y*m_height);
    }
    
};
void BaseWidgetSerie::onMouse(int x, int y){
    if(m_button_close.isActive(x,y)){
        m_close = true;
    }
    for(auto c : m_buttons){
        if(c->m_button.isActive(x, y)){
            Framework::Instance().sendMessages(c->m_command);
        }
        //drawText(c->m_label,c->m_x*m_width +50, c->m_y*m_height);
    }
    
};

void BaseWidgetSerie::add(double x, double y, std::string label, std::string command){
    auto b = new SerieButton;
    b->m_x = x;
    b->m_y = y;
    b->m_label = label;
    b->m_command = command;
    m_buttons.push_back(b);
    
}

HarxonWidget::HarxonWidget(){
    add(0.2, 0.2, "NOVP teuteu", "$CFG NTRIP 51.68.227.135 2101 NOVP teuteu teuteu 3\r\n");
    add(0.2, 0.4, "NRSAGTF lemairec", "$CFG NTRIP 51.68.227.135 8083 NRSAGTF lemairec lemairec 3\r\n");
    add(0.2, 0.6, "VRSAGTF lemairec", "$CFG NTRIP 51.68.227.135 8083 VRSAGTF lemairec lemairec 3\r\n");
}

MotorWidget::MotorWidget(){
    add(0.2, 0.2, "$H", "$H\r\n");
    add(0.2, 0.4, "$P", "$P\r\n");
    add(0.2, 0.6, "$L,255", "$L,255\r\n");
    add(0.4, 0.6, "$0", "$L,0\r\n");
    add(0.6, 0.6, "$R,255", "$R,255\r\n");
}

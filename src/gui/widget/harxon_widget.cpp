#include "harxon_widget.hpp"
#include "../../framework.hpp"

BaseWidgetSerie::BaseWidgetSerie(){
    m_imgClose = loadImage("/gui/ok.png");
};

void BaseWidgetSerie::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_x2 = 10;
    m_y2 = 10;
    m_width2 = 0.88*width;
    m_height2 = 1*height-20;
    
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    for(auto c : m_buttons){
        c->m_button.setResize(c->m_x*m_width, c->m_y*m_height,m_gros_button);
    }
};

void BaseWidgetSerie::draw(){
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_x2, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_whiteAlpha);
    drawButtonImage(m_button_close, m_imgClose);
    for(auto c : m_buttons){
        drawButtonLabel2(c->m_button);
        m_painter->setPen(m_pen_black);
        m_painter->setBrush(m_brush_whiteAlpha);
        drawText(c->m_label,c->m_x*m_width +50, c->m_y*m_height);
    }
    
};
int BaseWidgetSerie::onMouse(int x, int y){
    if(m_button_close.isActive(x,y)){
        m_close = true;
    }
    for(auto c : m_buttons){
        if(c->m_button.isActive(x, y)){
            Framework::Instance().sendMessages(c->m_command);
        }
        //drawText(c->m_label,c->m_x*m_width +50, c->m_y*m_height);
    }
    return 0;
    
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
    double x = 0.2;
    double y = 0.3;
    double inter = 0.1;
    
    add(x, y, "NOVP lemairec", "$CFG NTRIP 51.68.227.135 2101 NOVP lemairec lemairec 3\r\n");
    y+=inter;
    add(x, y, "NRSAGTF lemairec", "$CFG NTRIP 51.68.227.135 8083 NRSAGTF lemairec lemairec 3\r\n");
    y+=inter;
    add(x, y, "LAON centipede", "$CFG NTRIP caster.centipede.fr 2101 LAON centipede centipede 3\r\n");
    x = 0.6;
    y = 0.3;
    add(x, y, "Free APN", "$CFG NET free\r\n");
    y+=inter;
    add(x, y, "Thing Mobile APN", "$CFG NET TM\r\n");
    
    
    
}

MotorWidget::MotorWidget(){
    add(0.2, 0.2, "$H", "$H\r\n");
    add(0.2, 0.4, "$P", "$P\r\n");
    add(0.2, 0.6, "$L,255", "$L,255\r\n");
    add(0.4, 0.6, "$0", "$L,0\r\n");
    add(0.6, 0.6, "$R,255", "$R,255\r\n");
}

BineuseWidget::BineuseWidget(){
    add(0.2, 0.2, "$V", "$V\r\n");
    add(0.2, 0.3, "$P", "$P\r\n");
    double y = 0.5;
    double inter = 0.1;
    add(0.2, y, "$ON,L", "$ON,L\r\n");
    add(0.6, y, "$ON,R", "$ON,R\r\n");
    y+=inter;
    add(0.2, y, "$R,-255", "$R,-255,*\r\n");
    add(0.6, y, "$R,255", "$R,255,*\r\n");
    y+=inter;
    add(0.2, y, "$R,-100", "$R,-100,*\r\n");
    add(0.6, y, "$R,100", "$R,100,*\r\n");
    y+=inter;
    add(0.2, y, "$R,-1", "$R,-1,*\r\n");
    add(0.6, y, "$R,1", "$R,1,*\r\n");
    y+=inter;
    add(0.2, y, "$R,-0", "$R,-0,*\r\n");
    add(0.6, y, "$R,0", "$R,0,*\r\n");
}

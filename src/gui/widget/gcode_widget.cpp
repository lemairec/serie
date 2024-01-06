#include "gcode_widget.hpp"
#include "../../framework.hpp"
#include "../../util/util.hpp"



GcodeWidget::GcodeWidget(){
};

void GcodeWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_x2 = 10;
    m_y2 = 10;
    m_width2 = m_width*0.9;
    m_height2 = height-20;
    
    m_go_home.setResizeStd(m_x2+m_width2*0.3, m_y2+m_height2*0.2, "HOME");
    m_stop.setResizeStd(m_x2+m_width2*0.6, m_y2+m_height2*0.2, "STOP");
    
    m_charger_outil.setResizeStd(m_x2+m_width2*0.3, m_y2+m_height2*0.5, "outil+");
    m_decharger_outil.setResizeStd(m_x2+m_width2*0.3, m_y2+m_height2*0.7, "outil-");
    
    m_one_action.setResizeStd(m_x2+m_width2*0.6, m_y2+m_height2*0.5, "1 Action 1");
    m_many_actions.setResizeStd(m_x2+m_width2*0.6, m_y2+m_height2*0.7, "X Action 1");
};

void GcodeWidget::draw(){
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(10, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    drawButtonLabel2(m_go_home);
    drawButtonLabel2(m_charger_outil);
    drawButtonLabel2(m_decharger_outil);
    drawButtonLabel2(m_one_action);
    drawButtonLabel2(m_many_actions);
    
    drawButtonLabel2(m_stop, COLOR_CANCEL);
};
int GcodeWidget::onMouse(int x, int y){
    std::string orders = "M203 X100 Y100 Z100\n";
    if(m_go_home.isActive(x, y)){
        orders += "G28 Z\nG28\n";
        Framework::Instance().sendMessages(orders);
    }
    
   
    int x_g = 70; int y_g = 25; int z_g = 53;
    if(m_one_action.isActive(x, y)){
        int x2 = 100; int y2 = 100; int z2 = 122;
        orders += strprintf("G0 X%d Y%d Z00 F3000\n", x_g, y_g);
        orders += strprintf("M106 S255\n", x_g, y_g);
        orders += strprintf("G0 X%d Y%d Z%d F3000\n", x_g, y_g, z_g-10);
        orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g, z_g);
        orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g-2, y_g, z_g);
        orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g-2, z_g);
        orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g+2, y_g, z_g);
        orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g+2, z_g);
        orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g, z_g-10);
        orders += strprintf("G0 X%d Y%d Z00 F3000\n", x_g, y_g);
        orders += strprintf("G0 X%d Y%d Z00 F3000\n", x2, y2);
        orders += strprintf("G0 X%d Y%d Z%d F3000\n", x2, y2, z2);
        orders += strprintf("M106 S0\n", x_g, y_g);
        orders += strprintf("G0 X%d Y%d Z00 F3000\n", x2, y2);
        
        Framework::Instance().sendMessages(orders); //mm/min //100mm/s
    }
    if(m_many_actions.isActive(x, y)){
        int x2 = 100; int y2 = 100; int z2 = 122;
        for(int i = 0; i < 10; ++i){
            orders += strprintf("G0 X%d Y%d Z00 F3000\n", x_g, y_g);
            orders += strprintf("M106 S255\n", x_g, y_g);
            orders += strprintf("G0 X%d Y%d Z%d F3000\n", x_g, y_g, z_g-10);
            orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g, z_g);
            orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g-2, y_g, z_g);
            orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g-2, z_g);
            orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g+2, y_g, z_g);
            orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g+2, z_g);
            orders += strprintf("G0 X%d Y%d Z%d F300\n", x_g, y_g, z_g-10);
            orders += strprintf("G0 X%d Y%d Z00 F3000\n", x_g, y_g);
            orders += strprintf("G0 X%d Y%d Z00 F3000\n", x2, y2);
            orders += strprintf("G0 X%d Y%d Z%d F3000\n", x2, y2, z2);
            orders += strprintf("M106 S0\n", x_g, y_g);
            orders += strprintf("G0 X%d Y%d Z00 F3000\n", x2, y2);
            x2+=10;
        }
        Framework::Instance().sendMessages(orders);
    }
    if(m_stop.isActive(x, y)){
        orders = "M0\n M999\n";
        Framework::Instance().sendMessages(orders);
    }
    return 0;
    
};

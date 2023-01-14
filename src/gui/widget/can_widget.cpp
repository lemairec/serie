#include "can_widget.hpp"
#include "../../framework.hpp"




CanWidget::CanWidget(){
    m_img_plus = loadImage("/gui/plus.png");
    m_img_moins = loadImage("/gui/moins.png");
};

void CanWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    int x = m_width*0.3;
    int y = m_height*0.3;
    int inter = 0.05*m_width;
    
    m_lissage_ekf_xy.setResize(x, y, m_gros_button);
    y+=inter;
    m_lissage_ekf_cap.setResize(x, y, m_gros_button);
    y+=inter;
    m_lissage_ekf_a_cap.setResize(x, y, m_gros_button);
    y+=inter;
    m_lissage_ekf_v.setResize(x, y, m_gros_button);
    y+=inter;
    m_lissage_ekf_a_v.setResize(x, y, m_gros_button);
    y+=inter;
    m_lissage_ekf_roll.setResize(x, y, m_gros_button);
    y+=inter*1.2;
    m_button_send.setResize(x, y, "Send", true, 120, 40);
};

void CanWidget::draw(){
    Framework & f = Framework::Instance();
    if(m_lissage_ekf_xy.m_value == 0){
        m_lissage_ekf_xy.m_value = f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_xy;
        m_lissage_ekf_cap.m_value = f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_cap;
        m_lissage_ekf_a_cap.m_value = f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_a_cap;
        m_lissage_ekf_v.m_value = f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_v;
        m_lissage_ekf_a_v.m_value = f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_a_v;
        m_lissage_ekf_roll.m_value = f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_roll;
    }
    
    
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8, RAYON_ROUNDED, RAYON_ROUNDED);
    
    
    int y = m_height*0.2;
    
    y = m_height*0.2;
    {
        std::string s = "Version : " + f.m_nmea_parser.m_version;
        drawText(s, m_width*0.1, y);
    }
    y = m_height*0.25;
    {
        std::string s = "cfg_ekf : " + f.m_nmea_parser.m_last_cfg_ekf;
        drawText(s, m_width*0.1, y);
    }
    
    drawValueGui(m_lissage_ekf_xy, "ekf_xy", f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_xy);
    drawValueGui(m_lissage_ekf_cap, "ekf_cap", f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_cap);
    drawValueGui(m_lissage_ekf_a_cap, "ekf_a_cap", f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_a_cap);
    drawValueGui(m_lissage_ekf_v, "ekf_v", f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_v);
    drawValueGui(m_lissage_ekf_a_v, "ekf_a_v", f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_a_v);
    drawValueGui(m_lissage_ekf_roll, "ekf_roll", f.m_nmea_parser.m_cfg_ekf.m_lissage_ekf_roll);
    
    drawButtonLabel2(m_button_send);
};

void CanWidget::drawValueGui(ValueGui & value_gui, std::string s, double value){
    int x1 = m_width*0.1;
    int x3 = m_width*0.45;
    
    drawValueGuiKeyPad2(value_gui);
    drawText(s, x1, value_gui.m_y);
    if(value_gui.m_value != 0 && value_gui.m_value == value){
        drawText("ok", x3, value_gui.m_y);
    }
}


void CanWidget::onMouse(ValueGui & keypad, double x, double y, double pas){
    if(keypad.m_button_plus.isActive(x, y)){
        keypad.m_value += pas;
    }
    if(keypad.m_button_moins.isActive(x, y)){
        keypad.m_value -= pas;
    }
       
    /*if(isActiveValueGuiKeyPad(keypad,x, y)){
        m_keypad_widget.m_close = false;
        m_keypad_widget.setValueGuiKeyPad(&keypad);
    }*/
}

int CanWidget::onMouse(int x, int y){
    onMouse(m_lissage_ekf_xy, x, y, 0.01);
    onMouse(m_lissage_ekf_cap, x, y, 0.01);
    onMouse(m_lissage_ekf_a_cap, x, y, 0.01);
    onMouse(m_lissage_ekf_v, x, y, 0.01);
    onMouse(m_lissage_ekf_a_v, x, y, 0.01);
    onMouse(m_lissage_ekf_roll, x, y, 0.01);
    
    if(m_button_send.isActive(x, y)){
        std::string s = "$CFG_EKF,";
        s = s + std::to_string(m_lissage_ekf_xy.m_value) + ",";
        s = s + std::to_string(m_lissage_ekf_cap.m_value) + ",";
        s = s + std::to_string(m_lissage_ekf_a_cap.m_value) + ",";
        s = s + std::to_string(m_lissage_ekf_v.m_value) + ",";
        s = s + std::to_string(m_lissage_ekf_a_v.m_value) + ",";
        s = s + std::to_string(m_lissage_ekf_roll.m_value) + ",*\n";
        
        Framework & f = Framework::Instance();
        f.m_serial_port.writeGpsSerialS(s);
        INFO(s);
    }
    return 0;
    
};

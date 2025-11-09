#include "option_widget.hpp"
#include "../util/directory_manager.hpp"
#include <sstream>
#include <fstream>
#include <string>

#include "../framework.hpp"
#include "qt/main_window.hpp"
#include "main_widget.hpp"
#include "../config/langage.hpp"
//#include <QMediaPlayer>


#include <iostream>
#include <fstream>
#include <sstream>

OptionWidget::OptionWidget(){
    //m_close=false;
    //m_page =5;
    //addSerials();
}

void OptionWidget::loadImages(){
    m_imgClose = loadImage("/gui/ok.png");
    m_imgPlus = loadImage("/gui/plus.png");
    m_imgMinus = loadImage("/gui/minus.png");
    m_imgSatBlanc = loadImage("/gui/sat_blanc.png");
    m_imgSatGris = loadImage("/gui/sat_gris.png");
    m_imgVolantBlanc = loadImage("/gui/volant_blanc.png");
    m_imgVolantGris = loadImage("/gui/volant_gris.png");
    m_imgOutilBlanc = loadImage("/gui/outil_blanc.png");
    m_imgOutilGris = loadImage("/gui/outil_gris.png");
    m_imgOptionBlanc = loadImage("/gui/option_blanc.png");
    m_imgOptionGris = loadImage("/gui/option_gris.png");
    m_imgImuBlanc = loadImage("/gui/imu_blanc.png");
    m_imgImuGris = loadImage("/gui/imu_gris.png");
    
    m_img_off = loadImage("/gui/off.png");
    m_img_return = loadImage("/gui/return.png");
    
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");

}

void OptionWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_y2 = m_height*0.04;
    m_x2 = m_y2;
    m_width2 = m_width-2*m_y2-m_gros_button*2.4;
    m_height2 = m_height-2*m_y2;

    m_y_title = m_y2+m_height*0.08;
    m_y_inter = 0.08*m_height2;
    m_y_begin = m_y_title+4*m_y_inter;
    
    m_width3 = m_width2+m_y2+m_y2;
    m_part_1_x = m_width3*0.04;
    m_part_1_w = m_width3*0.44;
    m_part_1_m = m_part_1_x+0.5*m_width3*0.44;
    m_part_1_x2 = m_part_1_x+0.1*m_width3*0.44;
    m_part_1_x3 = m_part_1_x+0.8*m_width3*0.44;
    m_part_2_x = m_width3*0.52;
    m_part_2_w = m_width3*0.44;
    m_part_2_m = m_part_2_x+0.5*m_width3*0.44;
    m_part_2_x2 = m_part_2_x+0.1*m_width3*0.44;
    m_part_2_x3 = m_part_2_x+0.8*m_width3*0.44;
    
    m_select_widget.setSize(width, height);
    
    m_button_p1.setResize(0.1*m_width, 0.20*m_height, m_gros_button);
    m_button_p2.setResize(0.1*m_width, 0.30*m_height, m_gros_button);
    m_button_p3.setResize(0.1*m_width, 0.40*m_height, m_gros_button);
    m_button_p4.setResize(0.1*m_width, 0.50*m_height, m_gros_button);
    m_button_p5.setResize(0.1*m_width, 0.60*m_height, m_gros_button);
    m_button_p6.setResize(0.1*m_width, 0.70*m_height, m_gros_button);
    
    resizePage1();
    resizePage2();
    resizePage3();
    resizePage4();
    resizePage5();
    resizePage6();
    int x_right = width-m_gros_button-20;
    int inter = m_gros_button*2.1;
    int y = m_gros_button*1.2+10;
    m_button_close.setResize(x_right, y, m_gros_button);
    y += 1.5*inter;
    m_button_p1.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p2.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p3.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p4.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p5.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p6.setResize(x_right, y, m_gros_button);
    y += inter;
    
    m_button_return.setResize(x_right, m_height-m_gros_button*1.2-10, m_gros_button);
}

void OptionWidget::drawButtons(){
    {
        int h = m_height-20;
        int w = m_gros_button*2+20;
        
        m_painter->setBrush(m_brush_background_2);
        m_painter->setPen(m_pen_no);
        
        m_painter->drawRoundedRect(m_width-w-10, 10, w, h, 10, 10);
        
    }
    
    drawButtonImageCarre(m_button_close, m_img_off, 0.3, false, "CLOSE");
    drawButtonImageCarre(m_button_return, m_img_return, 0.3, false, "RETURN");
}

void OptionWidget::draw(){
    m_painter->setPen(m_pen_no);
    m_painter->setBrush(m_brush_background_1);
    m_painter->drawRect(0 , 0, m_width, m_height);
    
    drawButtons();
    
    if(m_page == 1){
        drawPage1();
    } else if(m_page == 2){
        drawPage2();
    } else if(m_page == 3){
        drawPage3();
    } else if(m_page == 4){
        drawPage4();
    } else if(m_page == 5){
        drawPage5();
    } else if(m_page == 6){
        drawPage6();
    }
    if(!m_select_widget.m_close){
        m_select_widget.draw();
    }
}

int OptionWidget::onMouse(int x, int y){
    if(m_button_return.isActive(x,y)){
        m_close = true;
    }
    if(m_button_close.isActive(x, y)){
        exit(0);
    }
    
    if(m_button_p1.isActive(x,y)){
        m_page = 1;
    } else if(m_button_p2.isActive(x,y)){
        m_page = 2;
    } else if(m_button_p3.isActive(x,y)){
        m_page = 3;
    } else if(m_button_p4.isActive(x,y)){
        m_page = 4;
    } else if(m_button_p5.isActive(x,y)){
        m_page = 5;
    } else if(m_button_p6.isActive(x,y)){
        m_page = 6;
    } else {
        if(m_page == 1){
            onMousePage1(x, y);
        } else if(m_page == 2){
            onMousePage2(x, y);
        } else if(m_page == 3){
            onMousePage3(x, y);
        } else if(m_page == 4){
            onMousePage4(x, y);
        } else if(m_page == 5){
            onMousePage5(x, y);
        } else if(m_page == 6){
            onMousePage6(x, y);
        }
    }
    return 0;
}


/**
 PAGE 1
 */

void OptionWidget::resizePage1(){
    //m_select_serial
    int y = 0.4*m_height;
    int inter = 0.1*m_height;
    
    m_select_serial.setResize(m_part_1_x+m_part_1_w/2, y, "OPT_CONN_CART", true, m_part_1_w/2);
    y+= inter;
    m_select_baudrates.setResize(m_part_1_x+m_part_1_w/2, y, "BAUDRATES", true, m_part_1_w/2);
    
    m_select_baudrates.clear();
    m_select_baudrates.addValueInt("4800", 4800);
    m_select_baudrates.addValueInt("9600", 9600);
    m_select_baudrates.addValueInt("115200", 115200);
    
    y+= inter;
    m_all_tty.setResize(m_part_1_x+m_part_1_w/2, y, "BAUDRATES", true, m_part_1_w/2);
};

void OptionWidget::drawPage1(){
    Framework & f = Framework::Instance();
    
    m_select_baudrates.setValueInt(f.m_config.m_baudrate);
    m_select_serial.setValueString(f.m_config.m_serial);
        
    drawText("titre", 0.5*m_width, 0.3*m_height);
    
    if(m_select_widget.m_close){
        m_select_serial.setValueString( f.m_config.m_serial);
        m_select_baudrates.setValueInt( f.m_config.m_baudrate);
    }
    drawButtonLabel2(m_select_serial.m_buttonOpen);
    drawButtonLabel2(m_select_baudrates.m_buttonOpen);
   
    drawText(f.m_serial_port.m_last_error, m_part_2_x+m_part_2_w/2, m_select_serial.m_y, sizeText_medium, true);
   
    drawButtonCheck(m_all_tty, f.m_config.m_all_tty, "ALL TTY");
    /*drawSelectButtonGuiClose(m_select_serial);
    drawSelectButtonGuiClose(m_select_baudrates);
    
    
    drawSelectButtonGuiOpen(m_select_baudrates);
    drawSelectButtonGuiOpen(m_select_serial);*/
        
}

void OptionWidget::onMousePage1(int x, int y){
    Framework & f = Framework::Instance();
    
    if(!m_select_widget.m_close){
        if(m_select_widget.onMouseSelect(x, y)){
            std::string s = m_select_widget.m_selectButton->getValueString();
            f.m_config.m_serial = m_select_serial.getValueString();
            f.m_config.m_baudrate = m_select_baudrates.getValueInt();
            f.initOrLoadConfig();
        }
       
        return;
    }
    
    if(m_select_serial.m_buttonOpen.isActive(x, y)){
        m_select_widget.open();
        m_select_widget.setValueGuiKeyPad(&m_select_serial);
    }
    if(m_all_tty.isActive(x, y)){
        f.m_config.m_all_tty = !f.m_config.m_all_tty;
    }
    if(m_select_baudrates.m_buttonOpen.isActive(x, y)){
        m_select_widget.open();
        m_select_widget.setValueGuiKeyPad(&m_select_baudrates);
    }
}


/**
 PAGE 2
 */

void OptionWidget::resizePage2(){
    
    
}



void OptionWidget::drawPage2(){

}

void OptionWidget::onMousePage2(int x, int y){

}



/**
 PAGE 4
 */

void OptionWidget::resizePage4(){
};

void OptionWidget::drawPage4(){
   
    
}

void OptionWidget::onMousePage4(int x, int y){
}


/**
 PAGE 5
 */

void OptionWidget::resizePage5(){
    m_button_motor_inverse.setResize(0.35*m_width, 0.20*m_height, m_petit_button);
    m_button_encoder_inverse.setResize(0.6*m_width, 0.20*m_height, m_petit_button);
    
    m_motor_vitesse_agressivite.setResize(0.35*m_width, 0.3*m_height, m_petit_button, "moteur agressivite ");
    m_motor_vitesse_max.setResize(0.35*m_width, 0.35*m_height, m_petit_button, "moteur vitesse max ");
    m_volant_pas_by_tour.setResize(0.35*m_width, 0.45*m_height, m_petit_button, "encoder pas par tour ");
    m_volant_angle_by_tour.setResize(0.35*m_width, 0.5*m_height, m_petit_button, "roue angle par tour de volant ");
    m_volant_derive.setResize(0.35*m_width, 0.55*m_height, m_petit_button, "rattrapage de derive ");
    
    m_volant_frequence.setResize(0.35*m_width, 0.65*m_height, m_petit_button, "frequence ");
    m_virtual_point.setResize(0.35*m_width, 0.7*m_height, m_petit_button, "virtual point ");
    
    m_button_auto_deactive.setResize(0.35*m_width, 0.8*m_height, m_petit_button, "auto deactive ");
    m_button_auto_active.setResize(0.35*m_width, 0.85*m_height, m_petit_button, "auto active ");
};

void OptionWidget::drawPage5(){
    
}

void OptionWidget::onMousePage5(int x, int y){
    
}


/**
 PAGE 6
 */

void OptionWidget::resizePage6(){
};

void OptionWidget::drawPage6(){
    }

void OptionWidget::onMousePage6(int x, int y){
   
}


/**
 PAGE 3
 */

void OptionWidget::resizePage3(){
}



void OptionWidget::drawPage3(){
   
}

void OptionWidget::onMousePage3(int x, int y){
    
}

void OptionWidget::open(){
    m_close = false;
    addSerials();
}

void OptionWidget::addSerials(){
    Framework & f = Framework::Instance();
    
    std::vector<std::string> serials;
    serials.push_back("none");
    std::vector<std::string> & s2 = f.m_serial_port.getAvailablePorts(f.m_config.m_all_tty);
    for(auto s : s2){
        serials.push_back(s);
    }
    
    
    
    m_select_serial.clear();
    for(auto serial: serials){
        m_select_serial.addValue(serial);
    }
}




//base

void OptionWidget::drawButtonOption(ButtonGui & button, QPixmap * image, bool check, double scale){
    drawButtonImageCarre(button, image, scale*3, check);
}

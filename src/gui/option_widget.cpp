#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"

#define PETIT_RAYON2 0.025

OptionWidget::OptionWidget(){
    
    m_imgClose = loadImage("/images/ok.png");
    m_imgPlus = loadImage("/images/plus.png");
    m_imgMinus = loadImage("/images/minus.png");
    m_imgSatBlanc = loadImage("/images/sat_blanc.png");
    m_imgSatGris = loadImage("/images/sat_gris.png");
    m_imgVolantBlanc = loadImage("/images/volant_blanc.png");
    m_imgVolantGris = loadImage("/images/volant_gris.png");
    m_imgOutilBlanc = loadImage("/images/outil_blanc.png");
    m_imgOutilGris = loadImage("/images/outil_gris.png");
    m_imgOptionBlanc = loadImage("/images/option_blanc.png");
    m_imgOptionGris = loadImage("/images/option_gris.png");
    m_imgImuBlanc = loadImage("/images/imu_blanc.png");
    m_imgImuGris = loadImage("/images/imu_gris.png");
    
    //m_close=false;
    //m_page =5;
    //addSerials();
}

void OptionWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    
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
    
}

void OptionWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhiteAlpha);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8);
    m_painter->setBrush(m_brushDarkGray);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.1, m_height*0.8);
    
    drawButtonImage(m_button_close, m_imgClose);
    
    if(m_page == 1){
        drawButtonImage(m_button_p1, m_imgOptionBlanc);
        drawPage1();
    } else {
        drawButtonImage(m_button_p1, m_imgOptionGris);
    }
    
    if(m_page == 2){
        drawButtonImage(m_button_p2, m_imgSatBlanc);
        drawPage2();
    } else {
        drawButtonImage(m_button_p2, m_imgSatGris);
        
    }
    
    if(m_page == 3){
        drawButtonImage(m_button_p3, m_imgImuBlanc, 0.5);
        drawPage3();
    } else {
        drawButtonImage(m_button_p3, m_imgImuGris, 0.5);
        
    }
    
    if(m_page == 4){
        drawButtonImage(m_button_p4, m_imgVolantBlanc);
        drawPage4();
    } else {
        drawButtonImage(m_button_p4, m_imgVolantGris);
    }
    
    //GpsFramework & f = GpsFramework::Instance();
    
    if(m_page == 5){
        drawButtonImage(m_button_p5, m_imgVolantBlanc);
        drawPage5();
    } else {
        drawButtonImage(m_button_p5, m_imgVolantGris);
    }
    
    if(m_page == 6){
        drawButtonImage(m_button_p6, m_imgVolantBlanc);
        drawPage6();
    } else {
        drawButtonImage(m_button_p6, m_imgVolantGris);
    }
}

int OptionWidget::onMouse(int x, int y){
    
    if(m_button_close.isActive(x,y)){
        m_close = true;
    } else if(m_button_p1.isActive(x,y)){
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
    int x = 0.3*m_width;
    int y = 0.4*m_height;
    int inter = 0.1*m_height;
    
    m_select_serial.setResize(x, y, m_petit_button);
    y+= inter;
    m_select_baudrates.setResize(x, y, m_petit_button);
    
    m_select_baudrates.clear();
    m_select_baudrates.addValueInt("9600", 9600);
    m_select_baudrates.addValueInt("115200", 115200);
    
    
   
};

void OptionWidget::drawPage1(){
    Framework & f = Framework::Instance();
    
    m_select_baudrates.setValueInt(f.m_config.m_baudrate);
    m_select_serial.setValueString(f.m_config.m_serial);
        
    drawText("titre", 0.5*m_width, 0.3*m_height);
    
    /*drawSelectButtonGuiClose(m_select_serial);
    drawSelectButtonGuiClose(m_select_baudrates);
    
    
    drawSelectButtonGuiOpen(m_select_baudrates);
    drawSelectButtonGuiOpen(m_select_serial);*/
        
}

void OptionWidget::onMousePage1(int x, int y){
    Framework & f = Framework::Instance();
    /*if(onMouseSelectButton(m_select_serial, x, y)){
        f.m_config.m_serial = m_select_serial.getValueString();
        f.initOrLoadConfig();
    } else if(onMouseSelectButton(m_select_baudrates, x, y)){
        f.m_config.m_baudrate = m_select_baudrates.getValueInt();
        f.initOrLoadConfig();
    }*/
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
    addSerials();
}

void OptionWidget::addSerials(){
    Framework & f = Framework::Instance();
    
    std::vector<std::string> serials;
    serials.push_back("none");
    std::vector<std::string> & s2 = f.m_serial_port.getAvailablePorts();
    for(auto s : s2){
        serials.push_back(s);
    }
    
    
    
    
    m_select_serial.clear();
    for(auto serial: serials){
        m_select_serial.addValue(serial);
    }
}

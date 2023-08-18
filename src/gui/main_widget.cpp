#include "main_widget.hpp"

#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <iomanip>

#include "environnement.hpp"
#include "../framework.hpp"
#include "../util/log.hpp"


#define MY_WIDTH 800
#define MY_HEIGHT 400

QGraphicsPixmapItem * item;
QPixmap * p;

int l_bottom = 20;

MainWidget::MainWidget()
{
    
    m_imgMenu = loadImage("/gui/menu.png");
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");

    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_option_widget);
    m_widgets.push_back(&m_search_widget);
    m_widgets.push_back(&m_log_widget);
    m_widgets.push_back(&m_key_pad_widget);
    m_widgets.push_back(&m_harxon_widget);
    m_widgets.push_back(&m_motor_widget);
    m_widgets.push_back(&m_bineuse_widget);
}

void MainWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    BaseWidget::setSize(width, height);
    int x_right = width-m_gros_button*1.2;
    //int x_left = m_gros_button*1.2;
    //int y_bas = height - m_gros_button*1.2;
    int inter = m_gros_button*2.1;
    int y = m_gros_button*1.2;
    m_button_setting.setResize(x_right, y, m_gros_button);
    y += inter*1.5;
    m_button_gps.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_cap.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_cfg.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_can.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_search.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_log.setResize(x_right, y, m_gros_button);
    
    
    
    m_widthMax = m_width/2-50;
    m_heightMax = m_height/2-50;
    
    m_harxon_widget.setSize(m_width, m_height);
    for(auto p : m_widgets){
        p->setSize(m_width, m_height);
    }
    m_key_pad_widget.setSize(m_width, m_height);
    m_key_board_widget.setSize(m_width, m_height);
    m_gps_widget.setSize(m_width, m_height);
    m_cap_widget.setSize(m_width, m_height);
    m_cfg_widget.setSize(m_width, m_height);
    m_can_widget.setSize(m_width, m_height);
    

    int inter_x = m_petit_button*3;
    int x = inter_x;
    x += inter_x;
    x += inter_x;
    m_buttonMenu2.setResize(x, m_height-30, m_petit_button);
    x += inter_x;
    m_buttonMenu3.setResize(x, m_height-30, m_petit_button);
    x += inter_x;
    m_buttonMenu4.setResize(x, m_height-30, m_petit_button);
    m_buttonSendMessage.setResize(m_width-100, 0.5*m_height, m_gros_button);
    
    m_buttonSaveLog.setResize(m_width-30, m_height-30, m_gros_button);
    
    {
        int y = m_height-180;
        int y2 = y+20;
        int inter = 16;
        int i = 0;
    }
}

MainWidget * MainWidget::instance(){
    static MainWidget gf;
    return &gf;
}

void MainWidget::setPainter(QPainter * p){
    BaseWidget::setPainter(p);
    m_harxon_widget.setPainter(p);
    for(auto p2 : m_widgets){
        p2->setPainter(p);
    }
    m_key_board_widget.setPainter(p);
    m_gps_widget.setPainter(p);
    m_cap_widget.setPainter(p);
    m_cfg_widget.setPainter(p);
    m_can_widget.setPainter(p);
    m_log_widget.m_select_widget.setPainter(p);
}

int max = 10000;



void MainWidget::draw(){
    //scene = s;
    DEBUG("BEGIN");
    draw_force();
    DEBUG("END");
}


void MainWidget::draw_force(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushDarkGray);
    
    m_painter->drawRect(0, 0, m_width, 40);
    m_painter->drawRect(0, m_height-60, m_width, 60);
    
    drawMenuRight();
    m_painter->setPen(m_penBlack);
    drawMessages();
    drawButtons();
    
    for(auto p : m_widgets){
        if(!p->m_close){
            p->draw();
        }
    }
    
    if(!m_key_board_widget.m_close){
        m_key_board_widget.draw();
    }
    Framework & f = Framework::Instance();
    
    if(m_cap_widget.isOpen()){
        m_cap_widget.draw();
    } else if(m_gps_widget.isOpen()){
        m_gps_widget.draw();
    } else if(m_cfg_widget.isOpen()){
        m_cfg_widget.draw();
    } else if(m_can_widget.isOpen()){
        m_can_widget.draw();
    }
    
}

void MainWidget::drawMessages(){
    m_painter->setBrush(m_brushWhite);
    
    int x = 10;
    int w = m_width-200;
    int y = 60;
    int h = m_height-60-60-20;
    m_painter->drawRect(x, y, w, h);
    
    int y2 = y-10+h;
    int inter = 16;
    
    Framework & f = Framework::Instance();
    int i = 0;
    for(auto s : f.m_messages_serial){
        if(y2 < y){
            break;
        }
        drawText(s, x+10, y2);
        y2+= -inter;
        ++i;
        
    }
    
}


void MainWidget::drawMenuRight(){
    m_painter->setPen(m_penNo);
    m_painter->setBrush(m_brushDarkGray);
    
    m_painter->drawRect(m_width-80, 0, 80, m_height);
}

void MainWidget::drawButtons(){
    Framework & f = Framework::Instance();
    drawButtonImageCarre(m_button_setting, m_imgMenu, 0.8);
    
    drawButtonLabelCarre(m_button_gps, "GPS", 0.8, m_gps_widget.isOpen());
    drawButtonLabelCarre(m_button_cap, "CAP", 0.8, m_cap_widget.isOpen());
    drawButtonLabelCarre(m_button_cfg, "CFG", 0.8, m_cfg_widget.isOpen());
    drawButtonLabelCarre(m_button_can, "CAN", 0.8, m_can_widget.isOpen());
    drawButtonLabelCarre(m_button_search, "SEARCH", 0.8, m_search_widget.isOpen());
    drawButtonLabelCarre(m_button_log, "LOG", 0.8, m_log_widget.isOpen());
    
    drawButton(m_buttonMenu2);
    drawButton(m_buttonMenu3);
    drawButton(m_buttonMenu4);
    
    drawButton(m_buttonSaveLog);
    drawButtonCheck(m_buttonSaveLog, f.m_save_log);
    
    drawButton(m_buttonSendMessage);
    drawText("envoyer message", m_buttonSendMessage.m_x, m_buttonSendMessage.m_y, sizeText_little, true);
}


int MainWidget::onMouse(int x, int y){
    Framework & f = Framework::Instance();
    
    size_t n = m_widgets.size();
    for(size_t i = 0; i < n; ++i){
        auto p = m_widgets[n-i-1];
        if(!p->m_close){
            p->onMouse(x, y);
            return 0;
        }
    }
    
    if(m_button_setting.isActive(x, y)){
        m_option_widget.open();
    } else if(m_buttonMenu2.isActive(x, y)){
        m_harxon_widget.m_close = false;
    } else if(m_buttonMenu3.isActive(x, y)){
        m_motor_widget.m_close = false;
    } else if(m_buttonMenu4.isActive(x, y)){
        m_bineuse_widget.m_close = false;
    } else if(m_buttonSaveLog.isActive(x, y)){
        f.changeSaveLog();
    } else if(m_buttonSendMessage.isActive(x, y)){
        m_key_board_widget.m_close = false;
        
        
    } else if(!m_key_board_widget.m_close){
        m_key_board_widget.onMouse(x, y);
        if(m_key_board_widget.m_close){
            QString s2 = m_key_board_widget.getText();
            s2 += "\r\n";
            std::string s = s2.toUtf8().constData();
            f.sendMessages(s);
        }
    } else if(m_button_gps.isActive(x, y)){
        f.m_gps = !f.m_gps;
        f.m_can = false;
        m_can_widget.m_close = true;
        m_gps_widget.m_close = true;
        m_cap_widget.m_close = true;
        if(f.m_gps){
            m_gps_widget.open();
        }
    } else if(m_button_cap.isActive(x, y)){
        f.m_gps = !f.m_gps;
        f.m_can = false;
        m_can_widget.m_close = true;
        m_gps_widget.m_close = true;
        m_cap_widget.m_close = true;
        if(f.m_gps){
            m_cap_widget.open();
        }
    } else if(m_button_can.isActive(x, y)){
        f.m_gps = false;
        f.m_can = !f.m_can;
        m_gps_widget.m_close = true;
        m_cap_widget.m_close = true;
        m_can_widget.m_close = true;
        if(f.m_can){
            m_can_widget.open();
        }
    } else if(m_button_cfg.isActive(x, y)){
        f.m_can = false;
        f.m_gps = !f.m_gps;
        m_gps_widget.m_close = true;
        m_cap_widget.m_close = true;
        m_cfg_widget.m_close = true;
        if(f.m_gps){
            m_cfg_widget.open();
        }
    } else if(m_button_search.isActive(x, y)){
        for(auto w : m_widgets){
            w->m_close = true;
        }
        if(m_search_widget.m_close){
            m_search_widget.open();
        } else {
            m_search_widget.m_close = true;
        }
    } else if(m_button_log.isActive(x, y)){
        for(auto w : m_widgets){
            w->m_close = true;
        }
        if(m_log_widget.m_close){
            m_log_widget.open();
        } else {
            m_log_widget.m_close = true;
        }
        
    }
    
    if(f.m_gps){
        if(m_cfg_widget.isOpen()){
            m_cfg_widget.onMouse(x, y);
        }
    }
    if(m_can_widget.isOpen()){
        m_can_widget.onMouse(x, y);
    }
    return 0;
}


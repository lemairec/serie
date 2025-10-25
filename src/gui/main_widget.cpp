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
    
    
    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_option_widget);
    m_widgets.push_back(&m_search_widget);
    m_widgets.push_back(&m_log_widget);
    m_widgets.push_back(&m_key_pad_widget);
}

void MainWidget::loadImages(){
    m_imgMenu = loadImage("/gui/menu.png", true);
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");

}


void MainWidget::setSize(int width, int height){ BaseWidget::setSize(width, height);
    int x_right = width-m_gros_button-20;
    int inter = m_gros_button*2.1;
    int y = m_gros_button*1.2+10;
    m_button_setting.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_gps.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_gcode.setResize(x_right, y, m_gros_button);
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
    
    for(auto p : m_widgets){
        p->setSize(m_width, m_height);
    }
    m_key_pad_widget.setSize(m_width, m_height);
    m_key_board_widget.setSize(m_width, m_height);
    m_key_board_widget_hex.setSize(m_width, m_height);
    m_gps_widget.setSize(m_width, m_height);
    m_gcode_widget.setSize(m_width, m_height);
    m_cfg_widget.setSize(m_width, m_height);
    m_can_widget.setSize(m_width, m_height);

    y = 0.4*m_height;
    m_buttonSendMessage.setResizeStd(m_width*0.77, y, "");
    y += inter;
    m_buttonSendMessagHex.setResizeStd(m_width*0.77, y, "");
    y += inter;
    m_buttonPosition.setResize(m_width*0.77+10, y, m_gros_button);
    y += inter;
    m_button_hexa.setResize(m_width*0.77+10, y, m_gros_button);
    y += inter;
    m_button_max.setResize(m_width*0.77+10, y, m_gros_button);
}

MainWidget * MainWidget::instance(){
    static MainWidget gf;
    return &gf;
}

void MainWidget::setPainter(QPainter * p){
    BaseWidget::setPainter(p);
    for(auto p2 : m_widgets){
        p2->setPainter(p);
    }
    m_key_board_widget.setPainter(p);
    m_key_board_widget_hex.setPainter(p);
    m_gps_widget.setPainter(p);
    m_gcode_widget.setPainter(p);
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
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_background_1);
    
    
    m_painter->setPen(m_pen_black);
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
    if(!m_key_board_widget_hex.m_close){
        m_key_board_widget_hex.draw();
    }

    if(m_gcode_widget.isOpen()){
        m_gcode_widget.draw();
    } else if(m_gps_widget.isOpen()){
        m_gps_widget.draw();
    } else if(m_cfg_widget.isOpen()){
        m_cfg_widget.draw();
    } else if(m_can_widget.isOpen()){
        m_can_widget.draw();
    }
    
}

void MainWidget::drawMessages(){
    m_painter->setBrush(m_brush_white);
    
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


void MainWidget::drawButtons(){
    Framework & f = Framework::Instance();
    if(true){
        {
            int h = m_height-20;
            int w = m_gros_button*2+20;
            
            m_painter->setBrush(m_brush_background_2);
            m_painter->setPen(m_pen_no);
            
            m_painter->drawRoundedRect(m_width-w-10, 10, w, h, 10, 10);
            
        }
        drawButtonImageCarre(m_button_setting, m_imgMenu, 0.8*0.4);
        
        drawButtonImageCarre(m_button_gps, m_imgMenu, 0.8*0.4, false, "GPS");
        drawButtonImageCarre(m_button_gcode, m_imgMenu, 0.8*0.4, false, "gcode");
        drawButtonImageCarre(m_button_cfg, m_imgMenu, 0.8*0.4, false, "CFG");
        drawButtonImageCarre(m_button_can, m_imgMenu, 0.8*0.4, false, "CAN");
        drawButtonImageCarre(m_button_search,m_imgMenu, 0.8*0.4, !m_search_widget.m_close, "SEARCH");
        drawButtonImageCarre(m_button_log, m_imgMenu, 0.8*0.4, false, "LOG");
    }
    
    drawButtonCheck(m_buttonPosition, f.m_position, "$P");
    drawButtonCheck(m_button_hexa, f.m_hexa, "hexa");
    drawButtonCheck(m_button_max, f.m_max, "[40]");
    
    drawButtonLabel2(m_buttonSendMessage);
    drawText("envoyer message", m_buttonSendMessage.m_x, m_buttonSendMessage.m_y, sizeText_little, true);
    drawButtonLabel2(m_buttonSendMessagHex);
    drawText("envoyer hexa", m_buttonSendMessagHex.m_x, m_buttonSendMessagHex.m_y, sizeText_little, true);
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
    } else if(m_buttonPosition.isActive(x, y)){
        f.m_position= !f.m_position;
    } else if(m_button_hexa.isActive(x, y)){
        f.m_hexa= !f.m_hexa;
    } else if(m_button_max.isActive(x, y)){
        f.m_max= !f.m_max;
    } else if(m_buttonSendMessage.isActive(x, y)){
        m_key_board_widget.m_close = false;
    } else if(m_buttonSendMessagHex.isActive(x, y)){
        m_key_board_widget_hex.m_close = false;
    } else if(!m_key_board_widget.m_close){
        m_key_board_widget.onMouse(x, y);
        if(m_key_board_widget.m_close){
            QString s2 = m_key_board_widget.getText();
            s2 += "\r\n";
            std::string s = s2.toUtf8().constData();
            f.sendMessages(s);
        }
    } else if(!m_key_board_widget_hex.m_close){
        m_key_board_widget_hex.onMouse(x, y);
        if(m_key_board_widget_hex.m_close){
            f.sendMessagesHexa(m_key_board_widget_hex.m_hx_res);
        }
    } else if(m_button_gps.isActive(x, y)){
        f.m_gps = !f.m_gps;
        f.m_can = false;
        m_can_widget.m_close = true;
        m_gps_widget.m_close = true;
        m_gcode_widget.m_close = true;
        if(f.m_gps){
            m_gps_widget.open();
        }
    } else if(m_button_gcode.isActive(x, y)){
        f.m_gps = !f.m_gps;
        f.m_can = false;
        m_can_widget.m_close = true;
        m_gps_widget.m_close = true;
        m_gcode_widget.m_close = true;
        if(f.m_gps){
            m_gcode_widget.open();
        }
    } else if(m_button_can.isActive(x, y)){
        f.m_gps = false;
        f.m_can = !f.m_can;
        m_gps_widget.m_close = true;
        m_gcode_widget.m_close = true;
        m_can_widget.m_close = true;
        if(f.m_can){
            m_can_widget.open();
        }
    } else if(m_button_cfg.isActive(x, y)){
        f.m_can = false;
        f.m_gps = !f.m_gps;
        m_gps_widget.m_close = true;
        m_gcode_widget.m_close = true;
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
    
    if(m_gcode_widget.isOpen()){
        m_gcode_widget.onMouse(x, y);
    } else if(m_can_widget.isOpen()){
        m_can_widget.onMouse(x, y);
    }
    return 0;
}


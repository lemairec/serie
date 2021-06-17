#include "gps_widget.hpp"

#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <iomanip>

#include "../logging.hpp"
#include "environnement.hpp"
#include "../framework.hpp"


#define MY_WIDTH 800
#define MY_HEIGHT 400

QGraphicsPixmapItem * item;
QPixmap * p;

int l_bottom = 20;

GpsWidget::GpsWidget()
{
    
    m_imgMenu = loadImage("/images/menu.png");

    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_menuWidget);
    m_widgets.push_back(&m_key_pad_widget);
}

void GpsWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_widthMax = m_width/2-50;
    m_heightMax = m_height/2-50;
    
    for(auto p : m_widgets){
        p->setSize(m_width, m_height);
    }
    m_key_pad_widget.setSize(m_width, m_height);
     m_key_board_widget.setSize(m_width, m_height);
    
    m_buttonMenu.setResize(40, m_height-30, m_gros_button);
    m_buttonSendMessage.setResize(0.7*m_width, 0.5*m_height, m_gros_button);
}

GpsWidget * GpsWidget::Instance(){
    static GpsWidget gf;
    return &gf;
}

void GpsWidget::setPainter(QPainter * p){
    BaseWidget::setPainter(p);
    for(auto p2 : m_widgets){
        p2->setPainter(p);
    }
    m_key_board_widget.setPainter(p);
}

int max = 10000;



void GpsWidget::draw(){
    //scene = s;
    DEBUG("BEGIN");
    draw_force();
    DEBUG("END");
}


void GpsWidget::draw_force(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushDarkGray);
    
    m_painter->drawRect(0, 0, m_width, 40);
    m_painter->drawRect(0, m_height-60, m_width, 60);
    
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
}

void GpsWidget::drawMessages(){
    m_painter->setBrush(m_brushWhite);
    
    m_painter->drawRect(10, 60, m_width/2, m_height-140);
    
    int x = 20;
    int y = 60+m_height-140-10;
    int inter = 16;
    
    Framework & f = Framework::Instance();
    int i = 0;
    for(auto s : f.m_messages_serial){
        drawText(s, x, y);
        y+= -inter;
        ++i;
        if(y < 60){
            break;
        }
    }
    
}


void GpsWidget::drawButtons(){
    drawButtonImage(m_buttonMenu, m_imgMenu);
    drawButton(m_buttonSendMessage);
    drawText("envoyer message", m_buttonSendMessage.m_x, m_buttonSendMessage.m_y);
}


void GpsWidget::onMouse(int x, int y){
    Framework & f = Framework::Instance();
    
    size_t n = m_widgets.size();
    for(size_t i = 0; i < n; ++i){
        auto p = m_widgets[n-i-1];
        if(!p->m_close){
            p->onMouse(x, y);
            return;
        }
    }
    
    if(m_buttonMenu.isActive(x, y)){
        m_menuWidget.m_close = false;
    } else if(m_buttonSendMessage.isActive(x, y)){
        m_key_board_widget.m_close = false;
        
        
    } else if(!m_key_board_widget.m_close){
        m_key_board_widget.onMouse(x, y);
        if(m_key_board_widget.m_close){
            QString s2 = m_key_board_widget.m_res;
            s2 += "\n";
            std::string s = s2.toUtf8().constData();
            INFO(s);
            f.m_serial_port.writeGpsSerialS(s);
        }
    }
}


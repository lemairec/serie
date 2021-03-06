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
    
    m_imgMenu = loadImage("/images/menu.png");
    m_img_check_on = loadImage("/images/check_on.png");
    m_img_check_off = loadImage("/images/check_off.png");

    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_menuWidget);
    m_widgets.push_back(&m_key_pad_widget);
    m_widgets.push_back(&m_harxon_widget);
    m_widgets.push_back(&m_motor_widget);
}

void MainWidget::setSize(int width, int height){
    {
        BaseWidget::setSize(width, height);
        int x_right = width-40;
        int inter = 0.09*height;
        int y = inter*0.8;
        m_buttonMenu.setResize(x_right, y, m_gros_button);
    }
    
    
    m_widthMax = m_width/2-50;
    m_heightMax = m_height/2-50;
    
    m_harxon_widget.setSize(m_width, m_height);
    for(auto p : m_widgets){
        p->setSize(m_width, m_height);
    }
    m_key_pad_widget.setSize(m_width, m_height);
    m_key_board_widget.setSize(m_width, m_height);

    
    int inter_x = m_petit_button*3;
    int x = inter_x;
    x += inter_x;
    x += inter_x;
    m_buttonMenu2.setResize(x, m_height-30, m_petit_button);
    x += inter_x;
    m_buttonMenu3.setResize(x, m_height-30, m_petit_button);
    m_buttonSendMessage.setResize(m_width-100, 0.5*m_height, m_gros_button);
    
    m_buttonSaveLog.setResize(m_width-30, m_height-30, m_gros_button);
    
    int y = m_height-180;
    int y2 = y+20;
    int inter = 16;
    int i = 0;
    
    m_categories.clear();
    for(auto c : Framework::Instance().m_categories){
        (void)c;
        ButtonGui * b = new ButtonGui();
        b->setResize(20, y2, 8);
        b->m_labelInt = i;
        
        ++i;
        y2+= inter;
        m_categories.push_back(b);
        
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
    drawCategories();
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

void MainWidget::drawMessages(){
    m_painter->setBrush(m_brushWhite);
    
    int x = 10;
    int w = m_width-200;
    int y = 60;
    int h = m_height-60-20-180;
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

void MainWidget::drawCategories(){
    m_painter->setBrush(m_brushWhite);
    
    int x = 10;
    int w = m_width-200;
    int y = m_height-180;
    int h = 100;
    m_painter->drawRect(x, y, w, h);
    
    int y2 = y+20;
    int inter = 16;
    
    Framework & f = Framework::Instance();
    int i = 0;
    for(auto b : m_categories){
        auto c = f.m_categories[b->m_labelInt];
        if(c->m_enable){
            drawButton(*b, COLOR_CHECK);
        } else {
            drawButton(*b, COLOR_OTHER);
        }
    }
    for(auto s : f.m_categories){
        drawText(s->m_begin, x+20, y2);
        drawQText(QString::number(s->m_count), x+100, y2);
        drawText(s->m_last, x+140, y2);
        y2 += inter;
        ++i;
        if(y2 > y+h){
            break;
        }
    }
    
}

void MainWidget::drawMenuRight(){
    m_painter->setPen(m_penNo);
    m_painter->setBrush(m_brushDarkGray);
    
    m_painter->drawRect(m_width-80, 0, 80, m_height);
}

void MainWidget::drawButtons(){
    drawButtonImage(m_buttonMenu, m_imgMenu);
    drawButton(m_buttonMenu2);
    drawButton(m_buttonMenu3);
    
    Framework & f = Framework::Instance();
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
    
    for(auto b : m_categories){
        if(b->isActive(x, y)){
            auto c = f.m_categories[b->m_labelInt];
            c->m_enable = !c->m_enable;
        };
    }
    
    if(m_buttonMenu.isActive(x, y)){
        m_menuWidget.m_close = false;
    } else if(m_buttonMenu2.isActive(x, y)){
        m_harxon_widget.m_close = false;
    } else if(m_buttonMenu3.isActive(x, y)){
        m_motor_widget.m_close = false;
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
    }
    return 0;
}


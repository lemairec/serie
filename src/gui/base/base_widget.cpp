#include "base_widget.hpp"
#include "../../util/directory_manager.hpp"
#include <iostream>
#include <sstream>

//#define DEBUG_GUI

BaseWidget::BaseWidget(){
    m_penBlack = QPen(Qt::black);
    m_penWhite = QPen(Qt::white);
    m_penGray = QPen(QColor(120,120,120));
    m_penRed = QPen(Qt::red);
    m_penGreen = QPen(Qt::green);
    m_penBlue = QPen(Qt::blue);
    m_penBlue2 = QPen(Qt::blue, 5);
    
    
    m_brushGray = QBrush (QColor(200,200,200));
    m_brushParcelle = QBrush(QColor(133,146,118, 100));

    m_brushBackGround1 = QBrush(QColor(183,166,138));
    m_brushBackGround2 = QBrush(QColor(183*1.2,166*1.2,138*1.2));
    
    
    m_brushDarkGray = QBrush (QColor(80,80,80));
    m_brushGray = QBrush (QColor(200,200,200));
    
    QColor gray = QColor(120,120,120);
    gray.setAlphaF(0.95);
    m_brushLightGrayDebug = QBrush (gray);
    QColor gray2 = QColor(60,60,60);
    gray2.setAlphaF(0.7);
    m_brushGrayAlpha = QBrush (gray2);
    
    
    m_brushGreen = QBrush (Qt::green);
    m_brushGreenButton= QBrush(QColor(123,180,149));
    m_brushWhite = QBrush(QColor(255,255,255));
    m_brushRedButton = QBrush(QColor(252,83,83));
    
    QColor white = QColor(255,255,255);
    white.setAlphaF(0.9);
    m_brushWhiteAlpha =QBrush(white);
    m_brushGreenAlpha = QBrush(QColor(0, 150, 0, 100));
    m_penNo.setColor(QColor(0, 250, 0, 0));
    m_brushOrange = QBrush(QColor(255, 127, 0));
    m_brushBlue = QBrush(QColor(0, 0, 250));
    m_brushRed = QBrush(Qt::red);
    
    int alpha = 255;
    //alpa = 100;
    QColor colorTracteur = QColor(0,0,200,alpha);
    m_brushTracteur = QBrush(colorTracteur);
    
    QColor colorOutil = QColor(60,60,200,alpha);
    m_brushOutil = QBrush(colorOutil);
    
    /*m_penOutil = QPen(colorOutil, 0.3*m_zoom);
    m_penTractorEssieu = QPen(color, 0.15*m_zoom);
    m_penTractorRoue = QPen(color, 0.3*m_zoom);*/
    m_img_plus = loadImage("/gui/plus.png");
    m_img_moins = loadImage("/gui/moins.png");
}


void BaseWidget::setSize(int width, int height){
    m_gros_button = 0.05*height;
    m_petit_button = 0.035*height;
    m_gros_gros_button = 0.12*height;
    m_width = width;
    m_height = height;
}

void BaseWidget::open(){
    m_close = false;
}

bool BaseWidget::isOpen(){
    return !m_close;
}

void BaseWidget::drawButtonImage(ButtonGui & button, QPixmap * pixmap, double scale){
    double scale2 = 0.4*scale;
    int w = pixmap->size().width()*scale2;
    int h = pixmap->size().height()*scale2;

    m_painter->drawPixmap(button.m_x-w/2, button.m_y-h/2, w, h, *pixmap);

#ifdef DEBUG_GUI
    int x = button.m_x-button.m_rayon;
    int y = button.m_y-button.m_rayon;
    int d = button.m_rayon*2;
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhiteAlpha);
    m_painter->drawEllipse(x, y, d, d);
#endif
}

void BaseWidget::drawButtonImageCarre(ButtonGui & button, QPixmap * pixmap, double scale, bool open){
    double scale2 = 0.4*scale;
    int w = pixmap->size().width()*scale2;
    int h = pixmap->size().height()*scale2;

    int x = button.m_x-button.m_rayon;
    int y = button.m_y-button.m_rayon;
    int d = button.m_rayon*2;
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushDarkGray);
    m_painter->drawRoundedRect(x, y, d, d, 5, 5);
    
    m_painter->drawPixmap(button.m_x-w/2, button.m_y-h/2, w, h, *pixmap);

    if(open){
        m_painter->setPen(m_penBlack);
        m_painter->setBrush(m_brushWhiteAlpha);
        
        m_painter->drawRoundedRect(x, y, d, d, 5, 5);
    }
}

void BaseWidget::drawMyImage(QPixmap & pixmap, int x, int y, double scale, bool center){
    double scale2 = 0.4*scale;
    
    int w = pixmap.size().width()*scale2;
    int h = pixmap.size().height()*scale2;

    m_painter->drawPixmap(x-w/2, y-h/2, w, h, pixmap);
}

void BaseWidget::drawButtonCheck(ButtonGui & button, bool check, const std::string & s){
    int x = button.m_x+2*button.m_rayon;
    int y = button.m_y;
    
    if(check){
        drawButtonImage(button, m_img_check_on, 1.3);
    } else {
        drawButtonImage(button, m_img_check_off, 1.3);
    }
    
    drawText(s, x, y, sizeText_medium);
}

void BaseWidget::drawButtonCheck(ButtonGui & button, bool check){
    int x = button.m_x+2*button.m_rayon;
    int y = button.m_y;
    
    if(check){
        drawButtonImage(button, m_img_check_on, 1.3);
    } else {
        drawButtonImage(button, m_img_check_off, 1.3);
    }
    
    drawQText(button.m_label, x, y, sizeText_medium);
}


void BaseWidget::drawButton(ButtonGui & button, int color){
    int x = button.m_x-button.m_rayon;
    int y = button.m_y-button.m_rayon;
    int d = button.m_rayon*2;
    
    m_painter->setPen(m_penBlack);
    if(color == COLOR_RED){
        m_painter->setBrush(QBrush(QColor(255, 0, 0)));
        m_painter->drawEllipse(x, y, d, d);
    } else if(color == COLOR_GREEN){
        m_painter->setBrush(QBrush(QColor(0, 255, 0)));
        m_painter->drawEllipse(x, y, d, d);
    } else if(color == COLOR_CHECK){
        int d2 = d*0.1;
        m_painter->setBrush(QBrush(QColor(255, 255, 255)));
        m_painter->drawEllipse(x, y, d, d);
        m_painter->setBrush(QBrush(QColor(155, 155, 155)));
        m_painter->drawEllipse(x+d2, y+d2, d-2*d2, d-2*d2);
    } else {
        m_painter->setBrush(QBrush(QColor(255, 255, 255)));
        m_painter->drawEllipse(x, y, d, d);
    }
    
#ifdef DEBUG_GUI
    m_painter->drawEllipse(button.m_x-10, button.m_y-10, 20, 20);
    m_painter->drawEllipse(button.m_x, button.m_y, 1, 1);
#endif
}

void BaseWidget::drawButtonCarre(ButtonGui & button, int color){
    m_painter->setPen(m_penBlack);
    if(color == COLOR_RED){
        m_painter->setBrush(QBrush(QColor(255, 0, 0)));
    } else if(color == COLOR_VALIDATE){
        m_painter->setBrush(m_brushGreenButton);
    } else if(color == COLOR_CANCEL){
        m_painter->setBrush(m_brushDarkGray);
    }
    m_painter->drawRoundedRect(button.m_x-button.m_rayon , button.m_y-button.m_rayon, button.m_rayon*2, button.m_rayon*2, 5, 5);
    
    
#ifdef DEBUG_GUI
    m_painter->drawEllipse(button.m_x-10, button.m_y-10, 20, 20);
    m_painter->drawEllipse(button.m_x, button.m_y, 1, 1);
#endif
}

void BaseWidget::drawButtonLabel2(ButtonGui & button, int color){
    m_painter->setPen(m_penBlack);
    if(color == COLOR_CANCEL){
        m_painter->setBrush(m_brushGray);
    } else if(color == COLOR_VALIDATE){
        m_painter->setBrush(m_brushGreenButton);
    } else if(color == COLOR_FAIL){
        m_painter->setBrush(m_brushDarkGray);
    } else if(color == COLOR_CHECK){
        m_painter->setBrush(m_brushDarkGray);
    } else if(color == COLOR_WHITE){
        m_painter->setBrush(m_brushWhite);
    } else {
        m_painter->setBrush(m_brushGray);
    }
    m_painter->drawRoundedRect(button.m_x-button.m_width/2 , button.m_y-button.m_height/2, button.m_width, button.m_height, 5, 5);
    drawQText(button.m_label, button.m_x, button.m_y, sizeText_medium, true, false);
#ifdef DEBUG_GUI
    drawButton(button);
#endif
}

void BaseWidget::drawButtonValidate(ButtonGui & button){
    drawButtonLabel2(button, COLOR_VALIDATE);
}

void BaseWidget::drawButtonCancel(ButtonGui & button){
    drawButtonLabel2(button, COLOR_CANCEL);
}

void BaseWidget::drawText(const std::string & text, int x, int y, SizeText size, bool center, bool white){
    QString s = QString::fromStdString(text);
    
    drawQText(s, x, y, size, center, white);
}

void BaseWidget::drawQText(const QString & s, int x, int y, SizeText size, bool center, bool white){
    int s2 = 10;
    switch (size) {
        case sizeText_bigbig:
            s2 = 22;
            break;
        case sizeText_big:
            s2 = 20;
            break;
        case sizeText_medium:
            s2 = 18;
            break;
        case sizeText_little:
            s2 = 14;
            break;
    }
    QFont font = QFont("Latin", s2, 1, false);
    font.setBold(true);
    //textItem->setFont(font);
    if(white){
        m_painter->setPen(Qt::white);
    }
    
    font.setPixelSize(s2);
    m_painter->setFont(font);
    
    if(center){
        //auto mBounds = textItem->boundingRect();
        auto fm = m_painter->fontMetrics();
        auto rect = fm.boundingRect(s);
        m_painter->drawText(x-rect.width()/2, y+5, s);
    } else {
        m_painter->drawText(x, y+2, s);
    }
   
}

void BaseWidget::drawQTexts(const QString & s, int x, int y, SizeText size, bool center, bool white){
    int s2 = 10;
    switch (size) {
        case sizeText_bigbig:
            s2 = 24;
            break;
        case sizeText_big:
            s2 = 22;
            break;
        case sizeText_medium:
            s2 = 18;
            break;
        case sizeText_little:
            s2 = 14;
            break;
    }
    QFont font = QFont("Latin", s2, 1, false);
    font.setBold(true);
    //textItem->setFont(font);
    if(white){
        m_painter->setPen(Qt::white);
    }
    
    QStringList list1 = s.split(QLatin1Char('\n'));
    
    font.setPixelSize(s2);
    m_painter->setFont(font);
    
    int y2 = y+5;
    for(auto s3 : list1){
        if(center){
            //auto mBounds = textItem->boundingRect();
            auto fm = m_painter->fontMetrics();
            auto rect = fm.boundingRect(s3);
            m_painter->drawText(x-rect.width()/2, y2, s3);
        } else {
            m_painter->drawText(x, y2, s3);
        }
        y2 += s2*1.2;
    }
   
}

QPixmap * BaseWidget::loadImage(const std::string & s){
    std::string s2 = DirectoryManager::Instance().getSourceDirectory()+s;
    QImage image2(QString::fromStdString(s2));
    QPixmap * res  = new QPixmap(QPixmap::fromImage(image2));
    return res;
}

void BaseWidget::drawValueGuiKeyPad(ValueGui & value){
    QString s = QString::number(value.m_value);
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushGreenAlpha);
    m_painter->drawRect(value.m_x-40, value.m_y-15, 80, 30);
    drawQText(s, value.m_x, value.m_y, sizeText_medium, true);
}


void BaseWidget::drawValueGuiKeyPad2(ValueGui & keypad){
    drawButtonImage(keypad.m_button_plus, m_img_plus);
    drawButtonImage(keypad.m_button_moins, m_img_moins);
    
    drawValueGuiKeyPad(keypad);
}

void BaseWidget::drawValueGuiAndLabel(ValueGui & keypad, double value){
    keypad.m_value = value;
    drawButtonImage(keypad.m_button_plus, m_img_plus);
    drawButtonImage(keypad.m_button_moins, m_img_moins);
    drawText(keypad.m_label, keypad.m_label_x, keypad.m_label_y, sizeText_medium, keypad.m_label_center);
    
    drawValueGuiKeyPad(keypad);
}

bool BaseWidget::isActiveValueGuiKeyPad(ValueGui & value, int x, int y){
    if(value.m_x-30 < x && x < value.m_x + 30 && value.m_y-15 < y && y < value.m_y+15){
        return true;
    }
    return false;
    
}

double getNextValue(double value, bool positif){
    std::vector<double> t = {0.9, 1 , 1.1, 1.2, 1.3, 1.4, 1.5, 1.7, 2, 2.2, 2.4, 2.6, 3 , 3.3, 3.6, 4, 4.5,  5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5 ,9, 9.5 ,10,11};
    double res = value;
    int i = 0;
    for(int j = 0; j < 4; ++j){
        if(res > 10){
            res = res/10;
            ++i;
        }
        if(res < 1){
            res = res*10;
            --i;
        }
    }

    size_t j = 0;
    double min = 10;
    for(size_t k = 0; k < t.size(); ++k){
        double v = res/t[k];
        if(std::abs(v-1) < min){
            j = k;
            min = std::abs(v-1);
        }
        
    }
    double next_value = res;
    if(positif){
        if(j+1 < t.size()){
            next_value = t[j+1];
        }
    } else {
        if(j-1 >= 0){
            next_value = t[j-1];
        }
    }
    if(i>0){
        for(int j = 0; j < i; ++j){
            next_value = next_value*10.0;
        }
    }
    if(i<0){
        for(int j = 0; j < -i; ++j){
            next_value = next_value/10.0;
        }
    }
    return next_value;
}

bool BaseWidget::onMouseKeyPad2(ValueGui & keypad, double x, double y, double inter){
    if(keypad.m_button_plus.isActive(x, y)){
        if(inter == 0){
            keypad.m_value = getNextValue(keypad.m_value, true);
        } else {
            keypad.m_value += inter;
        }
        return true;
    }
    if(keypad.m_button_moins.isActive(x, y)){
        if(inter == 0){
            keypad.m_value = getNextValue(keypad.m_value, false);
        } else {
            keypad.m_value -= inter;
        }
        return true;
    }
       
    if(isActiveValueGuiKeyPad(keypad,x, y)){
        //INFO("ici2");
        //m_keypad_widget.m_close = false;
        //INFO("ici22");
        //m_keypad_widget.setValueGuiKeyPad(&keypad);
    }
    return false;
}

void BaseWidget::drawValueGuiKeyBoard(ValueGuiKeyBoard & value){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushGreenAlpha);
    m_painter->drawRect(value.m_x-80, value.m_y-15, 160, 30);
    drawText(value.m_text, value.m_x, value.m_y, sizeText_medium, true);
}

void BaseWidget::drawValueGuiKeyBoardDisable(ValueGuiKeyBoard & value){
    drawText(value.m_text, value.m_x, value.m_y, sizeText_medium, true);
}

bool BaseWidget::isActiveValueGuiKeyBoard(ValueGuiKeyBoard & value, int x, int y){
    if(value.m_x-80 < x && x < value.m_x + 80 && value.m_y-15 < y && y < value.m_y+15){
       return true;
   }
   return false;
}

/* Select Gui example
 m_langage.setResize(m_part_1_x+m_part_1_w/2, y, "", true, m_part_1_w/2);
 m_langage.clear();
 m_langage.addValue(Langage::getKey("FR"));
 m_langage.addValue(Langage::getKey("EN"));
 m_langage.addValue(Langage::getKey("DE"));
 drawPart1Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, "langue");
 drawButtonLabel2(m_langage.m_buttonOpen);
 
 if(m_select_widget.m_close){
     m_langage.setValueString(Langage::getKey(config.m_langage.getStdValue()));
 }
 
 if(!m_select_widget.m_close){
     if(m_select_widget.onMouseSelect(x, y)){
         std::string s = m_select_widget.m_selectButton->getValueString();
         if(s == Langage::getKey("FR")){
             config.m_langage.setValue("FR");
         } else if(s == Langage::getKey("EN")){
             config.m_langage.setValue("EN");
         } else if(s == Langage::getKey("DE")){
             config.m_langage.setValue("DE");
         }
         loadConfig();
     }
    
     return;
 }
 
 if(m_langage.m_buttonOpen.isActive(x, y)){
     m_select_widget.open();
     m_select_widget.setValueGuiKeyPad(&m_langage);
 }
 */

/* ValueGui Exemple
 m_command_capteur_vitesse_cm_s.setResize(m_part_1_x3, y, m_petit_button);
{
     m_command_capteur_vitesse_cm_s.m_value = config.m_command_capteur_vitesse_mm_s.getValue()/10.0;
     drawText(Langage::getKey("HYDR_V_MAX"), m_part_1_x2,m_command_capteur_vitesse_cm_s.m_y, sizeText_medium);
     drawValueGuiKeyPad2(m_command_capteur_vitesse_cm_s);
 }
 if(onMouseKeyPad2(m_command_capteur_vitesse_cm_s, x, y, 0.5)){
     config.m_command_capteur_vitesse_mm_s.setValue(m_command_capteur_vitesse_cm_s.m_value*10);
 };
 */

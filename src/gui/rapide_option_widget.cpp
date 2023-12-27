#include "rapide_option_widget.hpp"

#include "../framework_vision.hpp"
#include "qt/main_window.hpp"

#include "../config/langage.hpp"

RapideOptionWidget::RapideOptionWidget(){
}

void RapideOptionWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_x = m_width*0.65+20;
    m_width2 = m_width*0.24;
    
    m_y = 10;
    m_height2 = m_height*0.81;
    
    m_x_middle = m_x+m_width2/2;
    m_x_left = m_x+m_width2*1/3;
    m_x1 = m_x+m_width2*1/4;
    m_x2 = m_x+m_width2*2/3;
    
    m_y_title = m_height*0.1;
    
    m_keypad_widget.setSize(width, height);
    m_button_close.setResize(m_x_middle, m_y+0.90*m_height2, QString::fromStdString(Langage::getKey("CLOSE")), true);
    setSizePage1(width, height);
    setSizePage2(width, height);
    setSizePage3(width, height);
    setSizePage4(width, height);
    setSizePage5(width, height);
    setSizePage6(width, height);
    
    m_button_next.setResizeStd(m_x+0.85*m_width2, m_y+0.95*m_height2, "", true, 0.1*m_height);
}

void RapideOptionWidget::loadImages(){
    BaseWidget::loadImages();
    m_img_check_on = loadImageInv("/gui/check_on.png");
    m_img_check_off = loadImageInv("/gui/check_off.png");

}


void RapideOptionWidget::loadConfig(){
    FrameworkVision::instance().m_config.save();
    ICommand * command = new CommandReloadConfig();
    FrameworkVision::instance().addCommand(command);
}

void RapideOptionWidget::resetConfig(){
    FrameworkVision::instance().m_config.load();
    ICommand * command = new CommandReloadConfig();
    FrameworkVision::instance().addCommand(command);
}

void RapideOptionWidget::draw(){
    m_painter->setPen(m_pen_no);
    m_painter->setBrush(m_brush_background_2);
    m_painter->drawRoundedRect(m_x, m_y, m_width2, m_height2, 10, 10);
    m_painter->setPen(m_pen_black_inv);
    
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
    } else if(m_page == 7){
        drawPage7();
    } else if(m_page == 8){
        drawPage8();
    }
    
    Config & config = FrameworkVision::instance().m_config;
    if(config.isTechnicien()){
        QString s = QString::number(m_page)+"/"+QString::number(m_nbr_page);
        m_button_next.m_label = s.toUtf8().constData();
        drawButtonLabel2(m_button_next);
    }
    
    drawButtonLabel2(m_button_close, COLOR_CANCEL);
}

int RapideOptionWidget::onMouse(int x, int y){
    Config & config = FrameworkVision::instance().m_config;

    if(m_button_close.isActive(x,y)){
        config.m_type_print = TypePrint_OriginWithRayon;
        config.m_print_epaisseur = false;
        
        loadConfig();
        m_close = true;
        return 0;
    }
    
    
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
    if(m_button_next.isActive(x, y)){
        Config & config = FrameworkVision::instance().m_config;
        
        if(config.isTechnicien()){
            m_page++;
            if(m_page > m_nbr_page){
                m_page = 1;
            }
        }
    }
    return 0;
}

void RapideOptionWidget::open(){
    m_close = false;
    //addSerials();
}


/**
    PAGE 1
 */

void RapideOptionWidget::setSizePage1(int width, int height){
    m_valuegui_red.setResize(m_x_middle, 0.4*m_height, m_petit_button, "");
    m_valuegui_contraste.setResize(m_x_middle, 0.6*m_height, m_petit_button, "");
    
    int y =  0.4*m_height2;
    int dx = 0.07*m_height;
    m_coeff_0.setResize(m_x_middle-2*dx, y, m_petit_button);
    m_coeff_1.setResize(m_x_middle-1*dx, y, m_petit_button);
    m_coeff_2.setResize(m_x_middle, y, m_petit_button);
    m_coeff_3.setResize(m_x_middle+1*dx, y, m_petit_button);
    m_coeff_4.setResize(m_x_middle+2*dx, y, m_petit_button);
    
    y =  0.6*m_height2;
    
    m_contrast_0.setResize(m_x_middle-2*dx, y, m_petit_button);
    m_contrast_1.setResize(m_x_middle-1*dx, y, m_petit_button);
    m_contrast_2.setResize(m_x_middle, y, m_petit_button);
    m_contrast_3.setResize(m_x_middle+1*dx, y, m_petit_button);
    m_contrast_4.setResize(m_x_middle+2*dx, y, m_petit_button);
    
    m_avanced_bw.setResizeStd(m_x_middle, 0.2*m_height2, "", true);
    m_avance_label_av = QString::fromStdString(Langage::getKey("RAPIDE_AVANCED"));
    m_avance_label_re = QString::fromStdString(Langage::getKey("RETURN"));
};

void RapideOptionWidget::drawPage1(){
    Config & config = FrameworkVision::instance().m_config;

    m_painter->setPen(m_pen_black_inv);

    drawText(Langage::getKey("RAPIDE_GREEN"), m_coeff_2.m_x, m_coeff_2.m_y-40, sizeText_medium, true);
    drawText(Langage::getKey("RAPIDE_DARK"), m_coeff_4.m_x, m_coeff_2.m_y+40, sizeText_little, true);
    drawText(Langage::getKey("RAPIDE_LIGHT"), m_coeff_0.m_x, m_coeff_4.m_y+40, sizeText_little, true);
    
    drawText(Langage::getKey("RAPIDE_CONSTRASTE"), m_contrast_2.m_x, m_contrast_2.m_y-40, sizeText_medium, true);
    drawText(Langage::getKey("RAPIDE_LOW"), m_contrast_0.m_x, m_contrast_2.m_y+40, sizeText_little, true);
    drawText(Langage::getKey("RAPIDE_HIGH"), m_contrast_4.m_x, m_contrast_2.m_y+40, sizeText_little, true);

    if(!m_avance_black_white){
        
        m_painter->setPen(m_pen_no);
        m_painter->setBrush(QBrush(QColor(115, 115, 115)));
        double r = m_coeff_0.m_rayon*0.8;
        m_painter->drawRect(m_coeff_0.m_x, m_coeff_0.m_y-5, m_coeff_4.m_x-m_coeff_0.m_x, 10);
        m_painter->drawEllipse(m_coeff_0.m_x-r, m_coeff_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_coeff_1.m_x-r, m_coeff_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_coeff_2.m_x-r, m_coeff_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_coeff_3.m_x-r, m_coeff_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_coeff_4.m_x-r, m_coeff_0.m_y-r, 2*r, 2*r);
        
        r = m_coeff_0.m_rayon*0.5;
        m_painter->setBrush(m_brush_white);
        if(config.m_coeff_color <= -1){
            m_painter->drawEllipse(m_coeff_0.m_x-r-1, m_coeff_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_color <= -0.5){
            m_painter->drawEllipse(m_coeff_1.m_x-r-1, m_coeff_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_color < 0.5){
            m_painter->drawEllipse(m_coeff_2.m_x-r-1, m_coeff_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_color >= 1){
            m_painter->drawEllipse(m_coeff_4.m_x-r-1, m_coeff_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_color >= 0.5){
            m_painter->drawEllipse(m_coeff_3.m_x-r-1, m_coeff_0.m_y-r-1, 2*r, 2*r);
        }
        
        
        m_painter->setPen(m_pen_no);
        m_painter->setBrush(QBrush(QColor(115, 115, 115)));
        r = m_contrast_0.m_rayon*0.8;
        m_painter->drawRect(m_contrast_0.m_x, m_contrast_0.m_y-5, m_contrast_4.m_x-m_contrast_0.m_x, 10);
        m_painter->drawEllipse(m_contrast_0.m_x-r, m_contrast_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_contrast_1.m_x-r, m_contrast_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_contrast_2.m_x-r, m_contrast_2.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_contrast_3.m_x-r, m_contrast_0.m_y-r, 2*r, 2*r);
        m_painter->drawEllipse(m_contrast_4.m_x-r, m_contrast_0.m_y-r, 2*r, 2*r);
        
        r = m_contrast_0.m_rayon*0.5;
        m_painter->setBrush(m_brush_white);
        
        if(config.m_coeff_res <= 4){
            m_painter->drawEllipse(m_contrast_0.m_x-r-1, m_contrast_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_res <= 7){
            m_painter->drawEllipse(m_contrast_1.m_x-r-1, m_contrast_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_res <= 10) {
            m_painter->drawEllipse(m_contrast_2.m_x-r-1, m_contrast_0.m_y-r-1, 2*r, 2*r);
        } else if(config.m_coeff_res <= 15){
            m_painter->drawEllipse(m_contrast_3.m_x-r-1, m_contrast_0.m_y-r-1, 2*r, 2*r);
        } else {
            m_painter->drawEllipse(m_contrast_4.m_x-r-1, m_contrast_0.m_y-r-1, 2*r, 2*r);
        }
        
        m_avanced_bw.m_label = m_avance_label_av;
    } else {
        m_valuegui_red.m_value = config.m_coeff_color;
        draw(m_valuegui_red, "");
        
        m_valuegui_contraste.m_value = config.m_coeff_res;
        draw(m_valuegui_contraste, "");
        
        m_avanced_bw.m_label = m_avance_label_re;
    }
    
    drawButtonLabel2(m_avanced_bw);
}

void RapideOptionWidget::onMousePage1(int x, int y){
    Config & config = FrameworkVision::instance().m_config;
    if(!m_avance_black_white){
        if(m_coeff_0.isActive(x, y) != 0){
            config.m_coeff_color = -1;
            loadConfig();
        } else if(m_coeff_1.isActive(x, y) != 0){
            config.m_coeff_color = -0.5;
            loadConfig();
        }else if(m_coeff_2.isActive(x, y) != 0){
            config.m_coeff_color = 0;
            loadConfig();
        }else if(m_coeff_3.isActive(x, y) != 0){
            config.m_coeff_color = 0.5;
            loadConfig();
        }else if(m_coeff_4.isActive(x, y) != 0){
            config.m_coeff_color = 1;
            loadConfig();
        }
        
        if(m_contrast_0.isActive(x, y) != 0){
            config.m_coeff_res = 4;
            loadConfig();
        } else if(m_contrast_1.isActive(x, y) != 0){
            config.m_coeff_res = 7;
            loadConfig();
        }else if(m_contrast_2.isActive(x, y) != 0){
            config.m_coeff_res = 10;
            loadConfig();
        }else if(m_contrast_3.isActive(x, y) != 0){
            config.m_coeff_res = 15;
            loadConfig();
        }else if(m_contrast_4.isActive(x, y) != 0){
            config.m_coeff_res = 20;
            loadConfig();
        }
    } else {
        if(m_valuegui_red.isActive(x, y) != 0){
            
            config.m_coeff_color += m_valuegui_red.getIntValue(x, y)*0.1;
            loadConfig();
        }
        
        if(m_valuegui_contraste.isActive(x, y) != 0){
            int contraste = config.m_coeff_res;
            int value = m_valuegui_contraste.getIntValue(x, y)*1;
            config.m_coeff_res = contraste+value;
            loadConfig();
        }
    }
    
    if(m_avanced_bw.isActive(x, y)){
        m_avance_black_white = !m_avance_black_white;
    }
    
   
}

/**
    PAGE 2
 */


void RapideOptionWidget::draw(ValueGui & keypad, std::string s){
    int dy = 30;
    drawText(s, keypad.m_x, keypad.m_y-dy, sizeText_medium, true);

    drawValueGuiKeyPad2(keypad);
}
void RapideOptionWidget::drawFalse(ValueGui & keypad, std::string s){
    int dy = 30;
    drawText(s, keypad.m_x, keypad.m_y-dy, sizeText_medium, true);

    drawValueGuiKeyPadFalse(keypad);
}

void RapideOptionWidget::onMouse(ValueGui & keypad, double x, double y, double pas){
    if(keypad.m_button_plus.isActive(x, y)){
        keypad.m_value += pas;
    }
    if(keypad.m_button_moins.isActive(x, y)){
        keypad.m_value -= pas;
    }
       
    if(isActiveValueGuiKeyPad(keypad,x, y)){
        m_keypad_widget.m_close = false;
        m_keypad_widget.setValueGuiKeyPad(&keypad);
    }
}

/*
page 2

*/

int y_camera = 0;
int y_culture = 0;
void RapideOptionWidget::setSizePage2(int width, int height){
    m_calcul.setResizeStd(m_x_middle, 0.80*m_height2, Langage::getKey("RAPIDE_AUTO_CALCUL"), true);
    m_avanced_pt.setResizeStd(m_x_middle, 0.2*m_height2, Langage::getKey("RAPIDE_AVANCED"), true);
   
    int y = m_height2*0.65;
    m_lum0.setResize(m_x + m_width2*(0.2), y, m_petit_button);
    m_lum1.setResize(m_x + m_width2*(0.4), y, m_petit_button);
    m_lum2.setResize(m_x + m_width2*(0.6), y, m_petit_button);
    m_lum3.setResize(m_x + m_width2*(0.8), y, m_petit_button);
  
    m_ajust_yes.setResizeStd(m_x + m_width2*0.3, 0.6*m_height2, Langage::getKey("YES"), true);
    m_ajust_no.setResizeStd(m_x + m_width2*0.7, 0.6*m_height2, Langage::getKey("NO"), true);
};



void RapideOptionWidget::drawPage2(){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = f.m_config;
    if(f.m_decisionModule.m_ajust == 100){
        int x = m_x + m_width2*(0.5);
        int y = 0.3*m_height;
        
        std::string s2 = Langage::getKey("RAPIDE_AUTO_RES");
        drawQTexts(QString::fromStdString(s2),x, y, sizeText_medium, true);
        
        drawButtonLabel2(m_ajust_yes, COLOR_VALIDATE);
        drawButtonLabel2(m_ajust_no, COLOR_FAIL);
        return;
    } else if(f.m_decisionModule.m_ajust != 0){
        double perc = f.m_decisionModule.m_ajust*0.01;
        
        int y = 0.3*m_height;
        int x = m_x + m_width2*(0.5);
        
        std::string s2 = Langage::getKey("RAPIDE_AUTO_PROGRESS");
        drawText(s2, x, y, sizeText_medium, true);
       
        
        y = 0.5*m_height;
        int h = 0.1*m_height;
        x = m_x + m_width2*(0.2);
        int w = 0.6*m_width2;
        
        m_painter->drawRoundedRect(x, y-h/2, w, h, 5, 5);
        
        m_painter->setBrush(m_brush_button_validate);
        m_painter->drawRoundedRect(x, y-h/2, perc*w, h, 5, 5);
        QString s3 = QString::number(std::round(perc*100))+ " %";
        drawQText(s3, x+w/2, y, sizeText_medium, true);
        
        
        return;
    }
    
    m_culture_developpement = round(config.m_pattern_epaisseur_mm/(0.15*f.m_config.m_pattern_inter_rang_mm));
    
    
    drawText(Langage::getKey("RAPIDE_LINES"), m_x_middle, y_camera, sizeText_medium, true);
    drawButtonLabel2(m_calcul, COLOR_VALIDATE);
    drawButtonLabel2(m_avanced_pt);
    
    m_painter->setPen(m_pen_black_inv);
    drawText(Langage::getKey("RAPIDE_CULTURE"), m_x_middle, y_culture, sizeText_medium, true);
    {
        m_valuegui_nbr_rang.m_value = config.m_nbr_rangs;
        draw(m_valuegui_nbr_rang, Langage::getKey("RAPIDE_NB_RANGS"));
    }
    
    {
        m_valuegui_inter.m_value = config.m_pattern_inter_rang_mm/10.0;
        draw(m_valuegui_inter, Langage::getKey("RAPIDE_INTERRANG"));
    }
    
     
    m_painter->setPen(m_pen_no);
    m_painter->setBrush(QBrush(QColor(115, 115, 115)));
    int r = m_lum1.m_rayon*0.8;
    m_painter->drawRect(m_lum0.m_x, m_lum0.m_y-5, m_lum3.m_x-m_lum0.m_x, 10);
    m_painter->drawEllipse(m_lum0.m_x-r, m_lum0.m_y-r, 2*r, 2*r);
    m_painter->drawEllipse(m_lum1.m_x-r, m_lum1.m_y-r, 2*r, 2*r);
    m_painter->drawEllipse(m_lum2.m_x-r, m_lum2.m_y-r, 2*r, 2*r);
    m_painter->drawEllipse(m_lum3.m_x-r, m_lum3.m_y-r, 2*r, 2*r);
    r = m_lum1.m_rayon*0.5;
    m_painter->setBrush(m_brush_white);
    if(m_culture_developpement == 0){
        m_painter->drawEllipse(m_lum0.m_x-r, m_lum0.m_y-r, 2*r, 2*r);
    } else if(m_culture_developpement == 1){
        m_painter->drawEllipse(m_lum1.m_x-r, m_lum1.m_y-r, 2*r, 2*r);
    } else if(m_culture_developpement == 2){
        m_painter->drawEllipse(m_lum2.m_x-r, m_lum2.m_y-r, 2*r, 2*r);
    } else if(m_culture_developpement == 3){
        m_painter->drawEllipse(m_lum3.m_x-r, m_lum3.m_y-r, 2*r, 2*r);
    }
    
    
    m_painter->setPen(m_pen_black_inv);
    drawText("Epaisseur", m_x + m_width2*(0.5), m_lum1.m_y-3*r, sizeText_medium, true);
    drawText("Petit", m_x + m_width2*(0.2), m_lum1.m_y+2.5*r, sizeText_medium, true);
    drawText("Grand", m_x + m_width2*(0.8), m_lum1.m_y+2.5*r, sizeText_medium, true);
   
    
    if(!m_keypad_widget.m_close){
        m_keypad_widget.draw();
    }
}

void RapideOptionWidget::onMousePage2(int x, int y){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = f.m_config;
    
    if(f.m_decisionModule.m_ajust == 100){
        if(m_ajust_yes.isActive(x, y)){
            loadConfig();
            f.m_decisionModule.m_ajust = 0;
        }
        if(m_ajust_no.isActive(x, y)){
            resetConfig();
            f.m_decisionModule.m_ajust = 0;
        }
        return;
    }else if(f.m_decisionModule.m_ajust !=0){
        return;
    }
    if(m_lum0.isActive(x, y)){
        m_culture_developpement = 0;
    }
    if(m_lum1.isActive(x, y)){
        m_culture_developpement = 1;
    }
    if(m_lum2.isActive(x, y)){
        m_culture_developpement = 2;
    }
    if(m_lum3.isActive(x, y)){
        m_culture_developpement = 3;
    }
    
    onMouse(m_valuegui_inter, x, y);
    onMouse(m_valuegui_nbr_rang, x, y);
    m_keypad_widget.onMouse(x, y);
    config.m_pattern_inter_rang_mm = m_valuegui_inter.m_value*10;
    config.m_nbr_rangs = m_valuegui_nbr_rang.m_value;
    config.m_pattern_epaisseur_mm = m_culture_developpement*0.15*f.m_config.m_pattern_inter_rang_mm;
    
    loadConfig();
    
    if(m_avanced_pt.isActive(x, y)){
        m_page++;
    }
    if(m_calcul.isActive(x, y)){
        f.m_decisionModule.m_ajust = 1;
        loadConfig();
    }
}


void RapideOptionWidget::setSizePage3(int width, int height){
    int inter = 0.085*m_height2;
    int y = 0.085*m_height2;
    y_camera = y;
    
    m_avanced_pt.setResizeStd(m_x_middle, 0.2*m_height, Langage::getKey("RAPIDE_AVANCED"), true);
   
    
    y+= inter;
    m_valuegui_distance_image_mm.setResize(m_x_middle, y, m_petit_button);
    
    m_valuegui_hauteur_mm.setResize(m_x_middle, y, m_petit_button);
    
    m_distance1_mm.setResize(m_x_middle, y, m_petit_button);
    
    y+= inter;
    m_valuegui_angle.setResize(m_x_middle, y, m_petit_button);
    
    m_valuegui_h_angle.setResize(m_x_middle, y, m_petit_button);
    
    m_distance2_mm.setResize(m_x_middle, y, m_petit_button);
    
    y+= inter;
    y_culture = y;
    y+= inter;
    m_valuegui_nbr_rang.setResize(m_x_middle, y, m_petit_button);
    y+= inter;
    m_valuegui_inter.setResize(m_x_middle, y, m_petit_button);
    y+= inter;
    m_valuegui_epaisseur.setResize(m_x_middle, y, m_petit_button);
    y+= inter*1.3;
    m_valuegui_score_min.setResize(m_x_middle, y, m_petit_button);
    y+= inter*1.2;
    
    m_ajust.setResizeStd(m_x_middle, y, Langage::getKey("RAPIDE_AUTO_CALCUL"), true);

};



void RapideOptionWidget::drawPage3(){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = f.m_config;
    
    drawText(Langage::getKey("RAPIDE_LINES"), m_x_middle, y_camera, sizeText_medium, true);
    if(config.m_calibration_type == TypeCalibration_DistanceAngle){
        m_valuegui_distance_image_mm.m_value = config.m_calibration_da_distance/10.0;
        draw(m_valuegui_distance_image_mm, "distance (cm)");
        
        m_valuegui_angle.m_value = config.m_calibration_da_angle;
        draw(m_valuegui_angle, "angle (°)");
    } else if(config.m_calibration_type == TypeCalibration_DistanceDistance){
        m_distance1_mm.m_value = config.m_calibration_dd_d1/10.0;
        draw(m_distance1_mm, "distance haut (cm)");
        
        m_distance2_mm.m_value = config.m_calibration_dd_d2/10.0;
        draw(m_distance2_mm, "distance bas (cm)");
        
    } else{
        m_valuegui_hauteur_mm.m_value = config.m_calibration_ha_hauteur/10.0;
        draw(m_valuegui_hauteur_mm, Langage::getKey("RAPIDE_HAUTEUR"));
        
        m_valuegui_h_angle.m_value = config.m_calibration_ha_angle;
        draw(m_valuegui_h_angle, Langage::getKey("RAPIDE_ANGLE"));
    }
    
    drawText(Langage::getKey("RAPIDE_CULTURE"), m_x_middle, y_culture, sizeText_medium, true);
    {
        m_valuegui_nbr_rang.m_value = config.m_nbr_rangs;
        draw(m_valuegui_nbr_rang, Langage::getKey("RAPIDE_NB_RANGS"));
    }
    
    {
        m_valuegui_inter.m_value = config.m_pattern_inter_rang_mm/10.0;
        draw(m_valuegui_inter, Langage::getKey("RAPIDE_INTERRANG"));
    }
    {
        m_valuegui_epaisseur.m_value = config.m_pattern_epaisseur_mm/10.0;
        draw(m_valuegui_epaisseur, Langage::getKey("RAPIDE_EPAISSEUR"));
    }
    
    {
        m_valuegui_score_min.m_value = config.m_score_min;
        draw(m_valuegui_score_min, Langage::getKey("RAPIDE_SCORE_MIN"));
    }
    
    if(!m_keypad_widget.m_close){
        INFO("ici");
        m_keypad_widget.draw();
    }
}


void RapideOptionWidget::onMousePage3(int x, int y){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = f.m_config;
    if(config.m_calibration_type == TypeCalibration_DistanceAngle){
        m_valuegui_distance_image_mm.m_value = config.m_calibration_da_distance/10.0;
        onMouse(m_valuegui_distance_image_mm, x, y);
        onMouse(m_valuegui_angle, x, y);
        
    } else if(config.m_calibration_type == TypeCalibration_DistanceDistance){
        onMouse(m_distance1_mm, x, y);
        onMouse(m_distance2_mm, x, y);
    } else {
        onMouse(m_valuegui_hauteur_mm, x, y);
        onMouse(m_valuegui_h_angle, x, y);
    }
    onMouse(m_valuegui_inter, x, y);
    onMouse(m_valuegui_nbr_rang, x, y);
    onMouse(m_valuegui_score_min, x, y);
    onMouse(m_valuegui_epaisseur, x, y);

    m_keypad_widget.onMouse(x, y);
    
    config.m_pattern_inter_rang_mm = m_valuegui_inter.m_value*10;
    config.m_nbr_rangs = m_valuegui_nbr_rang.m_value;
    config.m_score_min = m_valuegui_score_min.m_value;
    config.m_pattern_epaisseur_mm = m_valuegui_epaisseur.m_value*10;
    if(config.m_calibration_type == TypeCalibration_DistanceAngle){
        config.m_calibration_da_distance = m_valuegui_distance_image_mm.m_value*10;
        config.m_calibration_da_angle = m_valuegui_angle.m_value;
    } else if(config.m_calibration_type == TypeCalibration_DistanceDistance){
        config.m_calibration_dd_d1 = m_distance1_mm.m_value*10;
        config.m_calibration_dd_d2 = m_distance2_mm.m_value*10;
    } else {
        config.m_calibration_ha_hauteur = m_valuegui_hauteur_mm.m_value*10;
        config.m_calibration_ha_angle = m_valuegui_h_angle.m_value;
    }
    loadConfig();
}

/*
page 4

*/

void RapideOptionWidget::setSizePage4(int width, int height){
    int inter = 0.1*m_height2;
    int y = 0.2*m_height2;
    m_auto_offset.setResize(m_x1, y, m_petit_button);
    y = y+inter;
    m_valuegui_offset.setResize(m_x_middle, y, m_petit_button);
    y = y+inter;
    m_valuegui_offset2.setResize(m_x_middle, y, m_petit_button);
    y = y+inter;
    m_offset_change.setResizeStd(m_x_middle, y, "CHANGE", true);
    y = y+1.5*inter;
    m_tilt.setResize(m_x1, y, m_petit_button);;
    y = y+inter;
    m_tilt_l.setResize(m_x_middle, y, m_petit_button);;
    
};



void RapideOptionWidget::drawPage4(){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = f.m_config;
    
    m_painter->setPen(m_pen_black_inv);
    drawText(Langage::getKey("RAPIDE_OFFSET"), m_x_middle, m_auto_offset.m_y-0.1*m_height, sizeText_medium, true);
    if(config.m_offset_auto_enable){
        drawButtonCheck(m_auto_offset, config.m_offset_auto, Langage::getKey("RAPIDE_OFFSET_AUTO"));
    }
    
    m_valuegui_offset.m_value = config.m_offset_mm/10.0;
    if(config.m_offset_auto && config.m_offset_auto_enable){
        if(f.m_pilot_module.m_offset_i == 0){
            draw(m_valuegui_offset, Langage::getKey("RAPIDE_DISTANCE"));
        } else {
            drawFalse(m_valuegui_offset, Langage::getKey("RAPIDE_DISTANCE"));
        }
    } else {
       draw(m_valuegui_offset, Langage::getKey("RAPIDE_DISTANCE"));
    }
    drawText(Langage::getKey("RIGHT"), m_contrast_4.m_x, m_valuegui_offset.m_y+30, sizeText_little, true);
    drawText(Langage::getKey("LEFT"), m_contrast_0.m_x, m_valuegui_offset.m_y+30, sizeText_little, true);
    
    m_valuegui_offset2.m_value = config.m_offset2_mm/10.0;
    if(config.m_offset_auto && config.m_offset_auto_enable){
        if(f.m_pilot_module.m_offset_i == 1){
            draw(m_valuegui_offset2, Langage::getKey("RAPIDE_OFFSET_2"));
        } else {
            drawFalse(m_valuegui_offset2, Langage::getKey("RAPIDE_OFFSET_2"));
        }
    }
    if(config.m_offset_auto && config.m_offset_auto_enable){
        drawButtonLabel2(m_offset_change);
    }
    
    m_painter->setPen(m_pen_black_inv);
    drawButtonCheck(m_tilt, config.m_tilt, Langage::getKey("RAPIDE_TILT"));
    m_tilt_l.m_value = config.m_tilt_l_mm/10.0;
    if(config.m_tilt){
        draw(m_tilt_l, Langage::getKey("RAPIDE_TILT_DISTANCE_SOC"));
        auto order = FrameworkVision::instance().m_lastOrder;
        QString qs = "correction : " + QString::number(order->m_deplacement_tilt_mm/10, 'f', 1) + " cm";
        drawQText(qs, m_x_middle, m_tilt_l.m_y+0.05*m_height2, sizeText_little, true);
        
    }
    
    if(!m_keypad_widget.m_close){
        m_keypad_widget.draw();
    }
}

void RapideOptionWidget::onMousePage4(int x, int y){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = f.m_config;
    
    if(m_auto_offset.isActive(x, y) && config.m_offset_auto_enable){
        config.m_offset_auto = !config.m_offset_auto;
    }
    
    if(config.m_offset_auto && config.m_offset_auto_enable){
        if(f.m_pilot_module.m_offset_i == 0){
            onMouse(m_valuegui_offset, x, y, 0.5);
        }
    } else {
        onMouse(m_valuegui_offset, x, y, 0.5);
    }
    
    if(config.m_offset_auto && config.m_offset_auto_enable){
        if(f.m_pilot_module.m_offset_i == 1){
            onMouse(m_valuegui_offset2, x, y, 0.5);
        }
    }
    
    if(config.m_offset_auto && config.m_offset_auto_enable){
        if(m_offset_change.isActive(x, y)){
            f.m_pilot_module.changeOffset();
        }
    }
    
    if(m_tilt.isActive(x, y)){
        config.m_tilt = !config.m_tilt;
    }
    
    onMouse(m_tilt_l, x, y);
    
    m_keypad_widget.onMouse(x, y);
    
    config.m_offset_mm = m_valuegui_offset.m_value*10;
    config.m_offset2_mm = m_valuegui_offset2.m_value*10;
    config.m_tilt_l_mm = m_tilt_l.m_value*10;
    
    loadConfig();
}


// Page 5
void RapideOptionWidget::setSizePage5(int width, int height){
    m_lamp.setResize(m_x_left, 0.3*m_height2, m_petit_button);
    m_camera_change.setResizeStd(m_x_middle, 0.55*m_height2, Langage::getKey("RAPIDE_CHANGE"), true);
    m_camera_auto.setResize(m_x_left, 0.7*m_height2, m_petit_button);
}

void RapideOptionWidget::drawPage5(){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = FrameworkVision::instance().m_config;
    
    drawText(Langage::getKey("RAPIDE_ECLAIRAGE"), m_x+m_width2/2,  m_lamp.m_y-0.1*m_height, sizeText_big, true);
    drawButtonCheck(m_lamp, f.m_lamp, Langage::getKey("RAPIDE_LED"));
    
    if(f.m_cameras_nbr > 1){
        drawText(Langage::getKey("RAPIDE_CAMERAS"), m_x+m_width2/2,  m_camera_change.m_y-0.1*m_height, sizeText_big, true);
        
        {
            QString qs = QString::fromStdString(Langage::getKey("RAPIDE_CAMERA")) + " " + QString::number(f.m_camera_selected+1) + " / " + QString::number(f.m_cameras_nbr);
            drawQText(qs, m_x_middle, m_camera_change.m_y+40, sizeText_little, true);
        }
        
        
        drawButtonLabel2(m_camera_change);
        drawButtonCheck(m_camera_auto, config.m_cameras_auto, Langage::getKey("RAPIDE_AUTO"));
    }
    
    //y+=inter;
}

void RapideOptionWidget::onMousePage5(int x, int y){
    FrameworkVision & f = FrameworkVision::instance();
    Config & config = FrameworkVision::instance().m_config;
    
    if(m_lamp.isActive(x, y)){
        ICommand * command = new CommandLamp();
        FrameworkVision::instance().addCommand(command);
    }
    
    if(f.m_cameras_nbr > 1){
        if(m_camera_change.isActive(x, y) != 0){
            int cam = (f.m_camera_selected + 1)%f.m_cameras_nbr;
            f.m_camera_selected = cam;
        }
        if(m_camera_auto.isActive(x, y)){
            config.m_cameras_auto = !config.m_cameras_auto;
            MainWidget::instance()->m_option_widget.loadConfig();
        }
    }
}


// Page 6
void RapideOptionWidget::setSizePage6(int width, int height){
    m_button_reset.setResizeStd(m_x_middle, 0.6*m_height2, Langage::getKey("RAPIDE_RESET"), true);
    m_button_diag.setResizeStd(m_x_middle, 0.7*m_height2, Langage::getKey("DIAGNOSTIC"), true);
}

void RapideOptionWidget::drawPage6(){
    FrameworkVision & f = FrameworkVision::instance();
    drawText(Langage::getKey("RAPIDE_COUNTER"), m_x+m_width2/2, m_y_title, sizeText_big, true);
    
    int y = 0.25*m_height2;
    int inter = 0.04*m_height2;;
    
    {
        drawText(Langage::getKey("RAPIDE_TOTAL"), m_x1, y, sizeText_medium);
        QString qs = QString::number(f.m_qt_compteur_heure.m_heure_total, 'f', 1) + " h";
        drawQText(qs, m_x2, y, sizeText_medium);
    }
    y+=inter;
    
    {
        QString qs = QString::number(f.m_qt_compteur_heure.m_ha_total, 'f', 1) + " ha";
        drawQText(qs, m_x2, y, sizeText_medium);
    }
    y+=2*inter;
    
    {
        drawText(Langage::getKey("RAPIDE_PARTIAL"), m_x1, y, sizeText_medium);
        QString qs = QString::number(f.m_qt_compteur_heure.m_heure_partiel, 'f', 1) + " h";
        drawQText(qs, m_x2, y, sizeText_medium);
    }
    y+=inter;
    {
        QString qs = QString::number(f.m_qt_compteur_heure.m_ha_partiel, 'f', 1) + " ha";
        drawQText(qs, m_x2, y, sizeText_medium);
    }
    y+=2*inter;
    
    {
        drawText(Langage::getKey("RAPIDE_SESSION"), m_x1, y, sizeText_medium);
        QString qs = QString::number(f.m_qt_compteur_heure.m_heure_session, 'f', 1) + " h";
        drawQText(qs, m_x2, y, sizeText_medium);
    }
    y+=inter;
    {
        QString qs = QString::number(f.m_qt_compteur_heure.m_ha_session, 'f', 1) + " ha";
        drawQText(qs, m_x2, y, sizeText_medium);
    }
    
    if(f.m_config.m_vitesse_type == VitesseType_GPS){
        y = 0.8*m_height2;
        drawText(Langage::getKey("RAPIDE_GPS"), m_x+m_width2/2, y, sizeText_big, true);
        y+=inter;
        QString qs = QString::number(f.m_gps_vitesse, 'i', 0) + " " + QString::fromStdString(Langage::getKey("RAPIDE_SATELLITES"));
        drawQText(qs, m_x+m_width2/2, y, sizeText_medium, true);
    }
    
    drawButtonLabel2(m_button_reset);
    drawButtonLabel2(m_button_diag);
}

void RapideOptionWidget::onMousePage6(int x, int y){
    FrameworkVision & f = FrameworkVision::instance();
    if(m_button_reset.isActive(x, y) != 0){
        f.m_qt_compteur_heure.resetPartiel();
    }
    if(m_button_diag.isActive(x, y) != 0){
        MainWidget::instance()->m_diagnostic_widget.open();
    }
}


//Page7
void RapideOptionWidget::drawPage7(){
    drawQText("Temps", m_x+m_width2/2, m_y_title, sizeText_big, true);
    
    int y = m_y_title+40;
    int inter = 20;
    
    
    
    FrameworkVision & f = FrameworkVision::instance();
    
    for(size_t i = 0; i < f.m_cameras_nbr; ++i){
        TimeObserver & t = f.m_visionModule.getTimeObserver(i);
        QString qs = "camera " +  QString::number(i+1)+ " : " + QString::number(t.m_moy, 'f', 1) + " ms";
        drawQText(qs, m_x1, y, sizeText_little, false);
        y+=inter;
    }
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    
    QString qs = "camera 1 timer : " + QString::number(f.m_camera1_timer.m_moy, 'f', 1) + " ms";
    drawQText(qs, m_x1, y, sizeText_little, false);
    y+=inter;
    qs = "camera 2 timer : " + QString::number(f.m_camera2_timer.m_moy, 'f', 1) + " ms";
    drawQText(qs, m_x1, y, sizeText_little, false);
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    qs = "cameras timer : " + QString::number(f.m_cameras_timer.m_moy, 'f', 1) + " ms";
    drawQText(qs, m_x1, y, sizeText_little, false);
    y+=inter;
    qs = "     charge : " + QString::number(f.getChargeThread(), 'f', 1) + " %";
    drawQText(qs, m_x1, y, sizeText_little, false);
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    
    
    Image_ptr image = f.m_lastImage;
    auto order = f.m_lastOrder;
    {
        QString qs = "camera : " + QString::number(image->m_timeImgOrigin);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    
    {
        QString qs = "blackAndWhite : " + QString::number(image->m_timeBlackAndWhite-image->m_timeImgOrigin);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    
    {
        QString qs = "blackAndWhite filter : " + QString::number(image->m_timeBlackAndWhiteFiltered-image->m_timeBlackAndWhite);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    
    {
        QString qs = "decision1 : " + QString::number(image->m_timeDecisionModule1-image->m_timeBlackAndWhiteFiltered);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    
    {
        QString qs = "print : " + QString::number(image->m_timePrint-image->m_timeDecisionModule1);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    
    {
        QString qs = "total : " + QString::number(image->m_timePrint);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    drawQText("cam 1 : " + QString::number(f.m_images[0]->m_deplacement_mm/10, 'f', 1) + " cm , (" + QString::number(f.m_images[0]->m_deplacement_ang_deg, 'f', 1) + " °)", m_x1, y, sizeText_little, false);
    y+=inter;
    if(f.m_cameras_nbr > 1){
        drawQText("cam 2 : " + QString::number(f.m_images[1]->m_deplacement_mm/10, 'f', 1) + " cm , (" + QString::number(f.m_images[1]->m_deplacement_ang_deg, 'f', 1) + " °)", m_x1, y, sizeText_little, false);
    } else {
        drawQText("cam 2 : -- ", m_x1, y, sizeText_little, false);
    }
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    
    {
        QString qs = "order  : cam " + QString::number(order->m_camera + 1);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = QString::number(order->m_deplacement_mm/10, 'f', 1) + " cm , (" + QString::number(order->m_angle_rad/3.14*180, 'f', 1) + " °)";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = "offset deg: " + QString::number(order->m_deplacement_tilt_mm/10, 'f', 1) + " cm";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = "offset : " + QString::number(order->m_offset_mm/10, 'f', 1)  + " cm";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = "offset cam : " + QString::number(order->m_offset_cam_mm/10, 'f', 1)  + " cm";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = "=> : " + QString::number(f.m_pilot_module.m_deplacement_mm/10, 'f', 1)  + " cm";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    {
        QString qs = "mesured : " + QString::number(order->m_deplacement_measured_mm/10, 'f', 1);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = "=> des : " + QString::number(f.m_pilot_module.m_pas_desired_mm/10, 'f', 1);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    
    
}

void RapideOptionWidget::drawPage8(){
    FrameworkVision & f = FrameworkVision::instance();
    drawQText("Debug", m_x+m_width2/2, m_y_title, sizeText_big, true);
    //m_painter->setPen(m_pen_black_inv);
    int y = m_y_title+40;
    int inter = 20;
    
    
    /*{
        QString qs = "image : " + QString::number(round(f.m_camera_timer.m_moy))+ " ms ";;
        drawQText(qs, m_x2, y, sizeText_little, false);
    }
    
    y+=inter;
    {
        QString qs = "capteur : " + QString::number(round(f.m_pilot_module.m_capteur_timer.m_moy))+ " ms ";;
        drawQText(qs, m_x2, y, sizeText_little, false);
    }*/
    
    {
        if(f.m_pilot_module.m_pilot_time.isConnected()){
            drawQText("ok_serial", m_x1, y, sizeText_little, false);
        } else {
            drawQText("error_serial", m_x1, y, sizeText_little, false);
        }
    }
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    drawText(f.m_pilot_module.m_last_serial, m_x1, y, sizeText_little, false);
    y+=inter;
    drawText(f.m_pilot_module.m_last_order_send, m_x1, y, sizeText_little, false);
    
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    std::string s = "";
    switch(f.m_pilot_module.m_etat){
        case SerialEtat_Off:
            s="off";
            break;
        case SerialEtat_Temp:
            s="temp";
            break;
        case SerialEtat_Pas:
            s="pas";
            break;
    }
    if(f.m_pilot_module.m_stop){
        s+= " Stop";
    }
    drawText(s, m_x1, y, sizeText_little, false);
    y+=inter;
    
    {
        QString qs = "alive : " + QString::number(f.m_pilot_module.m_time_end_stop_all.time_since_epoch().count()) + " ms";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    

    if(f.m_config.m_algo_command == TypeAlgoCommand_Temp){
        QString qs = "cmd en temps : " + QString::number(f.m_lastOrder->m_timeOrder) + " ms";
        drawQText(qs, m_x1, y, sizeText_little, false);
        y+=inter;
    } else {
        {
            QString qs = "pas : " + QString::number(f.m_pilot_module.m_pas_mesured_2);
            drawQText(qs, m_x1, y, sizeText_little, false);
        }
        y+=inter;
        {
            QString qs = "mm : " + QString::number(f.m_pilot_module.m_pas_mesured_mm);
            drawQText(qs, m_x1, y, sizeText_little, false);
        }
        y+=inter;
        {
            QString qs = "mm liss : " + QString::number(f.m_pilot_module.m_pas_mesured_mm_liss);
            drawQText(qs, m_x1, y, sizeText_little, false);
        }
        y+=inter;
    }
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;

    {
        QString qs = "3eme point : " + QString::number(f.m_pilot_module.m_point_3);;
        drawQText(qs, m_x1, y, sizeText_little, false);
        
    }
    y+=inter;
    {
        QString qs = "  config : " + QString::number(f.m_pilot_module.m_command_auto_0_3point); + "=> : " + QString::number(f.m_pilot_module.go3emPoint());
        drawQText(qs, m_x1, y, sizeText_little, false);
        
    }
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    {
        QString qs = "capteur roue : " + QString::number(f.m_pilot_module.m_pulse_time_ms) + " ms ";
        drawQText(qs, m_x1, y, sizeText_little, false);
        //y+=inter;
    }
    y+=inter;
    {
        QString qs = "capteur roue liss : " + QString::number(f.m_pilot_module.m_pulse_time_ms_liss) + " ms ";
        drawQText(qs, m_x1, y, sizeText_little, false);
        //y+=inter;
    }
    y+=inter;
    {
        
        QString qs = "vitesse km/h : " + QString::number(f.m_current_vitesse) + " km/h ";
        drawQText(qs, m_x1, y, sizeText_little, false);
        //y+=inter;
    }
    
    y+=inter;
    drawQText("---", m_x1, y, sizeText_little, false);
    y+=inter;
    {
        QString qs = "m_pas_desired_mm  : " + QString::number(f.m_pilot_module.m_pas_desired_mm);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = "m_pas_desired2_mm  : " + QString::number(f.m_pilot_module.m_pas_desired2_mm);
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
    y+=inter;
    {
        QString qs = " ( max mm/s  : " + QString::number(f.m_pilot_module.m_command_capteur_vitesse_max_mm_s) + " )";
        drawQText(qs, m_x1, y, sizeText_little, false);
    }
}

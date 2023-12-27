#pragma once

#include "base/base_widget.hpp"
#include "base/keyboard_widget.hpp"

class Config;

class RapideOptionWidget : public BaseWidget {
    KeyPadWidget m_keypad_widget;
public:
    int m_x = 0;
    int m_width2 = 0;
    int m_x_middle = 0;
    int m_x_left = 0;
    int m_x1 = 0;
    int m_x2 = 0;
    int m_y = 0;
    int m_height2 = 0;
    int m_y_title = 0;
    
    int m_page = 1;
    int m_nbr_page = 8;
    
    ButtonGui m_button_close;
    ButtonGui m_button_next;
    
    
    RapideOptionWidget();

    void loadConfig();
    void resetConfig();
    
    void open();
    
    void setPainter(QPainter * p){
        m_painter = p;
        m_keypad_widget.setPainter(p);
    }
    void setSize(int width, int height);
    void loadImages();
    void draw();
    int onMouse(int x, int y);
    
    QString m_avance_label_av = "";
    QString m_avance_label_re = "";
    ButtonGui m_avanced_bw;
    bool m_avance_black_white = false;
    
    //page1
    double m_value;
    ValueGui m_valuegui_red;
    ButtonGui m_coeff_0;
    ButtonGui m_coeff_1;
    ButtonGui m_coeff_2;
    ButtonGui m_coeff_3;
    ButtonGui m_coeff_4;
    
    ButtonGui m_contrast_0;
    ButtonGui m_contrast_1;
    ButtonGui m_contrast_2;
    ButtonGui m_contrast_3;
    ButtonGui m_contrast_4;
    
    
    ValueGui m_valuegui_contraste;
    void setSizePage1(int width, int height);
    void drawPage1();
    void onMousePage1(int x, int y);
    
    //page2
    ValueGui m_valuegui_distance_image_mm;
    ValueGui m_valuegui_angle;
    
    ValueGui m_valuegui_hauteur_mm;
    ValueGui m_valuegui_h_angle;
    
    ValueGui m_distance1_mm;
    ValueGui m_distance2_mm;
    
    ValueGui m_valuegui_nbr_rang;
    ValueGui m_valuegui_inter;
    ValueGui m_valuegui_epaisseur;
    ValueGui m_valuegui_score_min;
    
    ButtonGui m_ajust;
    ButtonGui m_avanced_pt;
    
    
    ButtonGui m_ajust_yes;
    ButtonGui m_ajust_no;
    
    void setSizePage2(int width, int height);
    void drawPage2();
    void onMousePage2(int x, int y);
    
    //page3
    ButtonGui m_calcul;
    int m_culture_developpement = 0;
    ButtonGui m_lum0;
    ButtonGui m_lum1;
    ButtonGui m_lum2;
    ButtonGui m_lum3;
    
    void setSizePage3(int width, int height);
    void drawPage3();
    void onMousePage3(int x, int y);
    
    //page4
    ButtonGui m_auto_offset;
    ValueGui m_valuegui_offset;
    ValueGui m_valuegui_offset2;
    ButtonGui m_offset_change;
    ButtonGui m_tilt;
    ValueGui m_tilt_l;
    void setSizePage4(int width, int height);
    void drawPage4();
    void onMousePage4(int x, int y);
    
    void draw(ValueGui & keypad, std::string);
    void drawFalse(ValueGui & keypad, std::string);
    void onMouse(ValueGui & keypad, double x, double y, double pas = 1.0);
    
    //page5
    ButtonGui m_camera_change;
    ButtonGui m_camera_auto;
    ButtonGui m_lamp;
    void setSizePage5(int width, int height);
    void drawPage5();
    void onMousePage5(int x, int y);
    
    //page5
    ButtonGui m_button_reset;
    ButtonGui m_button_diag;
    ValueGui m_largeur;
    void setSizePage6(int width, int height);
    void drawPage6();
    void onMousePage6(int x, int y);
    
    
    void drawPage7();
    void drawPage8();
};

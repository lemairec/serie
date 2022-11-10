#ifndef OPTION_WIDGET
#define OPTION_WIDGET

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"

class OptionWidget : public BaseWidget {
    QPixmap * m_imgClose;
    QPixmap * m_imgPlus;
    QPixmap * m_imgMinus;
    
    QPixmap * m_imgSatBlanc;
    QPixmap * m_imgSatGris;
    QPixmap * m_imgVolantBlanc;
    QPixmap * m_imgVolantGris;
    QPixmap * m_imgOutilBlanc;
    QPixmap * m_imgOutilGris;
    QPixmap * m_imgOptionBlanc;
    QPixmap * m_imgOptionGris;
    QPixmap * m_imgImuBlanc;
    QPixmap * m_imgImuGris;
    
    QPixmap * m_img_off;
    QPixmap * m_img_return;
    
    
    ButtonGui m_button_close;
    ButtonGui m_button_ok;
    
    ButtonGui m_button_p1;
    ButtonGui m_button_p2;
    ButtonGui m_button_p3;
    ButtonGui m_button_p4;
    ButtonGui m_button_p5;
    ButtonGui m_button_p6;
    
    int m_page = 1;
    
    void addSerials();
    
    void drawPart2(double y, double h, std::string title);
    void drawPart1(double y, double h, std::string title);
    
    
    
    int m_x2, m_y2, m_width2, m_height2;
    int m_width3, m_y_title, m_y_begin, m_y_inter;
    int m_part_1_x, m_part_1_w, m_part_1_x2, m_part_1_x3, m_part_2_x, m_part_2_w, m_part_2_x2, m_part_2_x3;
    
    SelectWidget m_select_widget;
public:
    OptionWidget();
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    virtual void setPainter(QPainter * p){
        m_select_widget.setPainter(p);
        m_painter = p;
    }
    
    //page_imu
    SelectButtonGui m_select_serial;
    SelectButtonGui m_select_baudrates;
    
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
    
    //page2
    SelectButtonGui m_select_gps_serial;
    SelectButtonGui m_select_gps_baudrates;
    
    SelectButtonGui m_lissage_gps;
    ValueGui m_lissage_gps_ekf;
    
    SelectButtonGui m_cap;
    ValueGui m_cap_ekf;
    ValueGui m_cap_d;
    
    ButtonGui m_correction_lateral_imu;
    
    void resizePage2();
    void onMousePage2(int x, int y);
    void drawPage2();
    
    //page3
    SelectButtonGui m_select_pilot_serial;
    SelectButtonGui m_select_pilot_baudrates;
    SelectButtonGui m_select_pilot_langage;
    
    SelectButtonGui m_select_algo;
    ValueGui m_value_gui_lookahead_d;
    ValueGui m_value_gui_rwp_kth;
    ValueGui m_value_gui_rwp_kte;
    
    ButtonGui m_button_adaptive_vitesse;
    
    void resizePage3();
    void onMousePage3(int x, int y);
    void drawPage3();
    
    //page4
    ButtonGui m_button_sens;
    ButtonGui m_button_debug;
    ButtonGui m_button_auto;
    ButtonGui m_button_debug_file;
    ButtonGui m_button_menu_vertical;
    
    void resizePage4();
    void onMousePage4(int x, int y);
    void drawPage4();
    
    //page5
    ButtonGui m_button_encoder_inverse;
    ButtonGui m_button_motor_inverse;
     
    ValueGui m_motor_vitesse_agressivite;
    ValueGui m_motor_vitesse_max;
    
    ValueGui m_volant_pas_by_tour;
    ValueGui m_volant_angle_by_tour;
    ValueGui m_volant_derive;
    
    ValueGui m_volant_frequence;
    ValueGui m_virtual_point;
    
    ValueGui m_button_auto_deactive;
    ValueGui m_button_auto_active;
       
    
    void resizePage5();
    void onMousePage5(int x, int y);
    void drawPage5();
    
    
    
    //page_imu
    
    void resizePage6();
    void onMousePage6(int x, int y);
    void drawPage6();
    
    void open();
    
    
    void drawButtonOption(ButtonGui & button, QPixmap * image, bool check, double scale);
};

#endif

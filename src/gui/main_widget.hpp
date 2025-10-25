#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include "base/base_widget.hpp"
#include "option_widget.hpp"
#include "base/keyboard_widget.hpp"
#include "widget/harxon_widget.hpp"
#include "widget/nmea_widget.hpp"
#include "widget/gcode_widget.hpp"
#include "widget/cfg_widget.hpp"
#include "widget/can_widget.hpp"
#include "widget/search_widget.hpp"
#include "widget/log_widget.hpp"

class MainWidget : public BaseWidget {
    MainWidget();
public:
    static MainWidget * instance();
    
    OptionWidget m_option_widget;
    
    std::vector<BaseWidget *> m_widgets;
    
    KeyPadWidget m_key_pad_widget;
    KeyBoardWidget m_key_board_widget;
    KeyPadHexaWidget m_key_board_widget_hex;
    NMEAWidget m_gps_widget;
    GcodeWidget m_gcode_widget;
    CfgWidget m_cfg_widget;
    CanWidget m_can_widget;
    SearchWidget m_search_widget;
    LogWidget m_log_widget;
    
    
    int m_widthMax;
    int m_heightMax;

    QPixmap * m_imgMenu;
    
    
    ButtonGui m_button_setting;
    ButtonGui m_button_gps;
    ButtonGui m_button_can;
    ButtonGui m_button_search;
    ButtonGui m_button_log;
    ButtonGui m_button_gcode;
    ButtonGui m_button_cfg;
    ButtonGui m_buttonSendMessage;
    ButtonGui m_buttonSendMessagHex;
    ButtonGui m_buttonPosition;
    ButtonGui m_button_hexa;
    ButtonGui m_button_max;
    
    bool m_debug = false;
    
    void setPainter(QPainter * s);
    
    void loadImages();
    
    void draw();
    void draw_force();
    void drawButtons();
    void drawMessages();
    void drawCategories();

    
    void setSize(int width, int height);
    
    
    int onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

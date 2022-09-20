#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include "base/base_widget.hpp"
#include "option_widget.hpp"
#include "base/keyboard_widget.hpp"
#include "harxon_widget.hpp"

class MainWidget : public BaseWidget {
    MainWidget();
public:
    static MainWidget * instance();
    
    OptionWidget m_option_widget;
    HarxonWidget m_harxon_widget;
    MotorWidget m_motor_widget;
    BineuseWidget m_bineuse_widget;
    
    std::vector<BaseWidget *> m_widgets;
    
    KeyPadWidget m_key_pad_widget;
    KeyBoardWidget m_key_board_widget;
    
    std::vector<ButtonGui *> m_categories;
    
    int m_widthMax;
    int m_heightMax;

    QPixmap * m_imgMenu;
    
    
    ButtonGui m_buttonMenu;
    ButtonGui m_buttonMenu2;
    ButtonGui m_buttonMenu3;
    ButtonGui m_buttonMenu4;
    ButtonGui m_buttonSendMessage;
    ButtonGui m_buttonSaveLog;
    
    bool m_debug = false;
    
    void setPainter(QPainter * s);
    
    void draw();
    void draw_force();
    void drawButtons();
    void drawMenuRight();
    void drawMessages();
    void drawCategories();

    
    void setSize(int width, int height);
    
    
    int onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

#ifndef GPS_WIDGET_H
#define GPS_WIDGET_H

#include "base_widget.hpp"
#include "option_widget.hpp"
#include "menu_widget.hpp"
#include "keyboard_widget.hpp"

class GpsWidget : public BaseWidget {
    GpsWidget();
public:
    static GpsWidget * Instance();
    
    MenuWidget m_menuWidget;
    std::vector<BaseWidget *> m_widgets;
    
    KeyPadWidget m_key_pad_widget;
    KeyBoardWidget m_key_board_widget;
    
    
    int m_widthMax;
    int m_heightMax;

    QPixmap * m_imgMenu;
    
    
    ButtonGui m_buttonMenu;
    ButtonGui m_buttonSendMessage;
    
    bool m_debug = false;
    
    void setPainter(QPainter * s);
    
    void draw();
    void draw_force();
    void drawButtons();
    void drawMessages();

    
    void setSize(int width, int height);
    
    
    void mouseReleaseEvent ( QMouseEvent * event );
    
    void onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

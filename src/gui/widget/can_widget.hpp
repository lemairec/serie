#ifndef CAN_WIDGET_H
#define CAN_WIDGET_H

#include "../base/base_widget.hpp"
#include "../option_widget.hpp"
#include "../base/keyboard_widget.hpp"

class CanWidget : public BaseWidget {
    ButtonGui m_button_filtre_hexa;
    KeyPadHexaWidget m_keypad_hexa_widget;
public:
    CanWidget();

    void setSize(int width, int height);
    void setPainter(QPainter * painter);
    
    void drawMessagesCan();
    virtual void draw();
    virtual int onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

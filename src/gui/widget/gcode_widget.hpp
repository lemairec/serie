#ifndef GCODE_WIDGET_H
#define GCODE_WIDGET_H

#include "../base/base_widget.hpp"
#include "../option_widget.hpp"
#include "../base/keyboard_widget.hpp"

class GcodeWidget : public BaseWidget {
public:
    GcodeWidget();
    
    int m_x2, m_y2, m_width2, m_height2;
    
    ButtonGui m_go_home;
    ButtonGui m_stop;

    ButtonGui m_charger_outil;
    ButtonGui m_decharger_outil;
    
    ButtonGui m_one_action;
    ButtonGui m_many_actions;

    void setSize(int width, int height);
    virtual void draw();
    virtual int onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

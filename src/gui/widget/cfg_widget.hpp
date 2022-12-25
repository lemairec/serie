#ifndef CFG_WIDGET_H
#define CFG_WIDGET_H

#include "../base/base_widget.hpp"
#include "../option_widget.hpp"
#include "../base/keyboard_widget.hpp"

class CfgWidget : public BaseWidget {
    ValueGui m_lissage_ekf_xy;
    ValueGui m_lissage_ekf_cap;
    ValueGui m_lissage_ekf_a_cap;
    ValueGui m_lissage_ekf_v;
    ValueGui m_lissage_ekf_a_v;
    ValueGui m_lissage_ekf_roll;
    
    ButtonGui m_button_send;
public:
    CfgWidget();

    void setSize(int width, int height);
    
    void add(double x, double y, std::string label, std::string m_command);
    
    void drawAngle(double angle, const QString & s, const QColor &color);
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    void drawValueGui(ValueGui & value_gui, std::string s, double value);
    void onMouse(ValueGui & keypad, double x, double y, double pas);
};

#endif // GPS_WIDGET_H

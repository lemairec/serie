#ifndef NMEA_WIDGET_H
#define NMEA_WIDGET_H

#include "base/base_widget.hpp"
#include "option_widget.hpp"
#include "base/keyboard_widget.hpp"


class NMEAWidget : public BaseWidget {
public:
    NMEAWidget();

    void setSize(int width, int height);
    
    void add(double x, double y, std::string label, std::string m_command);
    virtual void draw();
    virtual int onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

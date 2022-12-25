#ifndef CAP_WIDGET_H
#define CAP_WIDGET_H

#include "../base/base_widget.hpp"
#include "../option_widget.hpp"
#include "../base/keyboard_widget.hpp"

class CapWidget : public BaseWidget {
public:
    CapWidget();

    void setSize(int width, int height);
    
    void add(double x, double y, std::string label, std::string m_command);
    
    void drawAngle(double angle, const QString & s, const QColor &color);
    virtual void draw();
    virtual int onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

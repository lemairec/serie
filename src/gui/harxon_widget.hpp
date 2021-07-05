#ifndef HARXON_WIDGET_H
#define HARXON_WIDGET_H

#include "base_widget.hpp"
#include "option_widget.hpp"
#include "menu_widget.hpp"
#include "keyboard_widget.hpp"

class SerieButton {
public:
    ButtonGui m_button;
    double m_x, m_y;
    std::string m_label;
    std::string m_command;
};

class BaseWidgetSerie : public BaseWidget {
    ButtonGui m_button_close;
    QPixmap * m_imgClose;
    std::vector<SerieButton*> m_buttons;
public:
    BaseWidgetSerie();

    void setSize(int width, int height);
    
    void add(double x, double y, std::string label, std::string m_command);
    virtual void draw();
    virtual void onMouse(int x, int y);
};

class HarxonWidget : public BaseWidgetSerie {
public:
    HarxonWidget();
};

class MotorWidget : public BaseWidgetSerie {
public:
    MotorWidget();
};
#endif // GPS_WIDGET_H

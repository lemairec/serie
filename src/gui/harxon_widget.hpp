#ifndef HARXON_WIDGET_H
#define HARXON_WIDGET_H

#include "base_widget.hpp"
#include "option_widget.hpp"
#include "menu_widget.hpp"
#include "keyboard_widget.hpp"

class HarxonWidget : public BaseWidget {
public:
    HarxonWidget();

    void setSize(int width, int height);
    
    virtual void draw();
    virtual void onMouse(int x, int y);
};

#endif // GPS_WIDGET_H

#ifndef LOG_WIDGET_H
#define LOG_WIDGET_H

#include "../base/base_widget.hpp"
#include "../option_widget.hpp"
#include "../base/keyboard_widget.hpp"

class LogWidget : public BaseWidget {
    
public:
    LogWidget();
    SelectWidget m_select_widget;
    
    ButtonGui m_button_search;
    ButtonGui m_button_close;
    
    SelectButtonGui m_select_logs;
    void open();
    void setSize(int width, int height);
    void setPainter(QPainter * painter);
    
    void drawMessagesCan();
    virtual void draw();
    virtual int onMouse(int x, int y);
};

#endif // SEARCH_WIDGET_H

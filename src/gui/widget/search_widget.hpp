#ifndef SEARCH_WIDGET_H
#define SEARCH_WIDGET_H

#include "../base/base_widget.hpp"
#include "../option_widget.hpp"
#include "../base/keyboard_widget.hpp"

class SearchWidget : public BaseWidget {
    ButtonGui m_button_search;
    ButtonGui m_button_close;
public:
    SearchWidget();

    void setSize(int width, int height);
    void setPainter(QPainter * painter);
    
    void drawMessagesCan();
    virtual void draw();
    virtual int onMouse(int x, int y);
};

#endif // SEARCH_WIDGET_H

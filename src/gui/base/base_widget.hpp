#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H

#include "component.hpp"

#define RAYON_ROUNDED 15

class BaseWidget{
public:
    QPainter * m_painter;
    
    QPen m_pen_black_inv;
    QPen m_penBlack;
    QPen m_penWhite;
    QPen m_penGray;
    QPen m_penRed;
    QPen m_penGreen;
    QPen m_penBlue;
    QPen m_penBlue2;
    QPen m_penNo;

    QBrush m_brushNo;
    QBrush m_brushWhite;
    QBrush m_brushWhiteAlpha;
    QBrush m_brushGreenAlpha;
    QBrush m_brushRed;
    QBrush m_brushOrange;
    QBrush m_brushBlue;
    QBrush m_brushGray;
    QBrush m_brushGreen;
    QBrush m_brushGreenButton;
    QBrush m_brushRedButton;
    
    QBrush m_brush_background_1;
    QBrush m_brushDarkGray;
    QBrush m_brushLightGrayDebug;
    QBrush m_brushGrayAlpha;
    
    QBrush m_brushParcelle;
    
    QBrush m_brushBackGround1;
    QBrush m_brushBackGround2;
    
    
    QPen m_penTracteurRoue;
    QBrush m_brushTracteur;
    QPen m_penOutil;
    QBrush m_brushOutil;
    
    QPixmap * m_img_check_on;
    QPixmap * m_img_check_off;
    
    QPixmap * m_img_plus;
    QPixmap * m_img_moins;
public:
    virtual void setPainter(QPainter * p){
        m_painter = p;
    }
public:
    bool m_black_mode = true;
    
    int m_gros_button = 10;
    int m_gros_gros_button = 10;
    int m_petit_button = 10;
    
    double m_width;
    double m_height;
    bool m_close = true;
    
    KeyPadWidget * m_key_pad_widget;
    KeyBoardWidget * m_key_board_widget;
    BaseWidget();
    
    virtual void draw() = 0;
        
    virtual int onMouse(int x, int y){return 0;};
    virtual void setSize(int width, int height);
    
    virtual void open();
    virtual bool isOpen();
    
    void drawButton(ButtonGui & button, int color = 0);
    void drawButtonCarre(ButtonGui & button, int color = 0);
    void drawButtonCheck(ButtonGui & button, bool check, const std::string & s);
    void drawButtonCheck(ButtonGui & button, bool check);
    void drawButtonLabel2(ButtonGui & button, int color = 0);
    void drawButtonImage(ButtonGui & button, QPixmap * pixmap, double scale=1.0);
    void drawButtonImageCarre(ButtonGui & button, QPixmap * pixmap, double scale=1.0, bool open = false);
    void drawButtonLabelCarre(ButtonGui & button, std::string s, double scale=1.0, bool open = false);
    void drawButtonValidate(ButtonGui & button);
    void drawButtonCancel(ButtonGui & button);

    void drawMyImage(QPixmap & pixmap, int x, int y, double scale, bool center);
    
    void drawLabel2(std::string s, double x, double y);

    void drawText(const std::string & text, int x, int y, SizeText = sizeText_little, bool center = false, bool white = false);
    void drawQText(const QString & text, int x, int y, SizeText = sizeText_little, bool center = false, bool white = false);
    void drawQTexts(const QString & text, int x, int y, SizeText = sizeText_little, bool center = false, bool white = false);
    
    void drawValueGuiKeyPad(ValueGui & value);
    void drawValueGuiKeyPad2(ValueGui & keypad);
    void drawValueGuiAndLabel(ValueGui & keypad, double value);
    bool isActiveValueGuiKeyPad(ValueGui & value, int x, int y);
    bool onMouseKeyPad2(ValueGui & keypad, double x, double y, double inter = 1.0);

    void drawValueGuiKeyBoard(ValueGuiKeyBoard & value);
    void drawValueGuiKeyBoardDisable(ValueGuiKeyBoard & value);
    bool isActiveValueGuiKeyBoard(ValueGuiKeyBoard & value, int x, int y);

    QPixmap * loadImage(const std::string & s);
    QPixmap * loadImageInv(const std::string & s);
};

#endif

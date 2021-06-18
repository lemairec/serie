#include "include_qt.hpp"
#include "../main_widget.hpp"

class MyWidget : public QWidget
{
  public:
    MainWidget * m_main_widget = NULL;
    MyWidget( QWidget *parent = 0 ) : QWidget( parent ) {}

    void paintEvent(QPaintEvent* e)
    {
        QWidget::paintEvent(e); // effectue le comportement standard

        QPainter painter(this); // construire
        //painter.setRenderHint(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        if(m_main_widget){
            m_main_widget->setPainter(&painter);
            m_main_widget->draw();
        }

    } // détruire
    
    void mouseReleaseEvent ( QMouseEvent * event );
};

class MainWindow : public QMainWindow
{
    MainWidget * m_main_widget;
    QTimer *m_timer;
    Q_OBJECT
    
    QWidget *centralWidget;
    explicit MainWindow(QWidget *parent = 0);
    
public:
    static MainWindow * Instance_ptr();
    MyWidget * m_my_widget;

    ~MainWindow();
    
    void test();
    void resizeEvent(QResizeEvent* event);

protected:
    void setupUi();
    void onNewPoint();
    void creerMenu();

signals:
    void onValueChangeSignal();

public slots:
    void onValueChangeSlot();
    void onTimerSlot();
    
    void openFile();

};

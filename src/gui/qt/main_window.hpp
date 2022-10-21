#include "include_qt.hpp"
#include "../main_widget.hpp"
#include "../../util/log.hpp"

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
    static MainWindow * instancePtr();
    MyWidget * m_my_widget;

    ~MainWindow();
    
    void test();
    void resizeEvent(QResizeEvent* event);

protected:
    void setupUi();
    void onNewPoint();
    void creerMenu();

    void keyPressEvent(QKeyEvent *event){
        if(!m_my_widget->m_main_widget->m_key_board_widget.m_close){
            if(event->key() == Qt::Key_Backspace){
                m_my_widget->m_main_widget->m_key_board_widget.removeLetter();
            } else{
                INFO("tata " << event->key());
                m_my_widget->m_main_widget->m_key_board_widget.addLetter(event->text());
            }
        } else {
            if(event->key() == Qt::Key_Escape){
                exit(1);
            } else if(event->key() == Qt::Key_Q){
                exit(1);
            }
        }
        
    }
    
    void keyReleaseEvent(QKeyEvent *event){
        INFO("tutu");
    }
    
signals:
    void onValueChangeSignal();

public slots:
    void onValueChangeSlot();
    void onTimerSlot();
    
    void openFile();
    void quitFullScreen();
    
};

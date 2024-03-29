#include "main_window.hpp"
#include "../option_widget.hpp"
#include "../../util/directory_manager.hpp"
#include "../../framework.hpp"

#include <QGridLayout>
#include <QTabWidget>
#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QResizeEvent>

#include <QTimer>
#include <QFileDialog>
#include "environnement.hpp"

void MyWidget::mouseReleaseEvent ( QMouseEvent * event ){
    if(m_main_widget){
        int x = event->x();
        int y = event->y();
        
        m_main_widget->onMouse(x, y);
    }
}

void MyWidget::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e); // effectue le comportement standard

    QPainter painter(this); // construire
    //painter.setRenderHint(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if(m_main_widget){
        m_main_widget->setPainter(&painter);
        m_main_widget->draw();
    }
}




MainWindow * MainWindow::instancePtr(){
    static MainWindow gf;
    return &gf;
}

MainWindow::MainWindow(QWidget *parent)
:QMainWindow(parent)
{
    DEBUG("begin");
    m_timer = new QTimer(this);
    m_timer->start(200);
    

    
    
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerSlot()));
    
    connect(this, SIGNAL(onValueChangeSignal()), this, SLOT(onValueChangeSlot()));
    
    setupUi();
    DEBUG("end");
    
}

MainWindow::~MainWindow()
{
    //GpsFramework::Instance().removeObserver();
}

void MainWindow::setupUi(){
    DEBUG("begin");
    if (this->objectName().isEmpty()){
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }
    this->resize(800, 480);
    
    m_my_widget = new MyWidget();
    m_main_widget = MainWidget::instance();
    m_my_widget->m_main_widget = m_main_widget;
    m_my_widget->m_main_widget->setSize(800, 480);
    

    //m_my_widget->setupUi();
    this->setCentralWidget(m_my_widget);
    
    
    Framework & f = Framework::Instance();
    if(f.m_config.m_fullscreen){
        showFullScreen();
    }
    
    
    //showMaximized();
    DEBUG("end");
}

void MainWindow::quitFullScreen(){
    showNormal();
}

//debug
//m_view->scene->setSceneRect(0, 0, width-10, height-10);
void MainWindow::resizeEvent(QResizeEvent *event){
    DEBUG("begin");
    int width = event->size().width();
    int height = event->size().height();
    m_main_widget->setSize(width, height);
    //m_gpsWidget->resizeEvent(event);
    DEBUG("end");
}

void MainWindow::onNewPoint(){
    DEBUG("begin");
    onValueChangeSlot();
    DEBUG("end");
}

void MainWindow::onValueChangeSlot(){
    DEBUG("begin");
    //m_view->m_gpsWidget->draw();
    DEBUG("end");
}

void MainWindow::onTimerSlot(){
    DEBUG("begin");
    m_my_widget->update();
    //m_view->m_gpsWidget->draw();
    DEBUG("end");
}

void MainWindow::creerMenu()
{
    DEBUG("begin");
    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction("open File", this, SLOT(openFile()));
    DEBUG("end");
}

void MainWindow::openFile(){
    DEBUG("begin");
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Address Book"), QString::fromStdString(DirectoryManager::instance().getSourceDirectory())+QString("/gps_samples"),
                                                    tr("Gps files (*.ubx)"));
    
    /*GpsFramework & f = GpsFramework::Instance();
    f.m_config.m_file_gps = fileName.toUtf8().constData();
    f.m_config.m_input_gps = "file";
    f.initOrLoadConfig();
    DEBUG("end");*/
}


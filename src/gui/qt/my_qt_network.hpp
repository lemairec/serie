#ifndef NETWORK_QT_H
#define NETWORK_QT_H

/*
#include <QtSerialPort/QSerialPort>

#include "../../config/config.hpp"
#include <QTextStream>
#include <QByteArray>
#include <QObject>
#include <QTimer>
#include <QtNetwork>

QT_USE_NAMESPACE


class MyQTNetwork : public QObject{
    Q_OBJECT
    
    QString m_host_url;
    
    MyQTNetwork();
   
    
public:
    static MyQTNetwork * Instance_ptr();
    
    bool m_is_connected = false;
    
    void initOrLoad(Config & config);
    void closeAll();
    
    void test();
    void test_camera();
    
    QString m_camera_30_url;
    bool m_camera_30_connected = false;
    QString m_camera_31_url;
    bool m_camera_31_connected = false;
    
private slots:
    
    void handleNetwork(QNetworkReply *reply);
    void handleErrorGps(QSerialPort::SerialPortError error);
};*/


#endif

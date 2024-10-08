#ifndef SERIAL_QT_H
#define SERIAL_QT_H

#include <QtSerialPort/QSerialPort>

#include "../../config/config.hpp"
#include <QTextStream>
#include <QByteArray>
#include <QObject>
#include <QTimer>

QT_USE_NAMESPACE

struct SerialSearch {
    QSerialPort m_serial_port;
    std::string m_serial_s;
    std::string m_data_s;
};

class MyQTSerialPorts : public QObject{
    Q_OBJECT
    
    std::string m_serial;
    QSerialPort m_serialPort;
    
    
    std::vector<std::string> m_serials;
    
    int m_pilot_langage = 0;
public:
    int m_serial_searchs_i = 0;
    std::map<std::string, SerialSearch *> m_serial_searchs;
    
    std::string m_last_error = "";
    
    MyQTSerialPorts();
    
    void initOrLoad(Config & config);
    void closeAll();
    
    void writeGpsSerialS(const std::string & l);
    
    bool pilotIsOpen(){return m_serialPort.isOpen();};
    void writePilotSerialD(std::vector<unsigned char> & l);
    void writePilotSerialDAndWait(std::vector<unsigned char> & l);
    void writePilotSerialS(const std::string & l);
    
    bool imuIsOpen(){return m_serialPort.isOpen();};
    
    void searchBegin();
    void setRecherche();
    void ecrireRecherche();
    void analyseRecherche();
    
    void addSerialPorts(std::string s);
    std::vector<std::string> & getAvailablePorts(bool all_tty);
private slots:
    void handleReadyReadGps();
    void handleErrorGps(QSerialPort::SerialPortError error);
    
    void handleReadyReadPilot();
    void handleErrorPilot(QSerialPort::SerialPortError error);

    void handleReadyReadImu();
    void handleErrorImu(QSerialPort::SerialPortError error);

private:
    QTimer m_timerPilot;
    QTimer m_timer100ms;
private slots:
    
    void handlePilot();
    void handle100Ms();
};


#endif

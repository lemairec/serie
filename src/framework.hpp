#ifndef GPS_FRAMEWORK_H
#define GPS_FRAMEWORK_H

#include "gui/qt/my_qt_serial_port.hpp"
#include "gui/qt/my_qt_file.hpp"
#include "config/config.hpp"
#include "gps/nmea_parser.hpp"
#include <chrono>
#include <QThread>
#include <time.h>
#include <math.h>
#include "util/stat.hpp"
#include "util/log.hpp"

class IGpsObserver {
public:
    virtual void onNewPoint() = 0;
};

class Framework {
    Framework();
    
    void saveInfoFile();
public:
    bool m_gps = false;
    bool m_can = false;
    NmeaParser m_nmea_parser;
    
    
    static Framework & Instance();
    ~Framework();
    void initOrLoadConfig();

    std::string m_messages_errors;
    void addError(std::string s);
    
    std::list<std::string> m_messages_serial;
    void addSerialMessage(std::string s);
    std::string m_message = "";
    void addSerialString(const std::string & s);
    void addSerialChar(char c);
    
    void sendMessages(const std::string & m);
    
    Config m_config;
    bool m_save_log;
    void changeSaveLog();
    
    MyQTSerialPorts m_serial_port;
    MyQTFile m_file;
private:
    void readFile();
};

#endif // GPS_FRAMEWORK_H

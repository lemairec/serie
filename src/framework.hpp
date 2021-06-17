#ifndef GPS_FRAMEWORK_H
#define GPS_FRAMEWORK_H

#include "gui/qt/my_qt_serial_port.hpp"
#include "config/config.hpp"
#include <chrono>
#include <QThread>
#include <time.h>
#include <math.h>
#include "logging.hpp"
#include "util/stat.hpp"

class IGpsObserver {
public:
    virtual void onNewPoint() = 0;
};

class Framework {
    Framework();
    
    void saveInfoFile();
public:
    static Framework & Instance();
    ~Framework();
    void initOrLoadConfig();

    std::string m_messages_errors;
    void addError(std::string s);
    
    std::list<std::string> m_messages_serial;
    void addSerialMessage(std::string s);
    std::string m_message = "";
    void addSerialChar(char c);
    
    Config m_config;
    
    MyQTSerialPorts m_serial_port;
private:
    void readFile();
};

#endif // GPS_FRAMEWORK_H

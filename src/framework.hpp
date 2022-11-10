#ifndef GPS_FRAMEWORK_H
#define GPS_FRAMEWORK_H

#include "gui/qt/my_qt_serial_port.hpp"
#include "config/config.hpp"
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

class Categorie {
public:
    std::string m_begin;
    int m_count = 0;
    bool m_enable = true;
    std::string m_last = "";
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
    
    void addCategorie(std::string s);
    std::vector<Categorie*> m_categories;
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
private:
    void readFile();
};

#endif // GPS_FRAMEWORK_H

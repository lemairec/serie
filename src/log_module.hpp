#ifndef LOG_MODULE_H
#define LOG_MODULE_H

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

class LogModule {
public:
    bool m_log = false;
    std::vector<QString> m_logs;
    
    
    LogModule();
    void initOrLoad();
    
    void save();
    void load();
    
    void openLog(const std::string & f);
    
    void clearAll();
    
    void changeLog();
    void onChar(char c);
};

#endif // GPS_FRAMEWORK_H

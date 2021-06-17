#include "config.hpp"
#include <QString>
#include <QSettings>
#include "environnement.hpp"
#include "../logging.hpp"
#include "../util/directory_manager.hpp"

Config::Config(){
    m_serial = "none";
    m_baudrate = 115200;
}

void Config::save(){
    std::string s = CONFIG_FILE;
    QString path = QString::fromStdString(s);
    QSettings settings(path, QSettings::IniFormat);
    
     
    
    QString input_serial = QString::fromStdString(m_serial);
    settings.setValue("m_serial", input_serial);
    settings.setValue("m_baudrate", m_baudrate);
    settings.setValue("m_fullscreen", m_fullscreen);
}

void Config::load(){
    std::string s = CONFIG_FILE;
    QString qpath = QString::fromStdString(s);
    QSettings settings(qpath, QSettings::IniFormat);
    
    if(settings.contains("m_serial")){
        m_serial = settings.value("m_serial").toString().toUtf8().constData();
    }
    if(settings.contains("m_baudrate")){
        m_baudrate = settings.value("m_baudrate").toInt();
    }
    if(settings.contains("m_fullscreen")){
        m_fullscreen = settings.value("m_fullscreen").toBool();
    }
}

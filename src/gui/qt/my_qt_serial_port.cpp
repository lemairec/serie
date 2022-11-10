#include "my_qt_serial_port.hpp"
#include "include_qt.hpp"
#include <sstream>
#include <QMetaEnum>
#include <QSerialPortInfo>

#include "../main_widget.hpp"

#include "environnement.hpp"
#include "../../util/directory_manager.hpp"
#include "../../framework.hpp"

MyQTSerialPorts::MyQTSerialPorts(){
    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(handleReadyReadGps()));
    connect(&m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MyQTSerialPorts::handleErrorGps);
    
    connect(&m_timerPilot, SIGNAL(timeout()), this, SLOT(handlePilot()));
      
}
void MyQTSerialPorts::initOrLoad(Config & config){
    DEBUG("begin");

    INFO(m_serial << ", " << config.m_serial);
    //m_pilot_langage = config.m_pilot_langage;

    if(config.m_serial != "none" && config.m_serial != "file"){
        if(m_serial == config.m_serial && m_serialPort.isOpen()){
            INFO("gps port already open");
        } else {
            if(m_serialPort.isOpen()){
                m_serialPort.close();
            }
            m_serial = config.m_serial;
            m_serialPort.setPortName(QString::fromStdString(m_serial));
            m_serialPort.setBaudRate(config.m_baudrate);
            
            std::ostringstream oss;
            oss << "open : " << m_serial << " " << config.m_baudrate;
            std::string s = oss.str();
            INFO(s);
            Framework & f = Framework::Instance();
            f.addSerialString(s);
            
            if (!m_serialPort.open(QIODevice::ReadWrite)) {
                std::ostringstream oss;
                oss << "Failed error:" << m_serialPort.errorString().toUtf8().constData();
                std::string s = oss.str();
                f.addSerialString(s);
            } else {
                f.addSerialString("opened");
            }
        }
    }
    /*m_timerPilot.stop();
    m_timerPilot.start(1000/config.m_pilot_frequence);*/
    DEBUG("end");
};

void MyQTSerialPorts::closeAll(){
    INFO("###close all");
    if(m_serialPort.isOpen()){
        INFO("close gps");
        m_serialPort.close();
    }
}

void MyQTSerialPorts::handleReadyReadGps(){
    DEBUG("begin");
    QByteArray a = m_serialPort.readAll();
    Framework & f = Framework::Instance();
    for(int i = 0; i < (int)a.size(); ++i){
        f.addSerialChar((char)(a.data()[i]));
    }
    
    DEBUG("end");
}
void MyQTSerialPorts::handleErrorGps(QSerialPort::SerialPortError error){
    /*DEBUG("begin");
    if(error != 0){
        std::ostringstream oss;
        oss << "handleErrorGps " << error << ", error:" << m_serialPortGps.errorString().toUtf8().constData();
        //TODOGpsFramework::Instance().m_pilot_last_error = oss.str();
        //GpsFramework::Instance().addError(oss.str());
        WARN(error);
    }
    DEBUG("end");*/
}

void MyQTSerialPorts::handleReadyReadPilot(){
}
void MyQTSerialPorts::handleErrorPilot(QSerialPort::SerialPortError error){
}

/**
 IMU
 */

void MyQTSerialPorts::handleReadyReadImu(){
}
void MyQTSerialPorts::handleErrorImu(QSerialPort::SerialPortError error){
}



void MyQTSerialPorts::writeGpsSerialS(const std::string & l){
    if(m_serialPort.isOpen()){
        QByteArray b;
        b.append(l.c_str());
        m_serialPort.write(b);
    }
}


void MyQTSerialPorts::writePilotSerialD(std::vector<unsigned char> & l){
    /*DEBUG("begin");
    if(m_serialPortPilot.isOpen()){
        QByteArray b;
        for(long unsigned int i = 0; i < l.size(); ++i){
            b.append(l[i]);
        }
        m_serialPortPilot.write(b);
        QString hex(b.toHex());
    }
    
    DEBUG("end");*/
}

void MyQTSerialPorts::writePilotSerialDAndWait(std::vector<unsigned char> & l){
    DEBUG("begin");
    writePilotSerialD(l);
    
    DEBUG("end");
}

#include <QThread>
int i = 0;
void MyQTSerialPorts::rechercheAuto(){
    setRecherche();
//    GCVBHÙDÈ
    
}

void MyQTSerialPorts::setRecherche(){
    INFO("##0 open");
    closeAll();
    //TODOGpsFramework & f = GpsFramework::Instance();
    //TODOf.m_config.m_input_gps = "none";
    //TODOf.m_config.m_inputPilot = "none";
    //TODOf.initOrLoadConfig();
    auto serials = getAvailablePorts();
    m_serial_searchs.clear();
    for(auto s : serials){
        INFO("##0 " << s);
        auto serial_search = new SerialSearch();
        serial_search->m_serial_s = s;
        serial_search->m_serial_port.setPortName(QString::fromStdString(s));
        serial_search->m_serial_port.setBaudRate(115200);
        if (!serial_search->m_serial_port.open(QIODevice::ReadWrite)) {
            INFO("##0 " << "failed");
             std::ostringstream oss;
            oss << "Failed to open imu port " << s << ", error:" << serial_search->m_serial_port.errorString().toUtf8().constData();
            //TODOGpsFramework::Instance().addError(oss.str());
            //standardOutput << QObject::tr("Failed to open port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;//
        }
        m_serial_searchs[s] = serial_search;
        
    }
    m_serial_searchs_i = 1;
}

void MyQTSerialPorts::ecrireRecherche(){
    INFO("##1 ecrire");
    for(auto s : m_serial_searchs){
        auto serial_search = s.second;
        
        std::string s2 = "$P;\n$P;\n";
        QByteArray b;
        b.append(s2.c_str());
        serial_search->m_serial_port.write(b);
    }
    
}
void MyQTSerialPorts::analyseRecherche(){
    INFO("##2 analyse");
    std::string gps_port = "none";
    std::string pilot_port = "none";
    for(auto s : m_serial_searchs){
        auto serial_search = s.second;
        INFO(s.first << " " << serial_search->m_serial_port.isOpen());
        QByteArray b = serial_search->m_serial_port.readAll();
        QString hex(b);
        std::string data_s = hex.toUtf8().constData();
        if(data_s.size()>2){
            if(data_s.find("$GNGGA") !=std::string::npos){
                gps_port = serial_search->m_serial_s;
            } else if(data_s.find("$GPGGA") !=std::string::npos){
                gps_port = serial_search->m_serial_s;
            } else if(data_s.find("$P,") !=std::string::npos){
                pilot_port = serial_search->m_serial_s;
            } else {
                INFO(data_s);
            }
        }
        QByteArray b2 = serial_search->m_serial_port.readAll();
        
        INFO(data_s);
        INFO("toto " << b2.constData());
        s.second->m_serial_port.close();
    }
    
    
    INFO("##2 fin recherche");
    INFO("## gps_port " << gps_port);
    INFO("## pilot_port " << pilot_port);
    //TODOGpsFramework & f = GpsFramework::Instance();
    //TODOf.m_config.m_input_gps = gps_port;
    //TODOf.m_config.m_inputPilot = pilot_port;
    //TODOf.initOrLoadConfig();
    
}


#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

std::string execute3(std::string cmd){
    std::string file = DirectoryManager::Instance().getDataDirectory() + "/tmp_cmd";
    std::string cmd2 = cmd + " > " + file;
    system(cmd2.c_str());
    std::ifstream infile(file);
    std::stringstream strStream;
    strStream << infile.rdbuf();//read the file
    std::string res = strStream.str();
    return res;
}

void MyQTSerialPorts::addSerialPorts(std::string s){
    std::string res = execute3(s);
    std::vector<std::string> strs;
    boost::split(strs, res, boost::is_any_of("\n"));
    for(auto s : strs){
        if(!s.empty()){
            INFO(s);
            m_serials.push_back(s);
        }
    }
}

std::vector<std::string> & MyQTSerialPorts::getAvailablePorts(){
    m_serials.clear();
    addSerialPorts("ls /dev/cu.*");
    addSerialPorts("ls /dev/ttyACM*");
    addSerialPorts("ls /dev/ttymxc*");
    addSerialPorts("ls /dev/ttyUSB*");
    addSerialPorts("ls /dev/ttyS*");

    return m_serials;
}


void MyQTSerialPorts::handlePilot(){
    DEBUG("begin");
    //INFO("coucou je suis ici");
    
    if(m_pilot_langage == 0){
        //TODOGpsFramework::Instance().m_pilotModule.handleHadrien();
        //GpsFramework::Instance().m_pilotModule.update();
    } else {
        //TODOGpsFramework::Instance().m_pilotModule.handleArduino();
    }
    DEBUG("end");
    
    if(m_serial_searchs_i > 0){
        m_serial_searchs_i++;
        INFO(m_serial_searchs_i);
        if(m_serial_searchs_i == 500){
            ecrireRecherche();
        }
        if(m_serial_searchs_i > 1000){
            analyseRecherche();
            //MainWidget::instance()->m_menuWidget.m_close = true;
            m_serial_searchs_i = 0;
            
        }
    }
}

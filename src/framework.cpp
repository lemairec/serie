#include "framework.hpp"
#include "config/config.hpp"
#include "environnement.hpp"
#include "util/util.hpp"
#include "util/directory_manager.hpp"

#include <QDateTime>
#include <math.h>
#include <time.h>

std::string file_info;
std::ofstream file_job_stream;
std::ofstream file_debug_stream;
std::string date_str;

void makedir(std::string dir2){
    std::string dir = DirectoryManager::instance().getSourceDirectory() + dir2;
    std::string s2 = "mkdir -p "+ dir + ";";
    INFO(s2);
    if(system( s2.c_str() )){
        WARN("can not execute : " << s2);
    };
}

Framework::Framework(){
    QDateTime date = QDateTime::currentDateTime();
    QString s = date.toString("yyyyMMddThhmm");
    date_str = s.toUtf8().constData();
    
    int y = date.date().year();
    if(y>(1011+1011)){
    //    exit(0);
    }
    
    m_messages_serial.push_front("salut teuteu");
    
    makedir("/job");
    makedir("/parcelle");
    makedir("/line");
    
    m_log_module.initOrLoad();
    m_config.load();
}

void Framework::addSerialMessage(std::string s){
    m_messages_serial.push_front(s);
}

void Framework::changeSaveLog(){
    m_save_log = !m_save_log;
    if(m_save_log){
        m_log_module.changeLog();
    }
}

void Framework::addSerialString(const std::string & s){
    for(int i = 0; i < (int)s.size(); ++i){
        addSerialChar((char)(s[i]));
    }
    addSerialChar('\n');
}

void Framework::printMessage(){
    if(m_hexa){
        std::stringstream ss;
        ss << " hex3 - ";
        for(auto c : m_message){
            ss << " " << std::setw(2) << std::setfill('0') << std::hex << (int)((uchar)c);
        }
        m_messages_serial.push_front(ss.str());
        m_message="";
    } else{
        m_messages_serial.push_front(m_message);
    }
}

void Framework::addSerialChar(char c){
    m_number_receive++;
    if(m_max){
        if(m_message.length() > 20){
            printMessage();
            m_message="";
        }
    }
    //INFO(std::hex << (int)c)
    if(c == '\n'){ //0x0b
        printMessage();
        m_message="";
    } else {
        m_message+=c;
    }
    m_log_module.onChar(c);
    if(m_gps || m_can){
        m_nmea_parser.readChar(c);
    }
    
    if(m_hexa){
        m_hexa_parser.readChar(c);
    }
}

void Framework::sendMessages(const std::string & s){
    m_serial_port.writeGpsSerialS(s);
    std::string s2 = "===> " + s;
    addSerialMessage(s2);
}

void Framework::sendMessagesHexa(std::vector<unsigned char> & l){
    m_serial_port.writeGpsSerialD(l);
    std::stringstream ss;
    for(auto c : l){
        ss << " " << std::setw(2) << std::setfill('0') << std::hex << (int)((uchar)c);
    }
    std::string s2 = "hex => " + ss.str();
    addSerialMessage(s2);
}

void Framework::onCanMessage(CanFrame_ptr m_canFrame){
    if(m_frame_filter == 0 || m_frame_filter == m_canFrame->m_png){
        m_messages_can.push_front(m_canFrame->m_message);
    }
}



Framework & Framework::Instance(){
    static Framework gf;
    return gf;
}

Framework::~Framework(){
    m_serial_port.closeAll();
}

void Framework::initOrLoadConfig(){
    m_config.save();
    
    m_serial_port.initOrLoad(m_config);
    m_file.initOrLoad(m_config);
}

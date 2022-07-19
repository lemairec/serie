#include "framework.hpp"
#include "config/config.hpp"
#include "environnement.hpp"
#include "util/util.hpp"
#include "util/directory_manager.hpp"

#include <QDateTime>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string file_info;
std::ofstream file_job_stream;
std::ofstream file_debug_stream;
std::string date_str;

void makedir(std::string dir2){
    std::string dir = DirectoryManager::Instance().getSourceDirectory() + dir2;
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
    
    m_config.load();
    
    addCategorie("$GPGGA");
    addCategorie("$GPVTG");
    addCategorie("$GPRMC");
    addCategorie("$GPZDA");
    addCategorie("CSQ");
    
}

void Framework::addSerialMessage(std::string s){
    m_messages_serial.push_front(s);
}

void Framework::addCategorie(std::string s){
    Categorie *c = new Categorie();
    c->m_begin = s;
    m_categories.push_back(c);
    
}

std::ofstream m_logFile;
void Framework::changeSaveLog(){
    m_save_log = !m_save_log;
    if(m_save_log){
        std::string path = "logserial.txt";
        m_logFile.open(path);
        if(m_logFile.fail()){
            std::cerr << "open failure as expected: " << strerror(errno) << std::endl;
            std::cerr << "Warning File fail " << path << std::endl;
            exit(1);
        }
        m_logFile << "### begin ###" << std::endl;
        m_logFile << "#############" << std::endl;
    }
}

void Framework::addSerialChar(char c){
    if(c == '\n'){
        std::string s =m_message;
        m_message="";
        for(auto c : m_categories){
            bool same = true;
            for(int i = 0; i<c->m_begin.size(); ++i){
                if(i<s.size()){
                    if(c->m_begin[i] != s[i]){
                        same = false;
                    }
                } else {
                    same = false;
                }
            }
            if(same){
                c->m_count++;
                c->m_last = s;
                if(!c->m_enable){
                    return;
                }
                
            }
            
        }
        m_messages_serial.push_front(s);
        
    } else {
        m_message+=c;
    }
    if(m_save_log){
        m_logFile << c;
    }
}

void Framework::sendMessages(const std::string & s){
    m_serial_port.writeGpsSerialS(s);
    std::string s2 = "===> " + s;
    addSerialMessage(s2);
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
}

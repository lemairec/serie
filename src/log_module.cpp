#include "log_module.hpp"

#include "util/directory_manager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <QFile>
#include <QDateTime>
#include <QTextStream>

LogModule::LogModule(){
}

void LogModule::initOrLoad(){
    std::string path = DirectoryManager::instance().getDataDirectory() + "/logs";
    std::string s2 = "mkdir -p "+ path + ";";
    std::cout << s2 << std::endl;;
    if(system( s2.c_str() )){
        std::cerr << "*** can not execute : " << s2 << std::endl;;
    };
    load();
}

void LogModule::load(){
    std::string path = DirectoryManager::instance().getDataDirectory() + "/logs/logs.txt";
    QString fileName = QString::fromStdString(path);
    QFile inputFile(fileName);
    m_logs.clear();
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
           QString line = in.readLine();
           if(line.size() > 3){
               m_logs.push_back(line);
           }
       }
       inputFile.close();
    }
    
}

void LogModule::save(){
    std::string path = DirectoryManager::instance().getDataDirectory() + "/logs/logs.txt";
    QString fileName = QString::fromStdString(path);
    QFile qFile(fileName);
    if (qFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&qFile);
        for(auto l : m_logs){
            out << l << "\n";
        }
        qFile.close();
    }
}

std::ofstream m_logFile;
void LogModule::changeLog(){
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyyMMdd_hh_mm_ss");
    m_logs.push_back(formattedTime);
    save();
    m_log = true;
    
    std::string path = DirectoryManager::instance().getDataDirectory() + "/logs/" + formattedTime.toUtf8().constData() + ".txt";
    m_logFile.open(path);
    if(m_logFile.fail()){
        std::cerr << "open failure as expected: " << strerror(errno) << std::endl;
        std::cerr << "Warning File fail " << path << std::endl;
        exit(1);
    }
    m_logFile << "### begin m_save_log ###" << std::endl;
    m_logFile << "#############" << std::endl;
}

void LogModule::onChar(char c){
    if(m_log){
        m_logFile << c;
    }
}

void LogModule::clearAll(){
    std::string path = DirectoryManager::instance().getDataDirectory() + "/logs";
    std::string s2 = "rm -rf "+ path + ";";
    std::cout << s2 << std::endl;;
    if(system( s2.c_str() )){
        std::cerr << "*** can not execute : " << s2 << std::endl;;
    };
    load();
}

void LogModule::openLog(const std::string & f){
    std::string path = DirectoryManager::instance().getDataDirectory() + "/logs/" + f + ".txt";
    std::string s2 = "gedit "+ path + ";";
    std::cout << s2 << std::endl;;
    if(system( s2.c_str() )){
        std::cerr << "*** can not execute : " << s2 << std::endl;;
    };
}





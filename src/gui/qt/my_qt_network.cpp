#include "my_qt_network.hpp"
/*#include "include_qt.hpp"
#include "../../framework.hpp"
#include <sstream>
#include <QMetaEnum>
#include <QSerialPortInfo>

#include "environnement.hpp"
#include "../../util/directory_manager.hpp"

MyQTNetwork * MyQTNetwork::Instance_ptr(){
    static MyQTNetwork gf;
    return &gf;
}

QNetworkAccessManager * manager;
MyQTNetwork::MyQTNetwork(){
    manager = new QNetworkAccessManager();
    
    QObject::connect(manager, &QNetworkAccessManager::finished, this,&MyQTNetwork::handleNetwork);
    
    m_host_url = "https://maplaine.fr/lemca/ping";
    
    m_camera_30_url = "http://192.168.1.30";
    m_camera_31_url = "http://192.168.1.31";
}
void MyQTNetwork::initOrLoad(Config & config){
    //m_host_url = "http://localhost:4000";
};

void MyQTNetwork::closeAll(){
    INFO("###close all");
}

std::string m_name;
void MyQTNetwork::handleNetwork(QNetworkReply *reply) {
    if (reply->error()) {
        std::string error = reply->errorString().toUtf8().constData();
        WARN(error);
        if(reply->url() == m_host_url){
            INFO("lu2");
            m_is_connected = false;
        } else if (reply->url() == m_camera_30_url){
            INFO("lu2");
            m_camera_30_connected = false;
        } else if (reply->url() == m_camera_31_url){
            INFO("lu2");
            m_camera_31_connected = false;
        } else {
            WARN("pas bien");
        }
        return;
    } else {
        std::string s = reply->readAll().toStdString();
        INFO("la");
        if(reply->url() == m_host_url){
            INFO("la2");
            m_is_connected = true;
        } else if (reply->url() == m_camera_30_url){
            INFO("la3");
            m_camera_30_connected = true;
        } else if (reply->url() == m_camera_31_url){
            INFO("la4");
            m_camera_31_connected = true;
        } else {
            WARN("pas bien");
        }
    }
};



void MyQTNetwork::handleErrorGps(QSerialPort::SerialPortError error){
    
}

void MyQTNetwork::test(){
    QNetworkRequest request;

    QString url = m_host_url;
    INFO(url.toUtf8().constData());
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

    manager->get(networkRequest);
    
}

void MyQTNetwork::test_camera(){
    {
        QNetworkRequest request;

        QString url = m_camera_30_url;
        INFO(url.toUtf8().constData());
        QUrl serviceUrl = QUrl(url);
        QNetworkRequest networkRequest(serviceUrl);
        networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

        manager->get(networkRequest);
    }
    {
        QNetworkRequest request;

        QString url = m_camera_31_url;
        INFO(url.toUtf8().constData());
        QUrl serviceUrl = QUrl(url);
        QNetworkRequest networkRequest(serviceUrl);
        networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

        manager->get(networkRequest);
    }
}
*/

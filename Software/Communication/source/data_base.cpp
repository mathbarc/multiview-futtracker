#include "data_base.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <sstream>

DAOWrapper::DAOWrapper(QString host, QString user,
                       QString pass, QString db, int port)
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName(host);
    this->db.setUserName(user);
    this->db.setPassword(pass);
    this->db.setDatabaseName(db);
    this->db.setPort(port);

    if(!this->db.open())
    {
        throw std::string("Erro ao estabelecer conecção com o banco.");
    }
}

DAOWrapper::DAOWrapper(cv::FileNode node){

    QString host(((std::string)node["host"]).c_str());
    QString user(((std::string)node["user"]).c_str());
    QString pass(((std::string)node["pass"]).c_str());
    QString dbase(((std::string)node["db"]).c_str());
    int port = (int)node["port"];

    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName(host);
    this->db.setUserName(user);
    this->db.setPassword(pass);
    this->db.setDatabaseName(dbase);
    this->db.setPort(port);

    if(!this->db.open())
    {
        throw std::string(db.lastError().text().toStdString());
    }
}

DAOWrapper::~DAOWrapper()
{
    std::cout<<"~DAOWrapper"<<std::endl;
    if(this->db.isOpen())
    {
        this->db.commit();
        this->db.close();
    }
    std::cout<<"~DAOWrapper done"<<std::endl;
}

void DAOWrapper::persistPlayer(Player& player)
{
    std::stringstream query;
    query << "INSERT INTO PLAYERS(NAME,NUMBER) VALUES ("<<
             player.getName() <<", "<<player.getShirtNumber()<<")";

    QSqlQuery q(QString(query.str().c_str()));
    if(!q.isActive())
    {
        std::cout<<q.lastError().text().toStdString()<<std::endl;
    }

}




#include "dbmanager.h"
#include <QDebug>

bool DBManager::OpenDatabase(QString DBName)
{
    m_db->setDatabaseName(m_dbPath);
    qDebug() << "driver: " << m_db->isValid();// "QSQLITE");
    if (!m_db->open()) {
        qDebug() << "Error: can not open Database " + DBName << "path: " << m_dbPath;
        return false;
    }

    qDebug() << "Database " + m_db->databaseName() << " successfully opened";
    qDebug() << "driver: " << m_db->driverName() << " status is: " << m_db->isDriverAvailable("QSQLITE");

    return true;
}

bool DBManager::ExecuteQuery(QString queryText)
{
    return m_query.exec(queryText);
}

DBManager &DBManager::instance()
{
    static DBManager instance;
    return instance;
}

QSqlQuery DBManager::query() const
{
    return m_query;
}

DBManager::DBManager() :
    m_db{(new QSqlDatabase {QSqlDatabase::addDatabase("QSQLITE")})},
    m_dbPath{"/home/drago/.local/share/Application/TestDB"}
{}

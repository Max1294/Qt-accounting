#pragma once
#include <memory>
#include <QSqlDatabase>
#include <QString>

class ConnectionManager
{
public:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator =(const ConnectionManager&) = delete;
    ~ConnectionManager();

//    bool isValid() const;
    bool openDatabase(QString DBName);
    static ConnectionManager& instance();
private:
    ConnectionManager();
    std::unique_ptr<QSqlDatabase> m_database;
};

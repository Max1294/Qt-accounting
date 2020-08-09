#pragma once
#include <memory>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

namespace {
    class DBCloser {
    public:
        void operator()(QSqlDatabase* db) {
            db->close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
            delete db;
        }
    };
}

class DBManager
{
public:
    bool OpenDatabase(QString DBName);
    bool ExecuteQuery(QString queryText);
    static DBManager& instance();

    QSqlQuery query() const;

private:
    std::unique_ptr<QSqlDatabase, DBCloser> m_db;
    QString m_dbPath;
    QSqlQuery m_query;
    QSqlRecord m_sqlRecord;
    DBManager();
};


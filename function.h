#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

bool OpenDatabase(QString DBName) {
    const QString path = "Contacts";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/drago/.local/share/Application/TestDB");

    if (!db.open()) {
        qDebug() << "Error: can not open Database " + DBName;
        return false;
    }

    qDebug() << "Database " + db.databaseName() << " successfully opened";
    qDebug() << "driver: " << db.driverName() << " is avaliable: " << db.isDriverAvailable("QSQLITE");
//    QString queryText{"SELECT rowid, * FROM /home/drago/.local/share/Application/TestDB"};
    QSqlQuery query; //{queryText};

    query.exec("SELECT Name, Surname, Number FROM Contacts");
    QSqlRecord record = query.record();
//    query.exec("SELECT COUNT(1) FROM Contacts");
//    qDebug() << "Number of columns: " << record.count() << "Number of rows: " << query.value(0).toString();

    while(query.next())
    {
        for(int i = 0; i < record.count(); ++i)
        {
            auto data = query.value(i).toString();
            qDebug() << "data " << data;
//            QString name = query.value(0).toString();
//            QString surname = query.value(1).toString();
//            QString number = query.value(2).toString();
//            qDebug() << "name " << name << " surname " << surname << " phone " << number;
        }
        qDebug() << "\n";
    }
    qDebug() << "Number of columns: " << record.count();
    query.exec("SELECT COUNT(1) FROM Contacts");
    query.next();
    qDebug() << "Number of rows: " << query.value(0).toString();
    db.close();
    return true;
}



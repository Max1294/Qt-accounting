#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

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

    while(query.next())
    {
        QString name = query.value(0).toString();
        QString surname = query.value(1).toString();
        QString number = query.value(2).toString();
        qDebug() << "name " << name << " surname " << surname << " phone " << number;
    }

    db.close();
    return true;
}



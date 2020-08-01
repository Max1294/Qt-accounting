#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QDebug>

bool OpenDatabase(QString DBName) {
    const QString path = "Contacts";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    if (!db.open()) {
        qDebug() << "Error: can not open Database " + DBName;
        return false;
    }
    db.setDatabaseName(DBName);
    qDebug() << "Database " + db.databaseName() << " successfully opened";
    qDebug() << "driver: " << db.driverName() << " is avaliable: " << db.isDriverAvailable("QSQLITE");

    db.close();
    return true;
}



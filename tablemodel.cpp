#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QMap>

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")}
{
    database().setDatabaseName(QString{"/home/drago/.local/share/Application/TestDB"});

    qDebug() << "driver: " << database().isValid();
    if (!database().open()) {
        qDebug() << "Error: can not open Database";
    }
    qDebug() << database().databaseName();

    setTable("Contacts");

    select();
}

QVariant TableModel::getData(int index) const
{
    QMap<int, QString> columnsName = {
        {0, "Name"},
        {1, "Surname"},
        {2, "Number"}
    };

    return QVariant::fromValue(QSqlTableModel::record((index % rowCount())).value(columnsName[(index / rowCount())]));
}

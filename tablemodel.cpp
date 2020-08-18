#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")}
{
    database().setDatabaseName(QString{"/home/drago/Desktop/QtProjects/TestDB"});

    qDebug() << "driver: " << database().isValid();
    if (!database().open()) {
        qDebug() << "Error: can not open Database";
    }
    qDebug() << database().databaseName();
    qDebug() << database().tables();
    qDebug() << database().tables()[1];
    QString queryText{"pragma table_info(" + database().tables()[1] + ")"};
    qDebug() << "queryText: " << queryText;
    auto names = database().exec(queryText);
    qDebug() << "names: ";
    while(names.next())
    {
        qDebug() << names.value(1).toString();
    }

    setTable(database().tables()[1]);

    select();
}

QVariant TableModel::getData(int index) const
{
    return QVariant::fromValue(QSqlTableModel::record((index % rowCount())).value((index / rowCount())));
}

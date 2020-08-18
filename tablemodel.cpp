#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <type_traits>

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

    setRoleNames(0);
    setTable(database().tables()[0]);
    qDebug() << "names size " << names.size();
    select();
}

//QHash<int, QByteArray> TableModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    for(int i = 0; i < names.size(); ++i)
//        roles[Qt::UserRole + i] = getRoleNames().toUtf8();
//}

//int TableModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent);
//    rowCount();
//}

//QVariant TableModel::data(const QModelIndex &index, int role) const
//{
//    return {};
//}

QVariant TableModel::getData(int index) const
{
    return QVariant::fromValue(QSqlTableModel::record((index % rowCount())).value((index / rowCount())));
}

QString TableModel::getRoleNames() const
{
    names.next();
    return names.value(1).toString();
}

void TableModel::setRoleNames(int tableIndex)
{
    QString queryText{"pragma table_info(" + database().tables()[tableIndex] + ")"};
    qDebug() << "queryText: " << queryText;
    names = database().exec(queryText);
}

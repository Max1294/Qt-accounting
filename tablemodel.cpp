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

    qDebug() << database().databaseName() << " " << database().tables();

    setTable(database().tables()[0]);

    auto temp = roleNames();
    for(auto& val : temp) {
        roles.push_back(val);
    }

    for(auto& val : roles) {
        qDebug() << "role " << val;
    }

    select();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QString queryText{"pragma table_info(" + database().tables()[0] + ")"};
    qDebug() << "queryText: " << queryText;
    QSqlQuery names = database().exec(queryText);

    QHash<int, QByteArray> temp;
    qDebug() << "enter";
    for(int i = 0; names.next(); ++i){
        qDebug() << "i " << i;
        temp[Qt::UserRole + i + 1] = names.value(1).toByteArray();
//        roles.push_back(names.value(1).toString());
    }

    temp[40] = "test";

    return temp;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    if (!index.isValid()) {
        return {};
    }
    qDebug() << "enter data" << index.row() << " " << index.column();
    if(role == 40)
    {
        return "test data";
    } else if(role == Qt::UserRole + 1)
    {
        return "Name";
    }

    return QVariant::fromValue (record(index.row()).value(index.column()));
}

QVector<QString> TableModel::getRoles()
{
    return roles;
}



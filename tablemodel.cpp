#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QModelIndex>

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")}
{
    database().setDatabaseName(QString{"/home/drago/Desktop/QtProjects/TestDB"});

    setEditStrategy(QSqlTableModel::OnFieldChange);

    qDebug() << "driver: " << database().isValid();

    if (!database().open()) {
        qDebug() << "Error: can not open Database";
    }

    m_tablesName = database().tables();
    m_tablesCount = database().tables().size();
    qDebug() << database().databaseName() << " tables count " << m_tablesCount
             << " tables " << m_tablesName;

    setTable(database().tables()[0]);
    select();
}

void TableModel::changeTab(int index)
{
    setTable(database().tables()[index]);
    select();
}

void TableModel::editField(const QModelIndex &index, QString data)
{
    if (data == record(index.row()).value(index.column())) return;

    qDebug() << "edit " << record(index.row()).value(index.column()) << " on " << data;

    auto tempRecord = record(index.row());
    tempRecord.setValue(index.column(), data);

    updateRowInTable(index.row(), tempRecord);

    setData(index, data);

//    emit dataChanged(createIndex(0, 0),
//                     createIndex(index .row(), index.column()));
}

int TableModel::tablesCount() const
{
    return m_tablesCount;
}

QStringList TableModel::tablesName() const
{
    return m_tablesName;
}

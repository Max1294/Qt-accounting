#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>

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

    setTab(TableModel::defaultTab);

    auto tmp = roleNames();
    for(auto& role : tmp)
    {
        qDebug() << "role " << role;
    }
}

void TableModel::setTab(int index)
{
    setTable(database().tables()[index]);
    select();
}

void TableModel::editField(int index, QString data)
{
    int row = index%rowCount();
    int column = index/rowCount();

    if (data == record(row).value(column)) return;

    qDebug() << "edit " << record(row).value(column) << " on " << data;

    auto tempRecord = record(row);
    tempRecord.setValue(column, data);

    updateRowInTable(row, tempRecord);
    setData(createIndex(row, column), data);

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

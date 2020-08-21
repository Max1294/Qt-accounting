#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

int TableModel::connection = 0;

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE", "Connection" + QString::number(TableModel::connection))}
{
    database().setDatabaseName(QString{"/home/drago/Desktop/QtProjects/TestDB"});

    setEditStrategy(QSqlTableModel::OnManualSubmit);//(QSqlTableModel::OnFieldChange);

    qDebug() << "driver: " << database().isValid();

    if (!database().open()) {
        qDebug() << "Error: can not open Database";
    }

    m_tablesCount = database().tables().size();
    qDebug() << database().databaseName() << " tables count " << m_tablesCount;

//    setTable(database().tables()[tabIndex]);
//    select();

    qDebug() << "connection " << TableModel::connection;
    ++TableModel::connection;
}

int TableModel::tablesCount() const
{
    return m_tablesCount;
}

void TableModel::resetData()
{
    submitAll();
}

void TableModel::changeTab(int tabIndex)
{
    setTable(database().tables()[tabIndex]);
    select();
}

#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")}
{
    database().setDatabaseName(QString{"/home/drago/Desktop/QtProjects/TestDB"});

    setEditStrategy(QSqlTableModel::OnManualSubmit);

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

int TableModel::tablesCount() const
{
    return m_tablesCount;
}

QStringList TableModel::tablesName() const
{
    return m_tablesName;
}

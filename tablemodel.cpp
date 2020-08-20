#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

TableModel* TableModel::model = nullptr;

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")}
{
    if(database().databaseName() == "")
    {
        database().setDatabaseName(QString{"/home/drago/Desktop/QtProjects/TestDB"});

        qDebug() << "driver: " << database().isValid();

        if (!database().open()) {
            qDebug() << "Error: can not open Database";
        }

        m_tablesCount = database().tables().size();
        qDebug() << database().databaseName() << " tables count " << m_tablesCount;

        setTable(database().tables()[0]);
        select();
    }
}

int TableModel::tablesCount() const
{
    return m_tablesCount;
}

TableModel TableModel::instance()
{
    if(model == nullptr)
    {
        model = new TableModel();
    }

    return model;
}

TableModel::~TableModel()
{
    delete model;
}

#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")},
    m_currentTab{0},
    sortDirection{SortDirection::DOWN}
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

    setTab(m_currentTab);
}

void TableModel::setTab(int index)
{
    m_currentTab = index;
    setTable(database().tables()[index]);

    if(filter() == "")
    {
        qDebug() << "filter is empty";
        select();
        return;
    }

    setFilter(filter());
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
}

void TableModel::sortColumn(int column, QString filter)
{
    QString columnName = headerData(column, Qt::Horizontal).toString();
    QMap<bool, QString> order = {
        {SortDirection::DOWN, "DESC"},
        {SortDirection::UP, "ASC"}
    };

    if(filter == "")
    {
        setFilter("1=1 ORDER BY " + columnName + " " + order[sortDirection]); // + ", Surname ASC, Number ASC");

        qDebug() << "query " << "SELECT * FROM " + database().tables()[m_currentTab] + " ORDER BY " + columnName + " " + order[sortDirection];
        sortDirection = !sortDirection;
        qDebug() << "filter() " << QSqlTableModel::filter();
        return;
    }

//    QString filterText = "";


//    qDebug() << "column " << columnName;
//    setFilter(columnName +  "'Eric'");
//    orderByClause();
//    select();
}

int TableModel::tablesCount() const
{
    return m_tablesCount;
}

QStringList TableModel::tablesName() const
{
    return m_tablesName;
}

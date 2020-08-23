#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>

TableModel::TableModel(QObject *parent) :
    QSqlTableModel{parent, QSqlDatabase::addDatabase("QSQLITE")},
    m_currentTab{0},
    sortCondition{Qt::AscendingOrder}
{
    database().setDatabaseName(QString{"/home/drago/Desktop/QtProjects/TestDB"});
    setEditStrategy(QSqlTableModel::OnFieldChange);

    qDebug() << "driver: " << database().isValid();

    if (!database().open()) {
        qDebug() << "Error: can not open Database";
    }

    setTable(database().tables()[m_currentTab]);

    m_tablesName = database().tables();
    m_tablesCount = database().tables().size();
    qDebug() << database().databaseName() << " tables count " << m_tablesCount
             << " tables " << m_tablesName;

    qDebug() << "test" << headerData(3, Qt::Horizontal);

    for(int i = 0; i < m_tablesCount; ++i)
    {
        m_tablesFilter.push_back("");

        for(int j = 0; headerData(j, Qt::Horizontal).toString() != QString::number(j+1); ++j)
        {
            QHash<QString, QString> tmp;
            tmp[headerData(j, Qt::Horizontal).toString()] = "";
            m_tablesFieldsFilter.push_back(tmp);
        }
    }
    select();
}

void TableModel::setTab(int index)
{
    qDebug() << index << database().tables()[m_currentTab];
    m_currentTab = index;
    setTable(database().tables()[m_currentTab]);
    bool isOk = select();
    qDebug() << "status " << isOk;
    qDebug() << m_tablesFilter[m_currentTab];

    if(m_tablesFilter.at(m_currentTab) == "")
    {
        qDebug() << "set table without filters";
        select();
    }
    else {
        setFilter(m_tablesFilter.at(m_currentTab));
    }
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
    qDebug() << "fil " << m_tablesFieldsFilter[m_currentTab][columnName];

    if(filter == "order")
    {
        qDebug() << "order";
        sortCondition = sortCondition == Qt::AscendingOrder ? Qt::DescendingOrder : Qt::AscendingOrder;
        setSort(column, sortCondition);
        select();
        return;
    }

    if(m_tablesFieldsFilter[m_currentTab][columnName] != "" && filter == "")
    {
        m_tablesFieldsFilter[m_currentTab][columnName] = "";
        select();
    }

    QRegExp exp;
    exp.setPattern("\\s");
    filter.replace(exp, "");

    exp.setPattern("^<=|^>=|^<|^>|^=");

    qDebug() << "filter " << filter << "reg exp " << exp.indexIn(filter);

    if(int pos = exp.indexIn(filter); pos != -1)
    {
        filter = filter.trimmed(); // ???
        m_tablesFieldsFilter[m_currentTab][columnName] = filter;
        filter.insert(pos+ (filter[pos+1] == '=' ? 2 : 1), "'");
        filter.insert(filter.size(), "'");
        exp.setPattern("\\s");
        filter.replace(exp, "");
        qDebug() << "filter " << filter;

        m_tablesFilter[m_currentTab] += m_tablesFilter[m_currentTab] == "" ? columnName + filter : " AND " + columnName + filter;
        qDebug() << m_tablesFilter[m_currentTab];

        setFilter(m_tablesFilter[m_currentTab]);
        return;
    }

    exp.setPattern("[-]+");
    qDebug() << "filter " << filter << "reg exp " << exp.indexIn(filter);

    if(int pos = exp.indexIn(filter); pos != -1) {
        m_tablesFieldsFilter[m_currentTab][columnName] = filter;
        filter.insert(0, ">='");
        filter.insert(pos+3, "'");
        filter.insert(pos+5, columnName +"<='");
        filter.insert(filter.size(), "'");
        filter.replace(exp, " AND ");

        qDebug() << "end filter " << filter;
        m_tablesFilter[m_currentTab] += m_tablesFilter[m_currentTab] == "" ? columnName + filter : " AND " + columnName + filter;

        qDebug() << "final filter " << m_tablesFilter[m_currentTab];
        setFilter(m_tablesFilter[m_currentTab]);
    }
}

int TableModel::tablesCount() const
{
    return m_tablesCount;
}

QStringList TableModel::tablesName() const
{
    return m_tablesName;
}

QString TableModel::tablesFieldsFilter(QString key) const
{
    return m_tablesFieldsFilter[m_currentTab][key];
}

#include "tablemodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>

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

    m_tablesName = database().tables();
    m_tablesCount = database().tables().size();
    qDebug() << database().databaseName() << " tables count " << m_tablesCount
             << " tables " << m_tablesName;

    qDebug() << "test" << headerData(3, Qt::Horizontal);

    for(int i = 0; i < m_tablesCount; ++i)
    {
        m_tablesFilter.push_back("");
        setTable(database().tables()[i]);
        QHash<QString, QString> tmp;

        for(int j = 0; headerData(j, Qt::Horizontal).toString() != QString::number(j+1); ++j)
        {
            tmp.insert(headerData(j, Qt::Horizontal).toString(), "");
        }

        m_tablesFieldsFilter.push_back(tmp);
    }

    qDebug() << "size " << m_tablesFieldsFilter.size() << m_tablesFilter.size();
    for(auto it = m_tablesFieldsFilter.begin(); it != m_tablesFieldsFilter.end(); ++it)
    {
        qDebug() << "it " << *it;
    }

    qDebug() << "m_tablesFilter " << m_tablesFilter;
}

void TableModel::setTab(int index)
{
    qDebug() << index << database().tables()[m_currentTab];
    m_currentTab = index;
    setTable(database().tables()[m_currentTab]);
    qDebug() << m_tablesFilter[m_currentTab];

    if(m_tablesFilter.at(m_currentTab) == "")
    {
        qDebug() << "set table without filters";
        select();
    }
    else {
        setFilter(m_tablesFilter.at(m_currentTab));
        select();
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
    QRegExp exp;

    exp.setPattern("\\s");
    filter.replace(exp, "");

//    setFilter("Name='das'");

//    if(rowCount() == 0) {
//        qDebug() << "no match";
//        setFilter("Name='Eric'");
//        return;
//    }

    if(filter == "order")
    {
        sortCondition = sortCondition == Qt::AscendingOrder ? Qt::DescendingOrder : Qt::AscendingOrder;
        setSort(column, sortCondition);
        select();
        return;
    }

    if(filter == "" && m_tablesFieldsFilter[m_currentTab][columnName] != "")
    {
        QString str = columnName + m_tablesFieldsFilter[m_currentTab][columnName];
        exp.setPattern("\\b" + str);
        int pos = exp.indexIn(m_tablesFilter[m_currentTab]);
        int length = exp.matchedLength();

        if(pos == -1) return;

        m_tablesFieldsFilter[m_currentTab][columnName] = "";

        if(pos == 0) {
            qDebug() << "1" << m_tablesFilter[m_currentTab];
            m_tablesFilter[m_currentTab].replace(pos, length + 5, "");
        }
        else if(pos > 0 && (pos + length == m_tablesFilter[m_currentTab].size()))
        {
            qDebug() << "2" << m_tablesFilter[m_currentTab];
            m_tablesFilter[m_currentTab].replace(pos-5, length + 5, "");
        }
        else
        {
            qDebug() << "3" << m_tablesFilter[m_currentTab];
            m_tablesFilter[m_currentTab].replace(pos, length + 5, "");
        }

        setTable(database().tables()[m_currentTab]);
        setFilter(m_tablesFilter.at(m_currentTab));

//        select();
        qDebug() << "m_tablesFilter " << m_tablesFilter[m_currentTab] << QSqlTableModel::filter();
        return;
    }

    exp.setPattern("^<=|^>=|^<|^>|^=");

    qDebug() << "filter " << filter << "reg exp " << exp.indexIn(filter);

    if(int pos = exp.indexIn(filter); pos != -1)
    {
        filter.insert(pos+ (filter[pos+1] == '=' ? 2 : 1), "'");
        filter.insert(filter.size(), "'");
        m_tablesFieldsFilter[m_currentTab][columnName] = filter;
        qDebug() << "filter " << filter;

        m_tablesFilter[m_currentTab] += m_tablesFilter[m_currentTab] == "" ? columnName + filter : " AND " + columnName + filter;
        qDebug() << "m_tablesFilter " <<  m_tablesFilter[m_currentTab];

        setFilter(m_tablesFilter[m_currentTab]);

        // TODO don't display empty data
        if(rowCount() == 0) {
            qDebug() << "no match";
            setFilter("1=1");
            select();
        }

        return;
    }

    exp.setPattern("[-]+");
    qDebug() << "filter " << filter << "reg exp " << exp.indexIn(filter);

    if(int pos = exp.indexIn(filter); pos != -1) {
        filter.insert(0, ">='");
        filter.insert(pos+3, "'");
        filter.insert(pos+5, columnName +"<='");
        filter.insert(filter.size(), "'");
        m_tablesFieldsFilter[m_currentTab][columnName] = filter;
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

void TableModel::addColumn(QString column)
{
    static int c = 1;
    database().exec("ALTER TABLE " + database().tables()[m_currentTab] + " ADD " + column + QString::number(c) + " TEXT");
    setTab(m_currentTab);
    ++c;
}

void TableModel::deleteColumn(int column)
{
    QVector<QString> columns;

    for(int i = 0; headerData(i, Qt::Horizontal).toString() != QString::number(i+1); ++i)
    {
        if(i == column) continue;
        qDebug() << headerData(i, Qt::Horizontal).toString() + ",";
        columns.push_back(headerData(i, Qt::Horizontal).toString() + ",");
    }

    int pos = columns[columns.size()-1].lastIndexOf(',');
    columns[columns.size()-1]=columns[columns.size()-1].left(pos);
    qDebug() <<  columns[columns.size()-1];
    qDebug() << database().exec("BEGIN TRANSACTION").lastError().text();

    QString query;
    for(auto& column : columns)
    {
        query += column;
    }

    auto _table = database().tables()[m_currentTab];

    qDebug() << "1"  << database().exec("CREATE TEMPORARY TABLE backup_(" + query + ")").lastError().text();
    qDebug() << "2 INSERT INTO backup_ SELECT " + query + " FROM " + database().tables()[m_currentTab]
                << database().exec("INSERT INTO backup_ SELECT " + query + " FROM " + database().tables()[m_currentTab]).lastError().text();
    qDebug() << "3"  << database().exec("DROP TABLE " + database().tables()[m_currentTab]).lastError().text();
    qDebug() << "4"  << database().exec("CREATE TABLE " + _table + "(" + query + ")").lastError().text();
    qDebug() << "5" << database().exec("INSERT INTO " + _table + " SELECT " + query + " FROM backup_").lastError().text();
    qDebug() << "6"  << database().exec("DROP TABLE backup_").lastError().text();
    qDebug() << "7"  << database().exec("COMMIT").lastError().text();

    removeColumn(column);
}

void TableModel::addRow()
{

    QVector<QString> headers;
    QString values;

    for(int i = 0; headerData(i, Qt::Horizontal).toString() != QString::number(i+1); ++i)
    {
        values += "NULL,";
        qDebug() << headerData(i, Qt::Horizontal).toString() + ",";
        headers.push_back(headerData(i, Qt::Horizontal).toString() + ",");
    }

    int pos = headers[headers.size()-1].lastIndexOf(',');
    headers[headers.size()-1]=headers[headers.size()-1].left(pos);
    qDebug() <<  headers[headers.size()-1];

    pos = values.lastIndexOf(',');
    values = values.left(pos);
    qDebug() <<  values;

    QString query;
    for(auto& header : headers)
    {
        query += header;
    }

    static int q = 1;
    QString queryText = "INSERT INTO " + database().tables()[m_currentTab] + " (" + query + ") VALUES (" + values + ")";
    qDebug() <<queryText;
    qDebug() << database().exec(queryText).lastError().text();

    insertRow(rowCount());
    setTab(m_currentTab);
    submitAll();
    ++q;
}

void TableModel::deleteRow(int row)
{
    qDebug() << "row remove status " << removeRow(row);
    setTab(m_currentTab);
}

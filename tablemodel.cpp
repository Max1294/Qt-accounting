#include "tablemodel.h"
#include <QDebug>
TableModel::TableModel(QObject *parent) :
    m_DBManager{DBManager::instance()}
{
    Q_UNUSED(parent)
    m_DBManager.OpenDatabase("TestDB");
    QSqlQuery query = m_DBManager.query();
    query.exec("SELECT COUNT(1) FROM Contacts");
    query.next();
    m_rowCount = query.value(0).toInt();

    qDebug() << "names: " << query.exec("pragma table_info(Contacts)"); // get columns names
    while(query.next())
    {
        qDebug() << "data " << query.value(1).toString();
//        roles.push_back(query.value(1).toInt());
    }

    query.exec("SELECT Name, Surname, Number FROM Contacts");
    QSqlRecord record = query.record();
    m_columnCount = record.count();

    qDebug() << "Number of columns: " << m_columnCount << "Number of rows: " << m_rowCount;
}

int TableModel::rowCount(const QModelIndex &) const
{
    return m_rowCount;
}

int TableModel::columnCount(const QModelIndex &) const
{
    return m_columnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
            return QString("%1, %2, %3").arg(index.column()).arg(index.row());
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}


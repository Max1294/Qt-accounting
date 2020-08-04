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
    for(int i = 1; query.next(); ++i)
    {
         qDebug() << "data " << query.value(1).toString();
         // m_roleNames.insert((Qt::UserRole + i),  query.value(1).toByteArray());
         m_roles.push_back(query.value(1).toByteArray());
         m_roleNames[Qt::UserRole + i] = query.value(1).toByteArray();
         qDebug() << "m_roleNames " << m_roleNames[Qt::UserRole + i];
         qDebug() << "m_roles " << m_roles;
    }

    query.exec("SELECT Name, Surname, Number FROM Contacts");
    QSqlRecord record = query.record();
    m_columnCount = record.count();
    m_rows.reserve(m_rowCount);
    m_rows.resize(m_rowCount);

    for(int i = 0; query.next(); ++i)
    {
        for(int j = 0; j < m_columnCount; ++j)
        {
            m_rows[i] << QVariant::fromValue(query.value(j));
        }

    }

    //    m_rows = {"Jhon", "Bruno", 32};
    qDebug() << "m_rows: " << m_rows;
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
    if(!index.isValid())// && role == Qt::DisplayRole)
    {
        return QVariant{};
    }

    if (role == Qt::DisplayRole) return QString("moc data");

    return QVariant::fromValue(m_rows[role]);
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return m_roleNames;
    //return {{Qt::DisplayRole, "display"}};//m_roleNames;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
                return QVariant();
    }
    return QVariant::fromValue(m_roleNames[section]);
}

QVector<QVariantList> TableModel::rows() const
{
    return m_rows;
}

QVector<QByteArray> TableModel::roles() const
{
    return m_roles;
}

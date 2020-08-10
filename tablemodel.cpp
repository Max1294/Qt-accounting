#include "tablemodel.h"
#include <QDebug>
#include <QSqlError>
TableModel::TableModel(QObject *parent) :
    m_DBManager{DBManager::instance()}
{
    // ATTACH '/home/drago/.local/share/Application/TestDB' AS my_db;
    // SELECT name FROM my_db.sqlite_master WHERE type='table'; // all tables from db
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

    return QVariant::fromValue(m_rows[index.row()][index.column()]);
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

void TableModel::updateData(const int row, const int column, QString newdata)
{
    std::string queryText = "UPDATE Contacts SET " + m_roles[column].toStdString() + "='" + newdata.toStdString() + "'" + " WHERE " + m_roles[column].toStdString() + "='" + m_rows[row][column].toString().toStdString() + "'";

    auto query = m_DBManager.query();

    qDebug() <<  "query " << QString::fromUtf8(queryText.c_str());
//              << " status " << query.prepare(QString::fromUtf8(queryText.c_str()))
//              << "error " << query.lastError().text();
    m_DBManager.query().exec(QString::fromUtf8(queryText.c_str()));
    m_rows[row][column] = QVariant(newdata);
}

void TableModel::sortConditions(int column, QVariant conditions...)
{
    if(conditions.Size > 2 || conditions.Size == 0) return;

    auto query = m_DBManager.query();

    QString queryText = "SELECT " + QString::fromUtf8(m_roles[column].toStdString().c_str()) + " FROM Contacts WHERE "
            + (conditions.Size == 1 ? QVariant::fromValue(conditions).toString()
                                    : QVariant::fromValue(conditions).toString() + " AND " + QVariant::fromValue(conditions).toString());

    qDebug() << "sort execute " << query.exec(queryText);
}

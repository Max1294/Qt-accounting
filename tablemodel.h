#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "dbmanager.h"
#include <QVector>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QVector<QByteArray> roles READ roles CONSTANT)
    Q_PROPERTY(QVector<QVariantList> rows READ rows CONSTANT)
public:
    explicit TableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVector<QVariantList> rows() const;
    QVector<QByteArray> roles() const;

    Q_INVOKABLE void setQuery(QString queryText);

private:
    DBManager& m_DBManager;
    int m_rowCount;
    int m_columnCount;
    QHash<int, QByteArray> m_roleNames;
    QVector<QVariantList> m_rows;
    QVector<QByteArray> m_roles;
};

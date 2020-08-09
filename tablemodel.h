#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "dbmanager.h"
#include <QVector>
#include <QMimeData>

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

    void SetData(int row, int column, QString data);
    void AddColumn(QString columnName);
    void addRow(); // add params
    QString changeTable(QString tableName);


    Q_INVOKABLE void updateData(const int row, const int column, QString newdata);
    Q_INVOKABLE void sortConditions(int column, QVariant conditions...);
private:
    DBManager& m_DBManager;
    int m_rowCount;
    int m_columnCount;
    QHash<int, QByteArray> m_roleNames; // QVector<QHash<int, QByteArray>> ??
    QVector<QVariantList> m_rows;
    QVector<QByteArray> m_roles;
};

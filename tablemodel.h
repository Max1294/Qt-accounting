#pragma once
#include <QSqlTableModel>
#include <QSqlQuery>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = nullptr);

//    QHash<int, QByteArray> roleNames() const override;
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    Q_INVOKABLE QVariant getData(int index) const;
    Q_INVOKABLE QString getRoleNames() const;
    void setRoleNames(int tableIndex);

private:
    mutable QSqlQuery names;
};

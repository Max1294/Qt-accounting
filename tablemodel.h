#pragma once
#include <QSqlTableModel>
#include <QSqlQuery>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
//    Q_PROPERTY(QVector<QString> roles READ roles CONSTANT)
public:
    explicit TableModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString getData(int index) const;

    QVector<QString> getRoles();

private:
    QVector<QString> roles;
};

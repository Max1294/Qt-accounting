#pragma once

#include <QSqlTableModel>
#include <QSqlQuery>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int tablesCount READ tablesCount CONSTANT)
    Q_PROPERTY(QStringList tablesName READ tablesName CONSTANT)
public:
    explicit TableModel(QObject* parent = nullptr);

    Q_INVOKABLE void setTab (int index);
    Q_INVOKABLE void editField(int index, QString data);

    int tablesCount() const;
    QStringList tablesName() const;

private:
    int m_tablesCount;
    QStringList m_tablesName;
};

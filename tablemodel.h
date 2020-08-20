#pragma once
#include <QSqlTableModel>
#include <QSqlQuery>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int tablesCount READ tablesCount CONSTANT)
public:
    explicit TableModel(QObject* parent = nullptr);
    int tablesCount() const;

private:
    int m_tablesCount;
    static int connection;
};

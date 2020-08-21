#pragma once

#include <QSqlTableModel>
#include <QSqlQuery>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int tablesCount READ tablesCount CONSTANT)
    Q_PROPERTY(int tableIndex READ tableIndex WRITE setTableIndex);
public:
    explicit TableModel(QObject* parent = nullptr);
    int tablesCount() const;

    Q_INVOKABLE void resetData();
    Q_INVOKABLE void changeTab(int tabIndex);
    int tableIndex() const;
    void setTableIndex(int tableIndex);

private:
    int m_tablesCount;
    int m_tableIndex;
    static int connection;
};

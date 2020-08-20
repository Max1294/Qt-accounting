#pragma once
#include <QSqlTableModel>
#include <QSqlQuery>
#include <memory>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int tablesCount READ tablesCount CONSTANT)
public:
//    explicit TableModel(QObject* parent = nullptr);
    int tablesCount() const;
    static TableModel instance();

    ~TableModel();

protected:
    TableModel(QObject* parent = nullptr);
    static TableModel* model;
    int m_tablesCount;
};

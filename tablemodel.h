#pragma once
#include <QSqlTableModel>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = nullptr);

    Q_INVOKABLE QVariant getData(int index) const;

};

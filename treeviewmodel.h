#pragma once
#include <QStandardItemModel>
#include "tablemodel.h"
#include <QStandardItem>
#include <memory>
#include <QVector>

class TreeViewModel: public QStandardItemModel// , public TableModel
{
    Q_OBJECT;
public:
    TreeViewModel(QObject* parent = nullptr);

    void SetData();

private:
    QStandardItem* m_rootItem;
    QVector<QStandardItem> m_tables;
    QVector<QStandardItem> m_values;
};


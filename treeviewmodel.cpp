#include "treeviewmodel.h"

TreeViewModel::TreeViewModel(QObject* parent)
    : QStandardItemModel{parent},
      m_rootItem{invisibleRootItem()}
{
    setColumnCount(1);
        QStandardItem* rootItem = invisibleRootItem();

        QStandardItem* group1 = new QStandardItem;
        QStandardItem* group2 = new QStandardItem;
        QStandardItem* group3 = new QStandardItem;

        QStandardItem* value1 = new QStandardItem;
        QStandardItem* value2 = new QStandardItem;
        QStandardItem* value3 = new QStandardItem;
        QStandardItem* value4 = new QStandardItem;
        QStandardItem* value5 = new QStandardItem;
        QStandardItem* value6 = new QStandardItem;
        QStandardItem* value7 = new QStandardItem;
        QStandardItem* value8 = new QStandardItem;
        QStandardItem* value9 = new QStandardItem;

        group1->setText("Group1");
        group2->setText("Group2");
        group3->setText("Group3");

        value1->setText("Value1");
        value2->setText("Value2");
        value3->setText("Value3");
        value4->setText("Value4");
        value5->setText("Value5");
        value6->setText("Value6");
        value7->setText("Value7");
        value8->setText("Value8");
        value9->setText("Value9");

        group1->appendRow(value1);
        group1->appendRow(value2);
        group1->appendRow(value3);

        group2->appendRow(value4);
        group2->appendRow(value5);
        group2->appendRow(value6);

        group3->appendRow(value7);
        group3->appendRow(value8);
        group3->appendRow(value9);

        rootItem->appendRow(group1);
        rootItem->appendRow(group2);
        rootItem->appendRow(group3);


}

void TreeViewModel::SetData()
{
//    QMap<int, QString> values = {
//        {0, "Value1"},
//        {1, "Value2"},
//        {2, "Value3"},
//        {3, "Value4"},
//        {4, "Value5"},
//    };

//    QMap<int, QString> tables = {
//        {0, "Table1"},
//        {1, "Table2"},
//        {2, "Table3"},
//        {3, "Table4"},
//        {4, "Table5"},
//    };

//    setColumnCount(1);

//    // values
//    for(int i = 0; i < 5; ++i)
//    {
//        QStandardItem tmp;
//        tmp.setText(values[i]);
//        m_values.push_back(tmp);
//    }

//    // group
//    for(int i = 0; i < 1; ++i) { // TODO: i < TablesCount in DB
//        QStandardItem tmp;
//    }



//    m_rootItem->appendRow(&m_tables[0]);
}

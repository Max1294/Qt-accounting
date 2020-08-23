#pragma once
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QVector>
#include <QHash>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int tablesCount READ tablesCount CONSTANT)
    Q_PROPERTY(QStringList tablesName READ tablesName CONSTANT)
public:
    explicit TableModel(QObject* parent = nullptr);

    Q_INVOKABLE void setTab (int index);
    Q_INVOKABLE void editField(int index, QString data);
    Q_INVOKABLE void sortColumn(int column, QString filter = "");
    Q_INVOKABLE QString tablesFieldsFilter(QString key) const;

    int tablesCount() const;
    QStringList tablesName() const;

private:
    int m_tablesCount;
    QStringList m_tablesName;
    int m_currentTab;
    Qt::SortOrder sortCondition;
    QVector<QHash<QString, QString>> m_tablesFieldsFilter;
    QVector<QString> m_tablesFilter;
};

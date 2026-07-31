#pragma once
#include<qabstractitemmodel.h>

class StudentsModel :
    public QAbstractTableModel
{
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole);
};
#pragma once
#include <QAbstractTableModel>
#include "Dog.h"
#include <vector>

class DogListModel : public QAbstractTableModel
{
private:
    std::vector<Dog> list;

public:
    DogListModel(std::vector<Dog> list, QObject* parent = nullptr)
        : QAbstractTableModel(parent), list(list) {
    }

    //how many rows exist
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return list.size();
    }

    //how many columns exist 
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5; // Breed, Name, Years, Months, Photo Link
    }

    //cell content
    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return {};

        if (index.row() >= list.size())
            return {};

        Dog& d = const_cast<Dog&>(list[index.row()]);
        //populez tabelul 
        switch (index.column()) {
        case 0: return QString::fromStdString(d.getBreed());
        case 1: return QString::fromStdString(d.getName());
        case 2: return d.getAge().getYears();
        case 3: return d.getAge().getMonths();
        case 4: return QString::fromStdString(d.getLink());
        }

        return {};
    }

    //column labels for the horizontal header view row
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return {};

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Breed";
            case 1: return "Name";
            case 2: return "Years";
            case 3: return "Months";
            case 4: return "Photo Link";
            }
        }

        return {};
    }

    //refresh the grid 
    void updateData(const std::vector<Dog>& newData) {
        beginResetModel();
        this->list = newData;
        endResetModel();
    }
};
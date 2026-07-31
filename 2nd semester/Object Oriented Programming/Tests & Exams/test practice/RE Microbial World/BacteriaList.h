#pragma once
#include<QAbstractTableModel>
#include"Service.h"
#include"QBrush.h"

class BacteriaList : public QAbstractTableModel
{
private:
	std::vector<Bacteria> bacteries; 
public:
	BacteriaList(std::vector<Bacteria> data) : bacteries{ data } {}

	int rowCount(const QModelIndex&) const override { return bacteries.size(); }
	int columnCount(const QModelIndex&) const override { return 3; }

	QVariant data(const QModelIndex& idx, int role) const override
	{
		const auto& b = bacteries[idx.row()];
		if (role == Qt::DisplayRole)
		{
			switch (idx.column())
			{
			case 0: return QString::fromStdString(b.getName());
			case 1: return QString::fromStdString(b.getSpecies()); 
			case 2: return QString::fromStdString(std::to_string(b.getSize())); 
			}
		}

		if (role == Qt::BackgroundRole)
		{
			return QBrush(QColor("pink"));
		}

		else return QVariant();
	}

	void updateData(const std::vector<Bacteria>& newB) 
	{
		beginResetModel();
		bacteries = newB; 
		endResetModel();
	}
};

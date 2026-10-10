#pragma once
#include <QAbstractTableModel>
#include "Parcel.h"
#include <QBrush>

//the table with issues that is displayed in every window 

class ParcelsListView : public QAbstractTableModel
{
	std::vector < Parcel > parcels;
public:
	ParcelsListView(std::vector<Parcel> d) : parcels{ d } {}
	int rowCount(const QModelIndex&) const override { return parcels.size(); }
	int columnCount(const QModelIndex&) const override { return 5; }
	QVariant data(const QModelIndex& idx, int role) const override
	{
		const auto& p = parcels[idx.row()];
		if (role == Qt::BackgroundRole && p.getStatus() == true)
		{
			return QBrush(QColor("green"));
		}

		if (role == Qt::DisplayRole)
		{
			switch (idx.column())
			{
			case 0: return QString::fromStdString(p.getRecipient());
			case 1: return QString::fromStdString(p.getStreet());
			case 2: return QString::number(p.getNumber());
			case 3: return QString::number(p.getLocX());
			case 4: return QString::number(p.getLocY());
			}
		}
		return QVariant();
	}

	void updateData(const std::vector<Parcel>& new_parcels)
	{
		beginResetModel();
		parcels = new_parcels;
		endResetModel();
	}
};

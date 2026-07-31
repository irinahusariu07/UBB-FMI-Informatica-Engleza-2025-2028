#pragma once
#include "Service.h"
#include"Star.h"
#include<QAbstractTableModel>

class StarsListModel : public QAbstractTableModel
{
	std::vector<Star> stars;
public:
	StarsListModel(std::vector<Star> sd) : stars{ sd } {}
	int rowCount(const QModelIndex&) const override {
		return stars.size();
	}

	int columnCount(const QModelIndex&) const override {
		return 5;
	}

	QVariant data(const QModelIndex& idx, int role) const override
	{
		if (role != Qt::DisplayRole) return QVariant();
		const auto& s = stars[idx.row()];
		if (idx.column() == 0) return QString::fromStdString(s.getName());

		switch (idx.column())
		{
		case 0: return QString::fromStdString(s.getName());
		case 1: return QString::fromStdString(s.getConstellation());
		case 2: return QString::number(s.getRA());
		case 3: return QString::number(s.getDec());
		case 4: return QString::number(s.getDiam());
		}
		return QVariant();
	}

	void updateData(const std::vector<Star>& new_data)
	{
		beginResetModel();
		stars = new_data;
		endResetModel();
	}
};
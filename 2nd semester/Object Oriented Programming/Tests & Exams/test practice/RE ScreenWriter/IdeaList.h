#pragma once
#include<QAbstractTableModel>
#include "Service.h"

class IdeaList : public QAbstractTableModel
{
private:
	std::vector<Idea> ideas; 
	Writer& writer; 

public:
	IdeaList(std::vector<Idea> d, Writer& w) : ideas{ d }, writer{ w } {}

	int rowCount(const QModelIndex&) const override { return ideas.size(); }
	int columnCount(const QModelIndex&) const override { return 4; }

	QVariant data(const QModelIndex& idx, int role)const override
	{
		const auto& i = ideas[idx.row()];
		if (role == Qt::DisplayRole)
		{
			switch (idx.column())
			{
			case 0: return QString::fromStdString(i.getDesc());
			case 1: return QString::fromStdString(i.getStatus());
			case 2: return QString::fromStdString(i.getCreator());
			case 3: return QString::fromStdString(std::to_string(i.getAct()));
			}
		}
		return QVariant(); 
	}

	void updateData(const std::vector<Idea>& newi)
	{
		beginResetModel(); 
		ideas = newi; 
		endResetModel(); 
	}
};

#pragma once
#include <QAbstractTableModel>
#include "Issue.h"

//the table with issues that is displayed in every window 

class IssueListModel : public QAbstractTableModel
{
	std::vector<Issue> issues; 
public:
	IssueListModel(std::vector<Issue> d) : issues{ d } {}
	int rowCount(const QModelIndex&) const override { return issues.size(); }
	int columnCount(const QModelIndex&) const override { return 4; }
	QVariant data(const QModelIndex& idx, int role) const override
	{
		if (role != Qt::DisplayRole) return QVariant(); 
		const auto& i = issues[idx.row()]; //take an entry => a row 
		switch (idx.column())
		{
		case 0: return QString::fromStdString(i.getDescription());
		case 1: return QString::fromStdString(i.getType());
		case 2: return QString::fromStdString(i.getReporter());
		case 3: return QString::fromStdString(i.getSolver());
		}
		return QVariant();
	}

	void updateData(const std::vector<Issue>& new_data)
	{
		beginResetModel();
		issues = new_data;
		endResetModel();
	}
};
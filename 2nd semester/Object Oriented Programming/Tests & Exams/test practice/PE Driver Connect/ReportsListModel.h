#pragma once
#include<QAbstractTableModel>
#include"Report.h"
#include<qfont.h>
#include<qbrush.h>

class ReportListModel : public QAbstractTableModel
{
	std::vector<Report> reports;
public:
	ReportListModel(std::vector<Report> r) : reports{ r } {}
	int rowCount(const QModelIndex&) const override { return reports.size(); }
	int columnCount(const QModelIndex&) const override { return 4; }
	QVariant data(const QModelIndex& idx, int role) const override
	{
		const auto& report = reports[idx.row()];
		if (role == Qt::FontRole && report.getStatus() == true)
		{
			QFont boldFont;
			boldFont.setBold(true);
			return boldFont;
		}

		if (role == Qt::BackgroundRole)
		{
			return QBrush(QColor("light green"));
		}

		if (role != Qt::DisplayRole) return QVariant();
		switch (idx.column())
		{
		case 0: return QString::fromStdString(report.getDesc());
		case 1: return QString::fromStdString(report.getReporter());
		case 2: return QString::number(report.getLat());
		case 3: return QString::number(report.getLong());
		}
	}

	void updateDate(const std::vector<Report>& new_rep)
	{
		beginResetModel();
		reports = new_rep;
		endResetModel();
	}


};
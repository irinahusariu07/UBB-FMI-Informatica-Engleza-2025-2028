#pragma once
#include<QAbstractTableModel>
#include "Patient.h"
#include <qbrush.h>

class PatientModel : public QAbstractTableModel
{
	std::vector<Patient> patients; 
	std::string current_doc; 

public:
	PatientModel(std::vector<Patient> pd, const std::string& cd) : patients{ pd }, current_doc{ cd } {}
	int rowCount(const QModelIndex&) const override { return patients.size(); }
	int columnCount(const QModelIndex&) const override { return 5; }

	QVariant data(const QModelIndex& idx, int role) const override
	{
		const auto& p = patients[idx.row()]; 
		if (role == Qt::BackgroundRole && p.getDoc() == current_doc)
		{
			return QBrush(QColor("green"));
		}

		if (role == Qt::DisplayRole)
		{
			switch (idx.column())
			{
			case 0: return QString::fromStdString(p.getName());
			case 1: return QString::fromStdString(p.getDiag());
			case 2: return QString::fromStdString(p.getSpec());
			case 3: return QString::fromStdString(p.getDoc());
			case 4: return QString::fromStdString(p.getAdmission());
			}
		}
		return QVariant(); 
	}

	void updateData(const std::vector<Patient>& new_p)
	{
		beginResetModel(); 
		patients = new_p; 
		endResetModel(); 
	}
};
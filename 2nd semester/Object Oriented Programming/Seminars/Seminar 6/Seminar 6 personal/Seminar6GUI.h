#pragma once

#include <QMainWindow>
#include "ui_Seminar6GUI.h"
#include "StudentsModel.h"

class Seminar6GUI : public QMainWindow
{
	Q_OBJECT

public:
	Seminar6GUI( QWidget* parent = nullptr);
	~Seminar6GUI();

private:
	Ui::Seminar6GUIClass ui;
};


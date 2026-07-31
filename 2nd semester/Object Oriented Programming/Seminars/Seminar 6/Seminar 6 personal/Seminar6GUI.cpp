#include "Seminar6GUI.h"

Seminar6GUI::Seminar6GUI(StudentModel* studentModel, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.StudentTableView->setModel(studentModel);
}

Seminar6GUI::~Seminar6GUI()
{}


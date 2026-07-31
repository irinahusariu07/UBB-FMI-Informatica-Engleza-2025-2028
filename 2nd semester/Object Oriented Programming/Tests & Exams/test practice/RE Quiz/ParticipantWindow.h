#pragma once

#include <QMainWindow>
#include "ui_ParticipantWindow.h"

class ParticipantWindow : public QMainWindow
{
	Q_OBJECT

public:
	ParticipantWindow(QWidget *parent = nullptr);
	~ParticipantWindow();

private:
	Ui::ParticipantWindowClass ui;
};


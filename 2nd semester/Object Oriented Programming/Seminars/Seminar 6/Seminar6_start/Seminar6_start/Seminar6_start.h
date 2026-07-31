#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Seminar6_start.h"

class Seminar6_start : public QMainWindow
{
    Q_OBJECT

public:
    Seminar6_start(QWidget *parent = nullptr);
    ~Seminar6_start();

private:
    Ui::Seminar6_startClass ui;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Seminar6personal.h"

class Seminar6personal : public QMainWindow
{
    Q_OBJECT

public:
    Seminar6personal(QWidget *parent = nullptr);
    ~Seminar6personal();

private:
    Ui::Seminar6personalClass ui;
};


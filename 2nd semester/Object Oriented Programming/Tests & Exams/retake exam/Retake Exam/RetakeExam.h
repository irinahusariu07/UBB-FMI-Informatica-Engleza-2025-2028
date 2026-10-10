#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RetakeExam.h"

class RetakeExam : public QMainWindow
{
    Q_OBJECT

public:
    RetakeExam(QWidget *parent = nullptr);
    ~RetakeExam();

private:
    Ui::RetakeExamClass ui;
};


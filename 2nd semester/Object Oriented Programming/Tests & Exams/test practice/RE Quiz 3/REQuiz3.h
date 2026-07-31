#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_REQuiz3.h"

class REQuiz3 : public QMainWindow
{
    Q_OBJECT

public:
    REQuiz3(QWidget *parent = nullptr);
    ~REQuiz3();

private:
    Ui::REQuiz3Class ui;
};


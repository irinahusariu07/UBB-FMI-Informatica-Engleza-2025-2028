#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_REQuiz2.h"

class REQuiz2 : public QMainWindow
{
    Q_OBJECT

public:
    REQuiz2(QWidget *parent = nullptr);
    ~REQuiz2();

private:
    Ui::REQuiz2Class ui;
};


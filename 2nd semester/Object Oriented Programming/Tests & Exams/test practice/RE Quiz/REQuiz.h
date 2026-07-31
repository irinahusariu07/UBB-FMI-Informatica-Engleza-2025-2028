#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_REQuiz.h"

class REQuiz : public QMainWindow
{
    Q_OBJECT

public:
    REQuiz(QWidget *parent = nullptr);
    ~REQuiz();

private:
    Ui::REQuizClass ui;
};


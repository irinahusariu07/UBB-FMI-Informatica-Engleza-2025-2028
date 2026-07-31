#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_REArtAuction3.h"

class REArtAuction3 : public QMainWindow
{
    Q_OBJECT

public:
    REArtAuction3(QWidget *parent = nullptr);
    ~REArtAuction3();

private:
    Ui::REArtAuction3Class ui;
};


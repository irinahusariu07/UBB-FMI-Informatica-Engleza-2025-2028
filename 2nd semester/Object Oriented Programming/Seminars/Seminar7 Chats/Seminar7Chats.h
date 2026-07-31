#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Seminar7Chats.h"
#include "Observer.h"
#include"ChatSession.h"

class Seminar7Chats : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Seminar7Chats(ChatSession& cs, QWidget *parent = nullptr);
    ~Seminar7Chats();

private:
    Ui::Seminar7ChatsClass ui;
    ChatSession& cs;
};


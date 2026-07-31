#include "Seminar7Chats.h"

Seminar7Chats::Seminar7Chats(ChatSession& cs, QWidget *parent) : QMainWindow(parent), cs{cs}
{
    ui.setupUi(this);
}

Seminar7Chats::~Seminar7Chats()
{}


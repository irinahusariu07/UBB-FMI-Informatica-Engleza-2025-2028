#pragma once 
#include "Observer.h"
#include "QWidget"
#include"User.h"

class ChatWindow : public QWidget, public Observer
{
private:
	User user;
public:
	ChatWindow(User u) : user(u) {}
	void update() override;
	void sendMessage();
};
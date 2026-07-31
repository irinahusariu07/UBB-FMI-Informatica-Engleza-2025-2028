#pragma once
#include "Subject.h"
#include "UserMessage.h"

class ChatSession : public Subject
{
private:
	std::vector<UserMessage> user_message;
public:
	
	void addMessage(User* u, Message* m);
	std::vector<UserMessage> getMessage();
};

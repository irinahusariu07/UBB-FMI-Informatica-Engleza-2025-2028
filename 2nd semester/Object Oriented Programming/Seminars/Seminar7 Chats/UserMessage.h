#pragma once
#include <string>
#include"User.h"
#include"Message.h"

class UserMessage
{
private:
	std::string user, message;
public:
	UserMessage(const std::string& user, const std::string& message) : user{ user }, message{ message } {}
};
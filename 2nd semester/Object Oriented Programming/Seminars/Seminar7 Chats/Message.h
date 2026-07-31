#pragma once
#include <string>
#include <ctime>
class Message
{
private:
	std::string message; 
	std::time_t time_stamp; 

public:
	Message(std::time_t time_stamp, const std::string& message) : time_stamp(time_stamp), message(message) {}
};


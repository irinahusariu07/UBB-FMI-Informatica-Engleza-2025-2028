#pragma once
#include<string>
class User
{
private:
	std::string user_name;
	std::string name; 
public:
	User(const std::string& user_name, const std::string& name) : user_name(user_name), name(name) {}
};


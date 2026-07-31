#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

class Idea
{
	std::string description, status, creator; 
	int act; 

public:
	Idea(const std::string desc, const std::string& stat, const std::string& creat, int a) :
		description{ desc }, status{ stat }, creator{ creat }, act{ a } {
	}
	std::string getDesc() const { return description; }
	std::string getStatus() const { return status; }
	std::string getCreator() const { return creator; }
	int getAct() const { return act; }

	void setDesc(const std::string& newd) { description = newd; }
	void setStatus(const std::string& news) { status = news; }
};
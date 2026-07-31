#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Participant
{
	std::string name;
	int score;

public:
	Participant(const std::string& name) : name{ name }, score{ 0 } {}
	std::string getName() const { return name; }
	int getScore() const { return score; }
	void setScore(int news) { score = news; }
};
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Question
{
private:
	std::string text, answer; 
	int score, id; 

public:
	Question(int id, const std::string& txt, const std::string& ans, int sc) :
		id{ id }, text{ txt }, answer{ ans }, score{ sc } {
	}
	std::string getText() const { return this->text; }
	int getId() const { return this->id; }
	int getScore() const { return this->score; }
	std::string getAnswer() const { return this->answer; }
};
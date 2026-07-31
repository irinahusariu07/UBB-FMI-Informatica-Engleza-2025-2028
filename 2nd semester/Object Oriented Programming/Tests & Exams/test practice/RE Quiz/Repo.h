#pragma once
#include"Participant.h"
#include"Question.h"
#include<sstream>
#include<fstream>

class Repo
{
private:
	std::string qfile, pfile; 
	std::vector<Participant> participants; 
	std::vector<Question> questions; 

public:
	Repo(const std::string& q, const std::string& p) : qfile{ q }, pfile{ p } { readQuestionsFile(), readParticipantsFile(); }
	void readParticipantsFile();
	void readQuestionsFile();
	void writeQuestionsFile(); 

	std::vector<Participant>& getParticipants() { return participants; }
	std::vector<Question>& getQuestion() { return questions; }

	void addQuestion(Question& q);
};


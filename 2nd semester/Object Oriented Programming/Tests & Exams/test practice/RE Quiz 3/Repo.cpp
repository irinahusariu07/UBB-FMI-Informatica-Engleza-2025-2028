#include "Repo.h"

void Repo::readParticipantsFile()
{
	std::ifstream file(pfile);
	if (!file.is_open()) throw std::runtime_error("Cannot open participant file");
	participants.clear();
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string name, score;
		std::getline(ss, name, '|');
		std::getline(ss, score, '|');
		Participant p{ name }; //score e 0 
		participants.push_back(p);
	}
	file.close();
}

void Repo::readQuestionsFile()
{
	std::ifstream file(qfile);
	if (!file.is_open()) throw std::runtime_error("Cannot open question file");
	questions.clear();
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string id, txt, ans, sc;
		std::getline(ss, id, '|');
		std::getline(ss, txt, '|');
		std::getline(ss, ans, '|');
		std::getline(ss, sc, '|');

		Question q{ std::stoi(id), txt, ans, std::stoi(sc) };
		questions.push_back(q);
	}
	file.close();
}

void Repo::writeQuestionsFile()
{
	std::ofstream file(qfile);
	if (!file.is_open()) throw std::runtime_error("Cannot write to file");
	for (auto& q : questions)
	{
		file << q.getId() << "|" << q.getText() << "|" << q.getAnswer() << "|" << q.getScore() << "\n";
	}
	file.close();
}

void Repo::addQuestion(Question& q)
{
	questions.push_back(q);
	writeQuestionsFile();
}

void Repo::updateScore(const std::string name, int score)
{
	for (auto& p : participants)
	{
		if (p.getName() == name)
		{
			p.setScore(p.getScore() + score);
		}
	}
}





#pragma once
#include<sstream>
#include<fstream>
#include"Idea.h"
#include"Writer.h"

class Repo
{
private:
	std::vector<Idea> ideas; 
	std::vector<Writer> writers; 
	std::string wrfile, idfile; 

public:
	Repo(const std::string& wr, const std::string& id) : wrfile{ wr }, idfile{ id } { readWriterFile(); readIdeaFile(); }

	void readWriterFile();
	void readIdeaFile();
	void writeIdeaFile();
	//void writeEpisode(std::vector<Idea> towrite);

	std::vector<Idea> getIdeas() { return ideas; }
	std::vector<Writer> getWriters() { return writers; }

	void addIdea(Idea& i); 
	void acceptIdea(const std::string& desc, int act);
};


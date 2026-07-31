#pragma once
#include "Issue.h"
#include "User.h"
#include <fstream>
#include <sstream>

class Repo
{
private:
	std::vector<Issue> issues; 
	//std::vector<User> users; 
	std::string user_file; 
	std::string issue_file; 

public:
	Repo(const std::string& user, const std::string& issue) : user_file{ user }, issue_file{ issue } {
		readFromIssueFile(); 
	}
	void readFromIssueFile(); 
	void writeToIssueFile();
	std::vector<Issue> getIssues() const { return this->issues; }
	void addIssue(const Issue& i) { issues.push_back(i); writeToIssueFile(); }
	void updateIssue(const std::string& desc, const std::string& new_type, const std::string& new_solver);
	void removeIssue(const std::string& desc);
};


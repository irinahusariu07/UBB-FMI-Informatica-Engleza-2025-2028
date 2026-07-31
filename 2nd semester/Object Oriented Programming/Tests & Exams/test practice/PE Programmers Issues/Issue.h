#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<algorithm>

class Issue
{
	std::string description, type, reporter, solver; 
public:
	Issue(const std::string& description = "", const std::string& type = "open", const std::string& reporter = "", const std::string & solver = "")
	{
		this->description = description; 
		this->type = type; 
		this->reporter = reporter;
		this->solver = solver; 
	};
	std::string getDescription() const { return description; }
	std::string getType() const { return type; }
	std::string getReporter() const { return reporter; }
	std::string getSolver() const { return solver; }
	std::string toString() { return "Description: " + getDescription() + " Type: " + getType() + " Reporter: " + getReporter() + " Solver: " + getSolver() + "\n"; }
	void setType(const std::string& new_type) { this->type = new_type; }
	void setSolver(const std::string& new_solver) { this->solver = new_solver; }
};

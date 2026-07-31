#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;

public:
	Service(Repository& repo);

	void addStudent(const std::string& name, const std::string& group, double labGrade, double seminarGrade);
	int getSize() const;
	std::vector<Student>& getStudents();
};


#include "Service.h"

Service::Service(Repository& repo): repo {repo}
{
}

void Service::addStudent(const std::string& name, const std::string& group, double labGrade, double seminarGrade)
{
	Student stud{ name, group, labGrade, seminarGrade };
	this->repo.addStudent(stud);
}

int Service::getSize() const
{
	return this->repo.getSize();
}

std::vector<Student>& Service::getStudents()
{
	return this->repo.getStudents();
}

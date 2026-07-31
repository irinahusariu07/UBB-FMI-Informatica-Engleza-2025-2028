#include "Service.h"

void Service::addIssue(const std::string& desc, const std::string& reporter)
{
	if (desc == "" || reporter == "") throw std::runtime_error("Not a valid issue!");
	for (auto& i : repo.getIssues())
	{
		if (i.getDescription() == desc)
			throw std::runtime_error("Issue already exists!");
	}
	Issue i{ desc, "open", reporter, "" };
	repo.addIssue(i);
	notifyObservers();
}

void Service::resolveIssue(const std::string& desc, const std::string& solver)
{
	auto issues = repo.getIssues();
	bool modified = false; 
	for (auto& i : issues)
	{
		if (i.getDescription() == desc)
		{
			if (i.getType() != "open") throw std::runtime_error("Issue already closed!");
			else
			{
				repo.updateIssue(desc, "closed", solver);
				modified = true;
				notifyObservers();
			}
		}
	}
	if (modified != true) throw std::runtime_error("No issue matches the description!");
}

void Service::removeIssue(const std::string& desc)
{
	for (const auto& i : repo.getIssues()) 
	{
		if (i.getDescription() == desc) 
		{
			if (i.getType() != "closed") throw std::runtime_error("Only closed issues can be removed!");
			repo.removeIssue(desc);
			notifyObservers();
			return;
		}
	}
	throw std::runtime_error("Issue not found!");
}



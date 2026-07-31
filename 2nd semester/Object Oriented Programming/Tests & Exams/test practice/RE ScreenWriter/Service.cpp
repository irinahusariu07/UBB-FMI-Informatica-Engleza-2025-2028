#include "Service.h"

std::vector<Idea> Service::getIdeasSorted()
{
   std::vector<Idea>result = repo.getIdeas();
   std::sort(result.begin(), result.end(), [&](Idea i1, Idea i2)
	   {
		   return i1.getAct() < i2.getAct();
	   });
   return result; 
}

std::vector<Idea> Service::getAcceptedSorted()
{
	std::vector<Idea> result;
	for (auto& i : getIdeasSorted())
	{
		if (i.getStatus() == "accepted") result.push_back(i);
	}
	return result;
}

void Service::addIdea(const std::string& desc, const std::string& creat, int act)
{
	if (desc.empty() || act < 1 || act > 3) throw std::runtime_error("Invalid data"); 
	for (auto& i : getIdeasSorted())
	{
		if (i.getDesc() == desc && i.getAct() == act) throw std::runtime_error("Idea with this desc exists in this act"); 
	}
	Idea i{ desc, "proposed", creat, act };
	repo.addIdea(i); 
	notifyObs(); 
}


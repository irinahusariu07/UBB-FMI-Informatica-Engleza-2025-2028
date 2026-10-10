#pragma once
#include"Agent.h"
#include"Parcel.h"
#include<sstream>
#include <fstream>

class Repo
{
	std::vector<Agent> agents;
	std::vector<Parcel> parcels;
	std::string afile, pfile;

public:
	Repo(const std::string& afile, const std::string& pfile) : afile{ afile }, pfile{ pfile }
	{
		readAgentFile();
		readParcelFile();
	}

	void readAgentFile();
	void readParcelFile();
	void writeParcelFile();

	std::vector<Agent> getAgents() { return this->agents; }
	std::vector<Parcel> getParcels() { return this->parcels; }
	void addParcel(Parcel& p) { parcels.push_back(p); writeParcelFile(); }
	void updateParcel(const std::string& recipient);
};
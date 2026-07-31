#include "Service.h"
#include<algorithm>

void Service::addReport(const std::string& desc, const std::string& reporter, int lat, int longi, int status)
{
	// 1. Check for duplicates FIRST
	for (const auto& r : repo.getReports()) {
		if (r.getDesc() == desc && r.getLat() == lat && r.getLong() == longi)
			throw std::runtime_error("Report already exists!");
	}

	// 2. Validate Driver existence
	int dlat = 0, dlong = 0;
	bool found = false;
	for (auto& d : repo.getDrivers()) {
		if (d.getName() == reporter) {
			dlat = d.getLat(); dlong = d.getLong();
			found = true; break;
		}
	}
	if (!found) throw std::runtime_error("Driver not found!");
	if (getDistance(dlat, dlong, lat, longi) > 20) throw std::runtime_error("Too far!");

	// 3. Add and Notify
	Report r{ desc, reporter, lat, longi, false };
	repo.addReport(r); // Make sure addReport inside Repo calls writeReportFile()
	notifyObserver();
}

std::vector<Report> Service::getAllInRadius(const std::string& name)
{
	int dlat, dlong; 
	std::vector<Report> result; 
	for (auto& d : repo.getDrivers())
	{
		if (d.getName() == name)
		{
			dlat = d.getLat();
			dlong = d.getLong();
		}
	}
	for (auto& r : repo.getReports())
	{
		if (getDistance(dlat, dlong, r.getLat(), r.getLong()) <= 10)
			result.push_back(r);
	}
	return result;
}

void Service::validateReport(const std::string& desc, int lat, int longi, const std::string& validator)
{
	auto &reports = repo.getReports(); // Ensure this returns a reference!
	for (auto& re : reports) {
		if (re.getDesc() == desc && re.getLat() == lat && re.getLong() == longi) {
			if (re.getReporter() == validator) throw std::runtime_error("Cannot validate own!");
			if (re.checkValidator(validator)) throw std::runtime_error("Already validated!");

			re.addValidator(validator);

			if (re.getValidatorCount() >= 2 && !re.getStatus()) {
				re.setStatus(true);

				// Update file/RAM
				repo.updateReport(re);

				auto& dr = repo.getDriverByName(re.getReporter());
				dr.incrementScore();
				repo.updateDriver(dr); // Ensure this writes to drivers.txt!

				notifyObserver(); // THIS triggers the UI to re-read and apply BOLD formatting
			}
		}
	}
}







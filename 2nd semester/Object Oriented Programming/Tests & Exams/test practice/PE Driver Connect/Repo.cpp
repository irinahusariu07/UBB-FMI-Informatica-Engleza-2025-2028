#include "Repo.h"

void Repo::readDriverFile()
{
	std::ifstream file{ driver_file };
	if (!file.is_open()) throw std::runtime_error("Driver file corrupted!");
	drivers.clear(); 
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line); 
		std::string name, lats, longs, scores; 
		std::getline(ss, name, '|');
		std::getline(ss, lats, '|');
		int lat = std::stoi(lats);
		std::getline(ss, longs, '|');
		int longi = std::stoi(longs);
		std::getline(ss, scores, '|');
		int score = std::stoi(scores);
		Driver d{ name, lat, longi, score }; 
		drivers.push_back(d);
	}
	file.close(); 
}

void Repo::readReportFile() {
    std::ifstream file{ report_file };
    if (!file.is_open()) throw std::runtime_error("File corrupted!");
    reports.clear();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string desc, rep, lats, longs, statS;

        // Order: Desc | Reporter | Lat | Long | Status
        std::getline(ss, desc, '|');
        std::getline(ss, rep, '|');
        std::getline(ss, lats, '|');
        std::getline(ss, longs, '|');
        std::getline(ss, statS, '|');

        try {
            int lat = std::stoi(lats);
            int longi = std::stoi(longs);
            bool status = (statS == "true");

            reports.emplace_back(desc, rep, lat, longi, status);
        }
        catch (...) {
            throw std::runtime_error("Failed to parse line: " + line);
        }
    }
    file.close();
}

void Repo::writeReportFile() {
    std::ofstream file{ report_file };
    if (!file.is_open()) throw std::runtime_error("Cannot write to file");
    for (const auto& r : reports) {
        // Order: Desc | Reporter | Lat | Long | Status
        file << r.getDesc() << "|"
            << r.getReporter() << "|"
            << r.getLat() << "|"
            << r.getLong() << "|"
            << (r.getStatus() ? "true" : "false") << "\n";
    }
    file.close();
}

void Repo::updateReport(Report& r)
{
	for (auto& re : reports)
	{
		if (re.getDesc() == r.getDesc() && re.getLat() == r.getLat() && re.getLong() == r.getLong())

		{
			re = r;
			writeReportFile();
			return;
		}
	}
}

void Repo::updateDriver(Driver& d)
{
	for (auto& dr : drivers)
	{
		if (dr.getName() == d.getName()) dr = d;
	}
}


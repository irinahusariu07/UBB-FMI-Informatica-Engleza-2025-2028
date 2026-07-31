#include "Service.h"

std::vector<Report> Service::getAllInRadius(int dla, int dlo, int rad)
{
    std::vector<Report> result; 
    for (auto& r : repo.getReports())
    {
        if (computeDistance(r.getLatit(), r.getLongit(), dla, dlo) <= rad)
            result.push_back(r);
    }
    return result;
}

void Service::addReport(const std::string& desc, const std::string& reporter, int lat, int lon, int dla, int dlo)
{
    if (desc.empty()) throw std::runtime_error("Description empty");
    if (computeDistance(lat, lon, dla, dlo) > 20) throw std::runtime_error("Report location too far from driver location");

    for (auto& r : repo.getReports())
    {
        if (desc == r.getDesc() && lat == r.getLatit() && lon == r.getLongit())
        {
            throw std::runtime_error("Reported already");
        }
    }
    Report r{ desc, reporter, lat, lon, "false" };
    repo.addReport(r);
    notifyObs();
}

void Service::validateReport(const std::string& desc, int lat, int lon, const std::string& name)
{
    for (auto& r : repo.getReports())
    {
        if (r.getDesc() == desc && r.getLatit() == lat && r.getLongit() == lon)
        {
            if (r.getReporter() == name) throw std::runtime_error("Reporter cannot validate");
            for (auto& v : r.getValidators())
            {
                if (v == name) throw std::runtime_error("You already validated this report");
            }
            repo.updateStatus(desc, lat, lon, name);
        }
    }
    notifyObs();
}


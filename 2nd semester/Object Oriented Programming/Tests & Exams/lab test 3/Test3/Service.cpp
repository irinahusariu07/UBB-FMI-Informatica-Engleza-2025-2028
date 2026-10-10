#include "Service.h"

void Service::readFromFile()
{
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("FILE CORRUPTED");
    std::string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string shour, smin, status, destination, sdelay;
        int hour, minute, delay; 
        std::getline(ss, shour, ';');
        hour = stoi(shour);
        std::getline(ss, smin, ';');
        minute = stoi(smin);
        std::getline(ss, status, ';');
        std::getline(ss, destination, ';');
        std::getline(ss, sdelay, ';');
        delay = stoi(sdelay);
        Airport a{ hour, minute, status, destination, delay };
        flights.push_back(a); 
    }
    file.close();
}


std::vector<Airport> Service::getAll()
{
    std::sort(flights.begin(), flights.end(),[] (Airport& a, Airport& b){
        return (a.getHour() < b.getHour() || (a.getHour() == b.getHour() && a.getMinute() < b.getMinute()));
            });
    return this->flights; 
}

std::vector<Airport> Service::getWithDelay(int min_delay)
{
    std::vector<Airport> by_delay;
    std::vector<Airport> all = this->getAll(); 
    for (auto& f : all)
    {
        if (f.getDelay() >= min_delay) by_delay.push_back(f);
    }
    return by_delay; 
}

std::vector<Airport> Service::getAfterHour(int min_hour)
{
    std::vector<Airport> by_hour; 
    std::vector<Airport> all = this->getAll(); 
    for (auto& f : all)
    {
        if (f.getHour() >= min_hour) by_hour.push_back(f);
    }
    if (by_hour.size() == 0) throw std::runtime_error("No such flights"); 
    return by_hour; 
}





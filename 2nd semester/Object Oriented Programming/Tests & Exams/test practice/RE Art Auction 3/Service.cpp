#include "Service.h"

std::vector<Item> Service::getItems()
{
    std::vector<Item> result = repo.getItems();
    std::sort(result.begin(), result.end(), [&](Item i1, Item i2)
        {
            return i1.getCurrent() < i2.getCurrent();
        });
    return result;
}

std::vector<Item> Service::filterByCateg(const std::string& cat)
{
    std::vector<Item> result;
    for (auto& i : this->getItems())
    {
        if (i.getCategory() == cat) result.push_back(i);
    }
    return result;
}

void Service::addOffer(const std::string& name, int id, const std::string& date, int value)
{
    repo.addOffer(name, id, date, value);
    notifyObservers();
}

void Service::addItem(const std::string& name, const std::string& category, int price)
{
    if (name.empty() || price <= 0) throw std::runtime_error("Invalid data");
    for (auto& i : getItems())
    {
        if (i.getName() == name) throw std::runtime_error("Item already exists");
    }
    Item i{ name, category, price, {} };
    repo.addItem(i);
    notifyObservers();
}

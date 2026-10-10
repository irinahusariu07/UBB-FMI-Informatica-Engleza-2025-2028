#include "Service.h"
#include <stdexcept>
#include <iterator>



Service::Service(Repo& repository, AdoptionList* list) : repository {repository}, adoption_list {list}
{
}

void Service::addDog(std::string breed, std::string name, int years, int months, std::string photo_link)
{
	Dog new_dog{ breed, name, years, months, photo_link }; 
	DogValidator::validate(new_dog);
	monthsToYear(new_dog.getAge());

	if (repository.findDog(breed, name) != -1) //there is a dog with the same name and breed
	{
		throw DuplicateDogException();
	}
	this->repository.addDB(new_dog);
}

int Service::getNumberOfDogs() const
{
	return this->repository.getDBSize();
}

void Service::removeDog(std::string breed, std::string name)
{
	int dog_id = repository.findDog(breed, name);
	//dog not found
	if (dog_id == -1) throw InexistentDogException();
	repository.removeDB(dog_id);
}

void Service::monthsToYear(Age& age)
{
	if (age.getMonths() >= 12)
	{
		int add_year = age.getMonths() / 12; 
		age.setMonths(age.getMonths() % 12);
		age.setYears(age.getYears() + add_year); 
	}
}

void Service::updateDog(const std::string& breed, const std::string& name, const std::string& up_breed, const std::string& up_name, const int up_years, const int up_months, const std::string& up_link)
{
	int dog_id = repository.findDog(breed, name); 
	//dog not found 
	if (dog_id == -1) throw InexistentDogException();
	Dog new_dog{ up_breed, up_name, up_years, up_months, up_link };
	DogValidator::validate(new_dog);
	monthsToYear(new_dog.getAge()); 

	repository.updateDB(breed, name, new_dog); 
}


void Service::checkString(const std::string& text)
{
	if (text == "") throw std::runtime_error("Field cannot be empty");
}

void Service::checkAge(Age age)
{
	if (age.getYears() < 0 || age.getMonths() < 0)
		throw std::runtime_error("Age cannot be negative");
}

bool Service::compareAges(Age& dogAge,  Age& givenAge)
{
	if (dogAge.getYears() < givenAge.getYears()) return true; 
	else if (dogAge.getYears() == givenAge.getYears())
	{
		if (dogAge.getMonths() < givenAge.getMonths()) return true; 
	}
	return false; 
}

std::vector<Dog> Service::filterDogBreedByAge(const std::string& breed, int years, int months)
{
	std::vector<Dog> filtered; 
	std::vector<Dog> all = repository.getAllDogs();
	Age givenAge { years, months }; 
	std::copy_if(all.begin(), all.end(), std::back_inserter(filtered), [&](Dog& d)
		{
			return (breed == "" || d.getBreed() == breed) && compareAges(d.getAge(), givenAge);
		});
	return filtered; 
}

void Service::adoptDog(Dog d)
{
	this->adoption_list->add(d); //add dog to adoption list
	int id = repository.findDog(d.getBreed(), d.getName());
	repository.removeDB(id); //also remove it from main shelter database 
	this->adoption_list->writeToFile();
}

void Service::openAdoptionFile() const
{
	std::string path = this->adoption_list->getFilename();
	std::string command = "start " + path;
	system(command.c_str());
}

void Service::addDefaultDogs()
{
	addDog("chow chow", "ollie", 1, 2, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Chow%20Chow%204.jpg");
	addDog("alaskan malamute", "martin", 0, 9, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Alaskan%20Malamute%203.jpg");
	addDog("bull terrier", "ivy", 0, 3, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Bull%20Terrier%20%203.jpg");
	addDog("dachshund", "paul", 1, 5, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Dachshund%204.jpg");
	addDog("newfoundland", "willow", 1, 9, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Newfoundland%204.jpg");
	addDog("boxer", "bjorn", 3, 0, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Boxer%204.jpg");
	addDog("shepherd", "nord", 2, 2, "https://consumer-cms.petfinder.com/sites/default/files/images/content/German%20Shepherd%20%202.jpg");
	addDog("whippet", "daisy", 0, 9, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Whippet%203.jpg");
	addDog("irish setter", "ronald", 2, 0, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Irish%20Setter%203.jpg");
	addDog("basset hound", "hank", 4, 0, "https://www.zooplus.ro/ghid/wp-content/uploads/2025/01/basset-hound-im-grass.webp");
	addDog("shepherd", "zeus", 0, 5, "https://images.squarespace-cdn.com/content/v1/63deb27b4a085e065cb68f2a/22c509d7-20ad-4463-bb59-bcc7d3f21a0d/10-week-old-german-shepherd-puppy-red-and-black.jpg");
	addDog("cocker", "charlie", 1, 0, "https://consumer-cms.petfinder.com/sites/default/files/images/content/English%20Cocker%20Spaniel%203.jpg");
	addDog("giant schnauzer", "pepper", 0, 7, "https://www.dogster.com/wp-content/uploads/2024/02/Giant-Schnauzer-dog-standing-on-grass_Eliska-Zeiskova_Shutterstock.jpeg");
	addDog("border collie", "oreo", 2, 1, "https://consumer-cms.petfinder.com/sites/default/files/images/content/Border%20Collie%203.jpg");
	addDog("australian shepherd", "archie", 1, 6, "https://www.animalbehaviorcollege.com/wp-content/uploads/2015/06/australian-shepherd.jpg");
}





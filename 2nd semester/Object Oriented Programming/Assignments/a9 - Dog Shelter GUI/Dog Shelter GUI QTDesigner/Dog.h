#pragma once
#include<string>
#include<cassert>
#include<iostream>
#include<sstream>

class Age 
{
private:
	int months;
	int years; 

public:
	//Age(); 
	Age(int years = 0, int months = 0); 
	//months getter 
	int getMonths() const { return months; }
	//years getter
	int getYears() const { return years; }
	//months setter
	void setMonths(int new_months) { this->months = new_months; }
	//years setter 
	void setYears(int new_years) { this->years = new_years; }
};

class Dog
{

private:
	std::string breed; 
	std::string name; 
	Age age; 
	std::string photo_link; 
	friend std::ostream& operator<<(std::ostream& out, const Dog& d);
	friend std::istream& operator>>(std::istream& in, Dog& d);

public:
	//default constructor 
	Dog(const std::string& breed = "", const std::string& name = "", int years = 0, int months = 0, const std::string& photo_link = ""); 
	//breed getter 
	std::string getBreed() const { return breed; }
	//name getter 
	std::string getName() const { return name; }
	//link getter 
	std::string getLink() const { return photo_link; }
	//age obj getter 
	Age& getAge() { return age; }
	//breed setter
	void setBreed(std::string new_breed) { this->breed = new_breed; }
	//name setter
	void setName(std::string new_name) { this->name = new_name; }
	//link setter 
	void setLink(std::string new_link) { this->photo_link = new_link; }
};


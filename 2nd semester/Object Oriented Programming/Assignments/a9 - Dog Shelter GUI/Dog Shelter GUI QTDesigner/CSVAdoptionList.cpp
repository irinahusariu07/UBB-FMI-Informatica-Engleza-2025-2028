#include "CSVAdoptionList.h"

void CSVAdoptionList::writeToFile()
{
	std::ofstream file(this->filename); //create a file for writing 
	file << "Breed,Name,Years,Months,Link\n";
	//write each line - elements separated by comma 
	for (auto& d : adopted_dogs)
	{
		file << d.getBreed() << ","
			<< d.getName() << ","
			<< d.getAge().getYears() << ","
			<< d.getAge().getMonths() << ","
			<< d.getLink() << "\n";
	}
	file.close();
}

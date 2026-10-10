#include <iostream>
#include "Dog.h"
#include <vector>
#include <algorithm>
#include "Repo.h"
#include "Service.h"
#include "UI.h"
#include "tests.h"
#include "HTMLAdoptionList.h"
#include "CSVAdoptionList.h"
#include "AdoptionList.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    testAll();
    {
        
        std::cout << "\n \n \n \n";
        Repo repo{ "dog_shelter.txt" };
        
        std::cout << "Choose adoption list format: \n";
        std::cout << " 1. CSV \n";
        std::cout << " 2. HTML \n";
        
        AdoptionList* adoptions = nullptr; 
        while (adoptions == nullptr)
        {
            std::string choice; 
            std::cout << " > ";
            std::cin >> choice;
            std::cout << "\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == "1") adoptions = new CSVAdoptionList{ "adoption_list.csv" };
            else if (choice == "2") adoptions = new HTMLAdoptionList{ "adoption_list.html" };
            else std::cout << "Invalid choice!\n";
        }
        Service service{ repo , adoptions};
        if (service.getNumberOfDogs() == 0) service.addDefaultDogs(); //only add defaults if file is empty
        UI ui{ service };

        ui.run();
        delete adoptions; 
    }

    std::cout << "\n \n \n \n";
    std::cout << "\n--- MEMORY CHECK ---\n";
    if (_CrtDumpMemoryLeaks()) std::cout<<"Leaks found!\n";
    else std::cout<<"No leaks found.\n";
    
    return 0;
}
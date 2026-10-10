#include <iostream>
#include "Dog.h"
#include "DynamicVector.h"
#include "Repo.h"
#include "Service.h"
#include "UI.h"
#include "tests.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    testAll();
   /* {
        std::cout << "\n \n \n \n";
        Repo repo;
        Service service{ repo };
        service.addDefaultDogs();
        UI ui{ service };

        ui.run();
    }

    std::cout << "\n \n \n \n";
    std::cout << "\n--- MEMORY CHECK ---\n";
    if (_CrtDumpMemoryLeaks()) std::cout<<"Leaks found!\n";
    else std::cout<<"No leaks found.\n";
    
    return 0;*/
}
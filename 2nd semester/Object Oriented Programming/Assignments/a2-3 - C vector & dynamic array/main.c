#include <stdio.h>
#include "ui.h"
#include "services.h"
#include "repository.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    run_all_tests();
    //create each layer 
    Repo* repo = createRepo();
    Service* service = createService(repo);

    //add default 10 products
    addDefaultProducts(service);

    UI* ui = createUI(service);
    startUI(ui);

    //destroy 
    destroyUI(ui);
    destroyService(service);
    destroyRepo(repo);

    //int* a = malloc(sizeof(int) * 4);
    printf("\n \n \n \n");
    printf("\n--- MEMORY CHECK ---\n");
    if (_CrtDumpMemoryLeaks())
        printf("Leaks found!\n");
    else
        printf("No leaks found.\n");

    return 0;
}

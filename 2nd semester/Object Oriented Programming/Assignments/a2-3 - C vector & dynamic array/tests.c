#include "tests.h"
#include "domain.h"
#include "repository.h"
#include "services.h"
#include <assert.h>
#include <stdio.h>

void run_all_tests()
{
    test_product();
    test_vector();
    test_repo();
    test_service();
    printf("All tests passed successfully!\n");
}

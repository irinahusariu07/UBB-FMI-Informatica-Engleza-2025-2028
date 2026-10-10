#pragma once
#include "repository.h"

typedef struct {
    Repo* repository;

    DynamicVector* undo_stack;
    DynamicVector* redo_stack;

}Service;

/*
* create services based on the repo
*/
Service* createService(Repo* r);
/*
* function to destroy services
*/
void destroyService(Service* s);

/*
* function to add a product given by all info about it
* it checks if the fields are valid - return -1 if not
* also if the product already exists (identified by name supplier date) it only updates the quantity
*/
int addProductService(Service* s, char* name, char* supplier, int quantity, Date expiration_date);

/*
    function that deletes a product given by unique identifiers name, supplier, exp_date
    will return 1 if success, 0 if product not found, -1 if service issue
*/
int deleteProductService(Service* s, char* name, char* supplier, Date expiration_date);

/*
* function that updates the name of a product
* returns -1 if service error
* returns -2 if not valid input
* returns 0 if not found
* returns 1 if update successful
*/
int updateProductNameService(Service* s, char* name, char* supplier, Date expiration_date, char* new_name);

/*
* function that updates the supplier of a product
* returns -1 if service error
* returns -2 if not valid input
* returns 0 if not found
* returns 1 if update successful
*/
int updateProductSupplierService(Service* s, char* name, char* supplier, Date expiration_date, char* new_supplier);

/*
* function that updates the quantity of a product
* returns -1 if service error
* returns -2 if not valid input
* returns 0 if not found
* returns 1 if update successful
*/
int updateProductQuantityService(Service* s, char* name, char* supplier, Date expiration_date, int new_quantity);

/*
* function that updates the exp_date of a product
* returns -1 if service error
* returns -2 if not valid input
* returns 0 if not found
* returns 1 if update successful
*/
int updateProductExpirationService(Service* s, char* name, char* supplier, Date expiration_date, Date new_date);

/*
* function to get all products in repo 
*/
DynamicVector* getAllProducts(Service* s);

/*
* function that gets all expired products containing a given string
* parameter - today's date
* parameter - string that should be searched for (if empty - return all expired products)
* returns the vector of expired products
*/
DynamicVector* filterExpiredProducts(Service* s, char* string, Date today);

/*
* function that filters all products containing a given string in their name
* parameter - the string to be searched
*/
DynamicVector* filterName(Service* s, char* string);

/*
* function that creates a vector with all products from a certain supplier, with quantity less than a given value, ordered ascending by quantity
* parameter - supplier = given supplier
* parameter - quantity = given limit value
*/
DynamicVector* displayShortSupply(Service* s, char* supplier, int quantity);

//funtion to check validity of date 
int checkDate(Date date);
//function to check validity of quantity 
int checkQuantity(int quantity);
//function to check validity of name
int checkName(char* name);
//function to check validity of supplier
int checkSupplier(char* supplier);

/*
* add 10 default products
*/
void addDefaultProducts(Service* s);

//function that sorts an array ascending
DynamicVector* sortAscending(DynamicVector* v);
//function that sorts an array descending
DynamicVector* sortDescending(DynamicVector* v);
/*
* check if a date is past expiration date - used to check if product is expired
*/
int isExpired(Date exp_date, Date today);

//function that returns a copy of a vector
DynamicVector* copyVector(DynamicVector* v);
//function that saves state - adds current repo to an array - used in undo redo
void saveState(Service* s);
//undo functionality
int undo(Service* s);
//redo functionality
int redo(Service* s);

void test_service();
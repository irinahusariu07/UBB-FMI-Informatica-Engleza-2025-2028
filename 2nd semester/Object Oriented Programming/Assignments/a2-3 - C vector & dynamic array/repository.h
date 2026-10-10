#pragma once
#include "dynamicVector.h"
#include "domain.h"

typedef struct {
	DynamicVector* products;
}Repo;

/*
* function to create a repo - it allocates 10 spaces in the dynamic vector for the default products
*/
Repo* createRepo();
/*
* function to destroy a repo
*/
void destroyRepo(Repo* r);

/*
* function to find a product uniquely defined by its name supplier and expiration date
* returns index (position) at which the product can be found inside the vector of products or -1 if not found
*/
int findProduct(Repo* r, char* name, char* supplier, Date expiration_date);
/*
* function to add a product to the vector
*/
void addProductRepo(Repo* r, Product* prod);
/*
* function to remove a product given by index from the vector
*/
void deleteProductRepo(Repo* r, int index);
/*
* function to change a product at a position with a new given product - basically update
*/
void updateProductRepo(Repo* r, int index, Product* prod);
/*
* function to get a product at a given index
*/
TElem getProductRepo(Repo* r, int index);
/*
* function to get the size of a vector 
*/
int getVectorSizeRepo(DynamicVector* v);

/*
* function that returns a list of all products
*/
DynamicVector* getAllProductsRepo(Repo* r);
/*
* function to set all products in a repo - used for undo redo
*/
void setProductsRepo(Repo* r, DynamicVector* new_vector);

void test_repo();
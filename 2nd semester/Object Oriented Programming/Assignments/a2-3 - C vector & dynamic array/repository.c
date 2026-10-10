#include "repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Repo* createRepo()
{
	Repo* r = malloc(sizeof(Repo));
	if (r == NULL) return NULL;

	//10 default entries 
	r->products = createDynamicVector(10);
	return r;
}


void destroyRepo(Repo* r)
{
	if (r == NULL) return;

	destroyDynamicVector(r->products, (void (*)(TElem))destroyProduct);
	free(r);
}


int findProduct(Repo* r, char* name, char* supplier, Date expiration_date)
{
	int size = getSize(r->products);
	for (int i = 0; i < size; i++)
	{
		Product* curr_prod = getElem(r->products, i);
		Date d = getDate(curr_prod);
		//check if current product is the same with the one that is searched 
		//name supplier and expiration date match 
		if (strcmp(getName(curr_prod), name) == 0 &&
			strcmp(getSupplier(curr_prod), supplier) == 0 &&
			d.day == expiration_date.day &&
			d.month == expiration_date.month &&
			d.year == expiration_date.year)
			return i;
	}
	return -1;
}


void addProductRepo(Repo* r, Product* prod)
{
	if (prod == NULL) return;
	addElem(r->products, prod);
}


void deleteProductRepo(Repo* r, int index)
{
	deleteElem(r->products, index, (void(*)(TElem))destroyProduct);
}


void updateProductRepo(Repo* r, int index, Product* prod)
{
	if (prod == NULL) return;
	updateElem(r->products, index, prod, (void(*)(TElem))destroyProduct);
}

TElem getProductRepo(Repo* r, int index)
{
	return getElem(r->products, index);
}

int getVectorSizeRepo(DynamicVector* v)
{
	return v->size;
}

DynamicVector* getAllProductsRepo(Repo* r)
{
	return r->products;
}

void setProductsRepo(Repo* r, DynamicVector* new_vector)
{
	r->products = new_vector;
}

void test_repo()
{
	Repo* r = createRepo();
	assert(r != NULL);
	assert(getVectorSizeRepo(getAllProductsRepo(r)) == 0);

	Date d = { 2026, 4, 20 };
	Product* p = createProduct("flour", "boromir", 2, d);
	addProductRepo(r, p);

	assert(getVectorSizeRepo(getAllProductsRepo(r)) == 1);

	int idx = findProduct(r, "flour", "boromir", d);
	assert(idx == 0);

	Product* p_get = (Product*)getProductRepo(r, idx);
	assert(strcmp(getName(p_get), "flour") == 0);

	Date d2 = { 2027, 5, 21 };
	Product* p2 = createProduct("bread", "bakery", 5, d2);
	updateProductRepo(r, idx, p2);

	assert(getVectorSizeRepo(getAllProductsRepo(r)) == 1);
	assert(strcmp(getName((Product*)getProductRepo(r, 0)), "bread") == 0);

	deleteProductRepo(r, 0);
	assert(getVectorSizeRepo(getAllProductsRepo(r)) == 0);

	destroyRepo(r);
}

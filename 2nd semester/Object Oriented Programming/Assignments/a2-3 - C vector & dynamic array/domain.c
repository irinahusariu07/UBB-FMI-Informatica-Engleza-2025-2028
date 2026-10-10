#include "domain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


Product* createProduct(char* name, char* supplier, int quantity, Date expiration_date)
{
	Product* prod = malloc(sizeof(Product));
	if (prod == NULL) return NULL;

	prod->name = malloc((strlen(name) + 1) * sizeof(char));
	if (prod->name == NULL)
	{
		free(prod);
		return NULL;
	}
	prod->supplier = malloc((strlen(supplier) + 1) * sizeof(char));
	if (prod->supplier == NULL)
	{
		free(prod);
		return NULL;
	}
	prod->quantity = quantity;
	prod->expiration_date = expiration_date;

	strcpy(prod->name, name);
	strcpy(prod->supplier, supplier);

	return prod;
}


void destroyProduct(Product* prod)
{
	if (prod == NULL) return;

	free(prod->name);
	free(prod->supplier);
	free(prod);
}

char* getName(Product* prod)
{
	return prod->name;
}

void setName(Product* prod, char* new_name)
{
	free(prod->name);

	prod->name = malloc(strlen(new_name) + 1);
	if (prod->name == NULL) return;

	strcpy(prod->name, new_name);
}

char* getSupplier(Product* prod)
{
	return prod->supplier;
}

void setSupplier(Product* prod, char* new_supplier)
{
	free(prod->supplier);

	prod->supplier = malloc(strlen(new_supplier) + 1);
	if (prod->supplier == NULL) return;

	strcpy(prod->supplier, new_supplier);
}

int getQuantity(Product* prod)
{
	return prod->quantity;
}

void setQuantity(Product* prod, int new_quantity)
{
	prod->quantity = new_quantity;
}

Date getDate(Product* prod)
{
	return prod->expiration_date;
}

void setDate(Product* prod, Date new_date)
{
	prod->expiration_date = new_date;
}


void test_product()
{
	//create an expiration date
	Date d;
	d.year = 2026;
	d.month = 4;
	d.day = 20;
	//create a new product
	Product* p = createProduct("flour", "boromir", 2, d);
	//test each product field
	assert(strcmp(p->name, "flour") == 0);
	assert(strcmp(p->supplier, "boromir") == 0);
	assert(p->quantity == 2);
	assert(p->expiration_date.year == 2026);
	assert(p->expiration_date.month == 4);
	assert(p->expiration_date.day == 20);
	//destroy the test product
	destroyProduct(p);
}


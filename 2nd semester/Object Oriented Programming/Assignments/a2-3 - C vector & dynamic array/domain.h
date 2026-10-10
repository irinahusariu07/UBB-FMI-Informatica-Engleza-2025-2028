#pragma once

typedef struct {
	int year;
	int month;
	int day;
}Date;

typedef struct {
	char* name;
	char* supplier;
	int quantity;
	Date expiration_date;
}Product;


/*
* function to create a product with a given name, supplier, quantity and exp date
* returns the product
*/
Product* createProduct(char* name, char* supplier, int quantity, Date expiration_date);

/*
* function that destroys a product
* parameter - pointer to the product to destroy
*/
void destroyProduct(Product* prod);

//name getter
char* getName(Product* prod);
//name setter
void setName(Product* prod, char* new_name);

//supplier getter
char* getSupplier(Product* prod);
//supplier setter
void setSupplier(Product* prod, char* new_supplier);

//quatity getter
int getQuantity(Product* prod);
//quantity setter
void setQuantity(Product* prod, int new_quantity);

//date getter
Date getDate(Product* prod);
//date setter
void setDate(Product* prod, Date new_date);

void test_product();


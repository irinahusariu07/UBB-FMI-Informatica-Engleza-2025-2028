#pragma once
#include "services.h"

typedef struct {
	Service* service;
}UI;

/*
* create UI
*/
UI* createUI(Service* s);

/*
* destory UI
*/
void destroyUI(UI* ui);


void startUI(UI* ui);
void printMenu();

/*
* UI function to add a product - expects user input of name supplier quantity date - checks and prints error messages regarding product validity
*/
void addProductUI(UI* ui);

/*
* UI function to delete a product - expects user input for name supplier date - checks and prints error messages if product not found
*/
void deleteProductUI(UI* ui);

/*
* functions to update name of product
* check and print errror messages if product not found or if the change cant be made because of invalid input
*/
void updateNameUI(UI* ui);
/*
* functions to update supplier of product
* check and print errror messages if product not found or if the change cant be made because of invalid input
*/
void updateSupplierUI(UI* ui);
/*
* functions to update quantity of product
* check and print errror messages if product not found or if the change cant be made because of invalid input
*/
void updateQuantityUI(UI* ui);
/*
* functions to update date of product
* check and print errror messages if product not found or if the change cant be made because of invalid input
*/
void updateExpDateUI(UI* ui);

/*
* UI function to print all expired products containing a string
* expects user input of a string - if empty then shows all expired products
*/
void filterExpiredUI(UI* ui);
/*
* UI function to filter products containing a given string in their name
* expects user input for string
*/
void filterNameUI(UI* ui);
/*
* UI function to display all products from a given supplier with quantity less than a given value sorted ascending by quantity
*/
void shortSupplyUI(UI* ui);
/*
* UI function to print all existing products
*/
void showAllProductsUI(UI* ui);

/*
* function that lowers all characters from a string
*/
void toLowerStr(char* str);

/*
* function to remove extra spaces
*/
void strip(char* str);

/*
* function that returns the systems date (current date)
*/
Date TodayDate();

#include "ui.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>


UI* createUI(Service* s)
{
    UI* ui = malloc(sizeof(UI));
    if (ui == NULL) return NULL;
    ui->service = s;
    return ui;
}

void destroyUI(UI* ui)
{
    if (ui == NULL) return;
    free(ui);
}


void toLowerStr(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = tolower(str[i]);
}


void strip(char* str)
{
    if (str == NULL) return;

    int start = 0;
    int end = strlen(str) - 1;

    // remove leading spaces
    while (isspace((unsigned char)str[start])) start++;

    // remove trailing spaces
    while (end > start && isspace((unsigned char)str[end])) end--;

    // shift string left
    int i = 0;
    while (start <= end)
    {
        str[i++] = str[start++];
    }

    str[i] = '\0';
}


Date TodayDate()
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    Date d;
    d.year = t->tm_year + 1900;
    d.month = t->tm_mon + 1;
    d.day = t->tm_mday;

    return d;
}

void printMenu()
{
    printf("\nBread'n Bagel Management\n");
    printf("Add material - add\n");
    printf("Delete material - delete\n");
    printf("Update name - update name\n");
    printf("Update supplier - update supplier\n");
    printf("Update quantity - update quantity\n");
    printf("Update expiration date - update date\n");
    printf("Filter expired products - expired\n");
    printf("Show all materials from a given supplier which are short in supply - short supply\n");
    printf("Filter all products containing a given string in their name - filter name\n");
    printf("Show all materials - all\n");
    printf("undo\n");
    printf("redo\n");
    printf("exit");
}


void addProductUI(UI* ui)
{
    char name[50];
    char supplier[50];
    int quantity;
    Date d;

    printf("Product name: \n");
    fgets(name, 50, stdin);
    strip(name);
    toLowerStr(name);

    printf("Supplier: \n");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    char q[50];
    printf("Quantity: \n");
    fgets(q, 50, stdin);
    if (sscanf(q, "%d", &quantity)!=1)
    {
        printf("Invalid input for quantity!");
        return;
    }

    printf("Expiration date (year month day): \n");
    char date[50];
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &d.year, &d.month, &d.day)!=3)
    {
        printf("Invalid input for date!");
        return;
    }

    int status = addProductService(ui->service, name, supplier, quantity, d);
    if (status == 1) printf("Added successfully!");
    else if (status == -1) printf("Not valid product!");
}


void deleteProductUI(UI* ui)
{
    char name[50];
    char supplier[50];
    Date d;

    printf("Product name: \n");
    fgets(name, 50, stdin);
    strip(name);
    toLowerStr(name);

    printf("Supplier: \n");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    printf("Expiration date (year month day): \n");
    char date[50];
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &d.year, &d.month, &d.day) != 3)
    {
        printf("Invalid input for date!");
        return;
    }

    int status = deleteProductService(ui->service, name, supplier, d);
    if (status == -1) printf("Service error");
    else if (status == 0) printf("Product not found!");
    else if (status == 1) printf("Deleted successfully!");

}


void updateNameUI(UI* ui)
{
    char new_name[50];
    char name[50];
    char supplier[50];
    Date d;

    printf("Product name: \n");
    fgets(name, 50, stdin);
    strip(name);
    toLowerStr(name);

    printf("Supplier: \n");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    printf("Expiration date (year month day): \n");
    char date[50];
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &d.year, &d.month, &d.day) != 3)
    {
        printf("Invalid input for date!");
        return;
    }

    printf("New name: \n");
    fgets(new_name, 50, stdin);
    strip(new_name);
    toLowerStr(new_name);

    int status = updateProductNameService(ui->service, name, supplier, d, new_name);
    if (status == -1) printf("Service error\n");
    else if (status == -2) printf("Invalid name\n");
    else if (status == 0) printf("Product not found\n");
    else if (status == 1) printf("Updated successfully");
}

void updateSupplierUI(UI* ui)
{
    char new_supplier[50];
    char name[50];
    char supplier[50];
    Date d;

    printf("Product name: \n");
    fgets(name, 50, stdin);
    strip(name);
    toLowerStr(name);

    printf("Supplier: \n");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    printf("Expiration date (year month day): \n");
    char date[50];
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &d.year, &d.month, &d.day) != 3)
    {
        printf("Invalid input for date!");
        return;
    }

    printf("New supplier: \n");
    fgets(new_supplier, 50, stdin);
    strip(new_supplier);
    toLowerStr(new_supplier);

    int status = updateProductSupplierService(ui->service, name, supplier, d, new_supplier);
    if (status == -1) printf("Service error\n");
    else if (status == -2) printf("Invalid supplier\n");
    else if (status == 0) printf("Product not found\n");
    else if (status == 1) printf("Updated successfully");
}

void updateQuantityUI(UI* ui)
{
    int new_quantity;
    char name[50];
    char supplier[50];
    Date d;

    printf("Product name: \n");
    fgets(name, 50, stdin);
    strip(name);
    toLowerStr(name);

    printf("Supplier: \n");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    printf("Expiration date (year month day): \n");
    char date[50];
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &d.year, &d.month, &d.day) != 3)
    {
        printf("Invalid input for date!");
        return;
    }

    char q[50];
    printf("New quantity: \n");
    fgets(q, 50, stdin);
    if (sscanf(q, "%d", &new_quantity) != 1)
    {
        printf("Invalid input for quantity!");
        return;
    };

    int status = updateProductQuantityService(ui->service, name, supplier, d, new_quantity);
    if (status == -1) printf("Service error\n");
    else if (status == -2) printf("Invalid quantity\n");
    else if (status == 0) printf("Product not found\n");
    else if (status == 1) printf("Updated successfully");
}

void updateExpDateUI(UI* ui)
{
    Date new_date;
    char name[50];
    char supplier[50];
    Date d;

    printf("Product name: \n");
    fgets(name, 50, stdin);
    strip(name);
    toLowerStr(name);

    printf("Supplier: \n");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    printf("Expiration date (year month day): \n");
    char date[50];
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &d.year, &d.month, &d.day) != 3)
    {
        printf("Invalid input for date!");
        return;
    }

    printf("New expiration date (year month day): \n");
    fgets(date, 50, stdin);
    if (sscanf(date, "%d %d %d", &new_date.year, &new_date.month, &new_date.day) != 3)
    {
        printf("Invalid input for date!");
        return;
    }

    int status = updateProductExpirationService(ui->service, name, supplier, d, new_date);
    if (status == -1) printf("Service error\n");
    else if (status == -2) printf("Invalid date\n");
    else if (status == 0) printf("Product not found\n");
    else if (status == 1) printf("Updated successfully");
}


void filterExpiredUI(UI* ui)
{
    char text[50];
    printf("Enter string (empty -> all expired): ");
    fgets(text, 50, stdin);
    strip(text);
    toLowerStr(text);

    Date today = TodayDate();
    DynamicVector* expired_products = filterExpiredProducts(ui->service, text, today);
    int size = getSize(expired_products);

    if (size == 0)
    {
        printf("No expired products found.\n");
        destroyDynamicVector(expired_products, (void(*)(TElem))destroyProduct);
        return;
    }
    for (int i = 0; i < size; i++)
    {
        Product* prod = getElem(expired_products, i);
        Date d = getDate(prod);
        printf("%s | %s | %d | %d-%d-%d\n", getName(prod), getSupplier(prod), getQuantity(prod),
            d.day, d.month, d.year);
    }
    destroyDynamicVector(expired_products, (void(*)(TElem))destroyProduct);
}


void filterNameUI(UI* ui)
{
    char text[50];
    printf("Enter string: ");
    fgets(text, 50, stdin);
    strip(text);
    toLowerStr(text);

    DynamicVector* filter_name = filterName(ui->service, text);
    int size = getSize(filter_name);

    if (size == 0)
    {
        printf("No products containing that in their name\n");
        destroyDynamicVector(filter_name, (void(*)(TElem))destroyProduct);
        return;
    }
    for (int i = 0; i < size; i++)
    {
        Product* prod = getElem(filter_name, i);
        Date d = getDate(prod);
        printf("%s | %s | %d | %d-%d-%d\n", getName(prod), getSupplier(prod), getQuantity(prod),
            d.day, d.month, d.year);
    }
    destroyDynamicVector(filter_name, (void(*)(TElem))destroyProduct);
}


void shortSupplyUI(UI* ui)
{
    char supplier[50];
    int quantity;

    printf("Enter supplier: ");
    fgets(supplier, 50, stdin);
    strip(supplier);
    toLowerStr(supplier);

    char q[50];
    printf("Limit for quantity: \n");
    fgets(q, 50, stdin);
    if (sscanf(q, "%d", &quantity) != 1)
    {
        printf("Invalid input for quantity!");
        return;
    }

    DynamicVector* result = displayShortSupply(ui->service, supplier, quantity);

    int size = getSize(result);

    if (size == 0)
    {
        printf("No products found.\n");
        destroyDynamicVector(result, (void(*)(TElem))destroyProduct);
        return;
    }

    //mini menu so that the user chooses if to sort ascending or descending 
    if (size > 1)
    {
        printf("\n");
        printf("Sort ascending or descending: \n");
        char answer[50];
        fgets(answer, 50, stdin);
        strip(answer);
        toLowerStr(answer);
        if (strcmp(answer, "ascending") == 0) result = sortAscending(result);
        else if (strcmp(answer, "descending") == 0) result = sortDescending(result);
        else printf("Invalid response!");
    }
    for (int i = 0; i < size; i++)
    {
        Product* prod = getElem(result, i);
        Date d = getDate(prod);

        printf("%s | %s | %d | %d-%d-%d\n", getName(prod), getSupplier(prod), getQuantity(prod), d.day, d.month, d.year);
    }

    destroyDynamicVector(result, (void(*)(TElem))destroyProduct);
}


void showAllProductsUI(UI* ui)
{
    DynamicVector* all_products = getAllProducts(ui->service);
    int size = getSize(all_products);
    if (size == 0) printf("No products available \n");
    for (int i = 0; i < size; i++)
    {
        Product* prod = getElem(all_products, i);
        Date d = getDate(prod);
        printf("%s | %s | %d | %d-%d-%d\n", getName(prod), getSupplier(prod), getQuantity(prod),
            d.day, d.month, d.year);
    }
}


void startUI(UI* ui)
{
    if (ui == NULL) return;
    char cmd[50];
    printMenu();
    while (1)
    {
        printf("\n\n\n");
        printf("\nEnter command: \n");

        fgets(cmd, 50, stdin);
        //remove newline + make everything lowercase
        strip(cmd);
        toLowerStr(cmd);

        if (strcmp(cmd, "add") == 0) addProductUI(ui);
        else if (strcmp(cmd, "delete") == 0) deleteProductUI(ui);
        else if (strcmp(cmd, "update name") == 0) updateNameUI(ui);
        else if (strcmp(cmd, "update supplier") == 0) updateSupplierUI(ui);
        else if (strcmp(cmd, "update quantity") == 0) updateQuantityUI(ui);
        else if (strcmp(cmd, "update date") == 0) updateExpDateUI(ui);
        else if (strcmp(cmd, "expired") == 0) filterExpiredUI(ui);
        else if (strcmp(cmd, "short supply") == 0) shortSupplyUI(ui);
        else if (strcmp(cmd, "all") == 0) showAllProductsUI(ui);
        else if (strcmp(cmd, "filter name") == 0) filterNameUI(ui);
        else if (strcmp(cmd, "undo") == 0)
        {
            if (!undo(ui->service))
                printf("No more to undo\n");
            else
                printf("Undo successful!");
        }
        else if (strcmp(cmd, "redo") == 0)
        {
            if (!redo(ui->service))
                printf("No more to redo\n");
            else
                printf("Redo successful!");
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            printf("Goodbye!");
            break;
        }
        else printf("Invalid command!");
    }


}

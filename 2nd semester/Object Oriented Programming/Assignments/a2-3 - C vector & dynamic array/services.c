#include "services.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


Service* createService(Repo* r)
{
    Service* s = malloc(sizeof(Service));
    if (s == NULL) return NULL;

    s->repository = r;

    s->undo_stack = createDynamicVector(10);
    s->redo_stack = createDynamicVector(10);

    return s;
}


void destroyService(Service* s)
{
    if (s == NULL) return;

    while (getSize(s->undo_stack) > 0)
    {
        DynamicVector* v = getElem(s->undo_stack, getSize(s->undo_stack) - 1);
        destroyDynamicVector(v, (void(*)(TElem))destroyProduct);
        deleteElem(s->undo_stack, getSize(s->undo_stack) - 1, NULL);
    }

    while (getSize(s->redo_stack) > 0)
    {
        DynamicVector* v = getElem(s->redo_stack, getSize(s->redo_stack) - 1);
        destroyDynamicVector(v, (void(*)(TElem))destroyProduct);
        deleteElem(s->redo_stack, getSize(s->redo_stack) - 1, NULL);
    }

    destroyDynamicVector(s->undo_stack, NULL);
    destroyDynamicVector(s->redo_stack, NULL);

    free(s);
}


int addProductService(Service* s, char* name, char* supplier, int quantity, Date expiration_date)
{
    if (s == NULL) return 0;
    //check validity of product to add
    if (checkDate(expiration_date) != 1 || checkQuantity(quantity) != 1 ||
        checkSupplier(supplier) != 1 || checkName(name) != 1) return -1;

    saveState(s);

    //search for product - get its position in the vector  
    int prod_id = findProduct(s->repository, name, supplier, expiration_date);
    if (prod_id != -1)
        //found -> increase quantity 
    {
        Product* prod = getProductRepo(s->repository, prod_id);
        int new_quantity = getQuantity(prod) + quantity;
        setQuantity(prod, new_quantity);
    }

    else
        //not found -> add product to vector 
    {
        Product* prod = createProduct(name, supplier, quantity, expiration_date);
        addProductRepo(s->repository, prod);
    }
    return 1;
}


int deleteProductService(Service* s, char* name, char* supplier, Date expiration_date)
{
    if (s == NULL) return -1;
    //search for product - get its position in the vector  
    int prod_id = findProduct(s->repository, name, supplier, expiration_date);
    if (prod_id == -1) return 0; //not found - doesnt exist 

    saveState(s);

    //else found so delete 
    deleteProductRepo(s->repository, prod_id); //delete from repo and vector 
    return 1; //success 
}


int updateProductNameService(Service* s, char* name, char* supplier, Date expiration_date, char* new_name)
{
    if (s == NULL) return -1;
    //check validity of product name 
    if (checkName(new_name) != 1) return -2;
    //search for product - get its position in the vector  
    int prod_id = findProduct(s->repository, name, supplier, expiration_date);
    if (prod_id == -1) return 0; //not found - doesnt exist 

    saveState(s);

    Product* prod = getProductRepo(s->repository, prod_id); //found - update 
    setName(prod, new_name);
    return 1;
}


int updateProductSupplierService(Service* s, char* name, char* supplier, Date expiration_date, char* new_supplier)
{
    if (s == NULL) return -1;
    //check validity
    if (checkSupplier(new_supplier) != 1) return -2;
    //search for product - get its position in the vector  
    int prod_id = findProduct(s->repository, name, supplier, expiration_date);
    if (prod_id == -1) return 0; //not found - doesnt exist 

    saveState(s);

    Product* prod = getProductRepo(s->repository, prod_id); //found - update 
    setSupplier(prod, new_supplier);
    return 1;
}


int updateProductQuantityService(Service* s, char* name, char* supplier, Date expiration_date, int new_quantity)
{
    if (s == NULL) return -1;
    //check validity 
    if (checkQuantity(new_quantity) != 1) return -2;
    //search for product - get its position in the vector  
    int prod_id = findProduct(s->repository, name, supplier, expiration_date);
    if (prod_id == -1) return 0; //not found - doesnt exist 

    saveState(s);

    Product* prod = getProductRepo(s->repository, prod_id); //found - update 
    setQuantity(prod, new_quantity);
    return 1;
}


int updateProductExpirationService(Service* s, char* name, char* supplier, Date expiration_date, Date new_date)
{
    if (s == NULL) return -1;
    //check validity
    if (checkDate(new_date) != 1) return -2;
    //search for product - get its position in the vector  
    int prod_id = findProduct(s->repository, name, supplier, expiration_date);
    if (prod_id == -1) return 0; //not found - doesnt exist 

    saveState(s);

    Product* prod = getProductRepo(s->repository, prod_id); //found - update 
    setDate(prod, new_date);
    return 1;
}

DynamicVector* getAllProducts(Service* s)
{
    if (s == NULL) return NULL;
    return getAllProductsRepo(s->repository);
}


DynamicVector* filterExpiredProducts(Service* s, char* string, Date today)
{
    if (s == NULL) return NULL;
    DynamicVector* expired_products = createDynamicVector(1); //start a vector with the expired elements 
    DynamicVector* all_products = getAllProductsRepo(s->repository);
    int size = getSize(all_products);
    for (int i = 0; i < size; i++)
    {
        //go trough each element, check if they contain the string (or if the string is empty) and they are expired
        Product* prod = getProductRepo(s->repository, i);
        Date exp_date = getDate(prod);

        if (isExpired(exp_date, today) == 1)
        {
            if (strlen(string) == 0 || strstr(getName(prod), string) != NULL ||
                strstr(getSupplier(prod), string) != NULL)
            {
                Product* copy = createProduct(getName(prod), getSupplier(prod), getQuantity(prod), getDate(prod));

                addElem(expired_products, copy);
            }
        }
    }
    return expired_products;
}


DynamicVector* filterName(Service* s, char* string)
{
    if (s == NULL) return NULL;
    DynamicVector* containing_name = createDynamicVector(1);
    DynamicVector* all_products = getAllProductsRepo(s->repository);
    int size = getSize(all_products);
    for (int i = 0; i < size; i++)
    {
        //go trough each element, check if they contain the string in the name
        Product* prod = getProductRepo(s->repository, i);
        if (strstr(getName(prod), string) != NULL)
        {
            Product* copy = createProduct(getName(prod), getSupplier(prod), getQuantity(prod), getDate(prod));
            addElem(containing_name, copy);
        }
    }
    return containing_name;
}


DynamicVector* displayShortSupply(Service* s, char* supplier, int quantity)
{
    if (s == NULL) return NULL;
    DynamicVector* supplier_short = createDynamicVector(1);
    DynamicVector* all_products = getAllProductsRepo(s->repository);
    int size = getSize(all_products);
    for (int i = 0; i < size; i++)
    {
        Product* prod = getElem(all_products, i);
        if (strcmp(supplier, getSupplier(prod)) == 0 && getQuantity(prod) < quantity)
        {
            Product* copy = createProduct(getName(prod), getSupplier(prod), getQuantity(prod), getDate(prod));
            addElem(supplier_short, copy);
        }
    }

    return supplier_short;
}

DynamicVector* sortAscending(DynamicVector* v)
{
    int size = getSize(v);
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            Product* prodi = getElem(v, i);
            Product* prodj = getElem(v, j);

            if (getQuantity(prodj) < getQuantity(prodi))
            {
                Product* temp = v->elems[i];
                v->elems[i] = v->elems[j];
                v->elems[j] = temp;
            }
        }
    }
    return v;
}

DynamicVector* sortDescending(DynamicVector* v)
{
    int size = getSize(v);
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            Product* prodi = getElem(v, i);
            Product* prodj = getElem(v, j);

            if (getQuantity(prodj) > getQuantity(prodi))
            {
                Product* temp = v->elems[i];
                v->elems[i] = v->elems[j];
                v->elems[j] = temp;
            }
        }
    }
    return v;
}


int isExpired(Date exp_date, Date today)
{
    //check year 
    if (exp_date.year > today.year) return 0;
    if (exp_date.year < today.year) return 1;
    if (exp_date.year == today.year)
    {
        //check month
        if (exp_date.month > today.month) return 0;
        if (exp_date.month < today.month) return 1;
        if (exp_date.month == today.month)
        {
            //check day 
            if (exp_date.day > today.day) return 0;
            if (exp_date.day <= today.day) return 1;
        }
    }
    return 0;
}

DynamicVector* copyVector(DynamicVector* v)
{
    DynamicVector* copy = createDynamicVector(v->capacity);

    for (int i = 0; i < getSize(v); i++)
    {
        Product* p = (Product*)getElem(v, i);

        Product* new_p = createProduct(
            getName(p),
            getSupplier(p),
            getQuantity(p),
            getDate(p)
        );

        addElem(copy, new_p);
    }

    return copy;
}

void saveState(Service* s)
{
    if (s == NULL) return;

    DynamicVector* current = copyVector(getAllProductsRepo(s->repository));

    addElem(s->undo_stack, current);

    //clear redo stack
    while (getSize(s->redo_stack) > 0)
    {
        DynamicVector* v = getElem(s->redo_stack, getSize(s->redo_stack) - 1);
        destroyDynamicVector(v, (void(*)(TElem))destroyProduct);
        deleteElem(s->redo_stack, getSize(s->redo_stack) - 1, NULL);
    }
}

int undo(Service* s)
{
    if (s == NULL) return 0;

    int size = getSize(s->undo_stack);
    if (size == 0) return 0;

    //save current state for redo
    DynamicVector* current = getAllProductsRepo(s->repository);

    addElem(s->redo_stack, current);

    //get previous state 
    DynamicVector* previous = getElem(s->undo_stack, size - 1);

    //remove previous from undo without destroying it
    deleteElem(s->undo_stack, size - 1, NULL);

    //replace repo with the previous state
    setProductsRepo(s->repository, previous);

    return 1; //success
}

int redo(Service* s)
{
    if (s == NULL) return 0;

    int size = getSize(s->redo_stack);
    if (size == 0) return 0;

    // save current state to undo
    DynamicVector* current = getAllProductsRepo(s->repository);

    addElem(s->undo_stack, current);

    //get redo state
    DynamicVector* next = getElem(s->redo_stack, size - 1);

    //remove next from redo without destroying it
    deleteElem(s->redo_stack, size - 1, NULL);

    // restore repo
    setProductsRepo(s->repository, next);

    return 1;
}


/*validate date quantity name and supplier*/
int checkDate(Date date)
{
    if (date.year < 1000 || date.year > 10000) return 0;
    if (date.month < 1 || date.month > 12) return 0;
    if (date.month == 2 && (date.day < 1 || date.day > 29)) return 0; //for february 
    if ((date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) &&
        (date.day < 1 || date.day > 31)) return 0;
    if ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) && (date.day < 1 || date.day > 30)) return 0;
    return 1;
}

int checkQuantity(int quantity)
{
    if (quantity < 0) return 0;
    return 1;
}

int checkName(char* name)
{
    if (strlen(name) == 0) return 0;
    return 1;
}

int checkSupplier(char* supplier)
{
    if (strlen(supplier) == 0) return 0;
    return 1;
}


void addDefaultProducts(Service* s)
{
    if (s == NULL) return;
    Date d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
    d1.year = 2026;
    d1.month = 3;
    d1.day = 12;
    addProductService(s, "eggs", "agroland", 6, d1);
    d2.year = 2026;
    d2.month = 1;
    d2.day = 5;
    addProductService(s, "sugar", "margaritar", 2, d2);
    d3.year = 2030;
    d3.month = 1;
    d3.day = 31;
    addProductService(s, "chocolate", "nestle", 20, d3);
    d4.year = 2028;
    d4.month = 2;
    d4.day = 20;
    addProductService(s, "vanilla", "nestle", 15, d4);
    d5.year = 2027;
    d5.month = 12;
    d5.day = 21;
    addProductService(s, "yeast", "pakmaya", 10, d5);
    d6.year = 2026;
    d6.month = 9;
    d6.day = 13;
    addProductService(s, "salt", "solaris", 4, d6);
    d7.year = 2025;
    d7.month = 2;
    d7.day = 27;
    addProductService(s, "eggs", "naturis", 2, d7);
    d8.year = 2025;
    d8.month = 12;
    d8.day = 19;
    addProductService(s, "milk", "agroland", 1, d8);
    d9.year = 2030;
    d9.month = 10;
    d9.day = 31;
    addProductService(s, "chocolate", "nesquik", 25, d9);
    d10.year = 2027;
    d10.month = 7;
    d10.day = 3;
    addProductService(s, "sprinkles", "nestle", 100, d10);

}

void test_service()
{
    Repo* r = createRepo();
    Service* s = createService(r);

    assert(s != NULL);

    Date d = { 2026, 4, 20 };
    int add_res = addProductService(s, "flour", "boromir", 2, d);
    assert(add_res == 1);

    // add existing => update quantity
    add_res = addProductService(s, "flour", "boromir", 3, d);
    assert(add_res == 1);

    DynamicVector* prods = getAllProducts(s);
    assert(getSize(prods) == 1);
    Product* p = getElem(prods, 0);
    assert(getQuantity(p) == 5);

    // invalid add
    Date d_inv = { 20, 20, 20 };
    assert(addProductService(s, "flour", "boromir", 2, d_inv) == -1);

    // update
    Date d2 = { 2027, 5, 21 };
    assert(updateProductNameService(s, "flour", "boromir", d, "bread") == 1);
    assert(updateProductSupplierService(s, "bread", "boromir", d, "bakery") == 1);
    assert(updateProductQuantityService(s, "bread", "bakery", d, 10) == 1);
    assert(updateProductExpirationService(s, "bread", "bakery", d, d2) == 1);

    prods = getAllProducts(s);
    p = getElem(prods, 0);
    assert(strcmp(getName(p), "bread") == 0);
    assert(strcmp(getSupplier(p), "bakery") == 0);
    assert(getQuantity(p) == 10);
    assert(getDate(p).year == 2027);

    // undo / redo
    undo(s); // undo date update
    prods = getAllProducts(s);
    p = getElem(prods, 0);
    assert(getDate(p).year == 2026);

    redo(s); // redo date update
    prods = getAllProducts(s);
    p = getElem(prods, 0);
    assert(getDate(p).year == 2027);

    // delete product
    assert(deleteProductService(s, "bread", "bakery", d2) == 1);
    assert(getSize(getAllProducts(s)) == 0);

    // filter by name
    addProductService(s, "milk", "farm", 2, d);
    addProductService(s, "chocolate milk", "farm", 5, d);
    addProductService(s, "bread", "bakery", 1, d);
    DynamicVector* filtered = filterName(s, "milk");
    assert(getSize(filtered) == 2);
    destroyDynamicVector(filtered, (void(*)(TElem))destroyProduct);

    // get short supply products
    DynamicVector* short_sup = displayShortSupply(s, "farm", 3);
    assert(getSize(short_sup) == 1); // because only milk checks 2 < 3
    destroyDynamicVector(short_sup, (void(*)(TElem))destroyProduct);

    // sort - check wheter on the first postions the elements are in order
    DynamicVector* all = copyVector(getAllProducts(s));
    sortAscending(all);
    assert(strcmp(getName((Product*)getElem(all, 0)), "bread") == 0); 
    assert(strcmp(getName((Product*)getElem(all, 1)), "milk") == 0); 

    sortDescending(all);
    assert(strcmp(getName((Product*)getElem(all, 0)), "chocolate milk") == 0); 
    destroyDynamicVector(all, (void(*)(TElem))destroyProduct);

    destroyService(s);
    destroyRepo(r);
}
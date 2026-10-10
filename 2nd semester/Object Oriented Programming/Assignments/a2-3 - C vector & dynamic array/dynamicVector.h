#pragma once
#include <stdlib.h>
#include <assert.h>

//elements of type pointers 
typedef void* TElem;

typedef struct {
    int capacity;
    int size;
    TElem* elems;
} DynamicVector;

/*
* function that creates a dynamic vector
* parameter - capacity - the initial desired capacity of the vector - may be changed dynamically
* returns the created vector
*/
DynamicVector* createDynamicVector(int capacity);

/*
* function that destroys the dynamic vector to prevent memory leaks
* parameter - a pointer to a dynamic vector
* parameter - a pointer to destroy element function
*/
void destroyDynamicVector(DynamicVector* v, void (*destroyElem)(TElem));

/*
* function to add an element in the dynamic vector
* parameter - a pointer to a dynamic vector where to add element
* parameter - element to be added - is of type TElem (in my case - Product)
*/
void addElem(DynamicVector* v, TElem elem);

/*
* function to delete a given element
* since all elements are uniquely id'd through name supplier and expiration date, the element given by an index
* parameter - a poinet to a dynamic vector
* parameter - index to the element
* parameter - pointer to destroy element 
*/
void deleteElem(DynamicVector* v, int index, void (*destroyElem)(TElem));

/*
* function to get an element in the vector specified by index
*/
TElem getElem(DynamicVector* v, int index);

/*
* function to get size (number of elements) in a dynamic vector
*/
int getSize(DynamicVector* v);

/*
* function to update (change) a given element in the dynamic vector
* parameter - a pointer to a dynamic vector
* parameter - index to an element to be changed
* parameter - new element that replaces the old one at given index
*/
void updateElem(DynamicVector* v, int index, TElem new_elem, void(*destroyElem)(TElem));

/*
* function to resize the dynamic vector once the max capacity is reached
* doubles the capacity
*/
void resizeVector(DynamicVector* v);

void test_vector();

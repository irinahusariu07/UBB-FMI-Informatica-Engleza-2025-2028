#include "dynamicVector.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


DynamicVector* createDynamicVector(int capacity)
{
	DynamicVector* v = malloc(sizeof(DynamicVector));
	if (v == NULL) return NULL;
	v->capacity = capacity;
	v->size = 0;
	v->elems = malloc(sizeof(TElem) * capacity);
	return v;
}



void destroyDynamicVector(DynamicVector* v, void(*destroyElem)(TElem))
{
	if (v == NULL) return;
	if (destroyElem != NULL)
	{
		for (int i = 0; i < v->size; i++)
			destroyElem(v->elems[i]);
	}
	free(v->elems);
	free(v);
}



void addElem(DynamicVector* v, TElem elem)
{
	//check if the vector exits 
	if (v == NULL) return;
	//check if size is big enough to store the new element - if not resize 
	if (v->size >= v->capacity) resizeVector(v);
	//add the new element and increase size 
	v->elems[v->size] = elem;
	v->size++;
}



void deleteElem(DynamicVector* v, int index, void(*destroyElem)(TElem))
{
	//check if the parameters are ok 
	if (v == NULL || index < 0 || index >= v->size) return;

	if (destroyElem != NULL)
		destroyElem(v->elems[index]);

	for (int i = index; i < v->size - 1; i++)
		v->elems[i] = v->elems[i + 1];

	v->size--;
}


void updateElem(DynamicVector* v, int index, TElem new_elem, void (*destroyElem)(TElem))
{
	// check parameters
	if (v == NULL || index < 0 || index >= v->size) return;

	// destroy the old element if destructor is provided
	if (destroyElem != NULL)
		destroyElem(v->elems[index]);

	// update the element
	v->elems[index] = new_elem;
}


void resizeVector(DynamicVector* v)
{
	v->capacity = v->capacity * 2;
	TElem* new_elems = malloc(sizeof(TElem) * v->capacity);

	for (int i = 0; i < v->size; i++) new_elems[i] = v->elems[i];

	free(v->elems);
	v->elems = new_elems;
}


TElem getElem(DynamicVector* v, int index)
{
	return v->elems[index];
}


int getSize(DynamicVector* v)
{
	return v->size;
}


void test_vector()
{
	DynamicVector* v = createDynamicVector(2);
	assert(v != NULL);
	assert(getSize(v) == 0);
	assert(v->capacity == 2);

	int* a = malloc(sizeof(int)); 
	*a = 1;
	int* b = malloc(sizeof(int)); 
	*b = 2;
	int* c = malloc(sizeof(int)); 
	*c = 3;

	addElem(v, a);
	assert(getSize(v) == 1);
	assert(getElem(v, 0) == a);

	addElem(v, b);
	assert(getSize(v) == 2);

	// should trigger resize
	addElem(v, c);
	assert(getSize(v) == 3);
	assert(v->capacity == 4);

	int* d = malloc(sizeof(int)); 
	*d = 4;
	updateElem(v, 1, d, free);
	assert(getElem(v, 1) == d);

	deleteElem(v, 0, free);
	assert(getSize(v) == 2);
	assert(getElem(v, 0) == d);

	destroyDynamicVector(v, free);
}

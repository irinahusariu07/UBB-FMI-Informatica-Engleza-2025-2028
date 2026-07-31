#pragma once 
#include "Weather.h"


typedef Weather TElem;

class DynamicVector
{
private:
	TElem* elems;
	int size;
	int capacity;
	void resize();

public:
	//default constructor 
	DynamicVector(int initial_capacity = 2);

	//copy constructor
	DynamicVector(const DynamicVector& other);

	//the equal operator  
	DynamicVector& operator=(const DynamicVector& other);

	//add elements 
	void add(TElem element);

	int getSize() const { return this->size; }

	//delete an element 
	void remove(int element_id);

	//get all elements 
	TElem* getAll() const { return this->elems; }

	//get element by id
	TElem& getElem(int index) const { return this->elems[index]; }

	//destroyer
	~DynamicVector();

};


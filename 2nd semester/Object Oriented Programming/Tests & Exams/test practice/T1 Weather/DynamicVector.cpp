#include "DynamicVector.h"

void DynamicVector::resize()
{
	this->capacity *= 2;
	TElem* newBlock = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++) newBlock[i] = this->elems[i];
	delete[] this->elems;
	this->elems = newBlock;
}

DynamicVector::DynamicVector(int initial_capacity)
{
	this->size = 0;
	this->capacity = initial_capacity;
	this->elems = new TElem[this->capacity];
}

DynamicVector::DynamicVector(const DynamicVector& other)
{
	this->capacity = other.capacity;
	this->size = other.size;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++) this->elems[i] = other.elems[i];
}

DynamicVector& DynamicVector::operator=(const DynamicVector& other)
{
	if (this == &other) return *this; //if the pointer to the current obj = the memory dress of the other vector => equal => return value at this address 
	delete[] this->elems; //deallocate the slot allocated previously 
	//create another slot of memory 
	this->elems = new TElem[other.capacity];
	this->capacity = other.capacity;
	this->size = other.size;
	for (int i = 0; i < this->size; i++) this->elems[i] = other.elems[i];
	return *this;
}

void DynamicVector::add(TElem element)
{
	if (this->size == this->capacity) resize();
	this->elems[this->size] = element;
	this->size++;
}

void DynamicVector::remove(int element_id)
{
	if (element_id < 0 || element_id >= getSize()) return;
	for (int i = element_id; i < getSize() - 1; i++)
	{
		this->elems[i] = this->elems[i + 1];
	}
	this->size--;
}

DynamicVector::~DynamicVector()
{
	delete[] this->elems;
}




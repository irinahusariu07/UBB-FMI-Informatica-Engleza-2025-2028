#include "DynamicArray.h"

void DynamicArray::_resize()
{
	this->capacity *= 2;
	TElem* newBlock = new TElem[this->capacity];
	for (int i = 0; i < this->size; ++i) {
		newBlock[i] = this->elems[i];
	}
	delete[] this->elems;
	this->elems = newBlock;
}

DynamicArray::DynamicArray(int intial_cap) : size(0), capacity(intial_cap)
{
	this->elems = new TElem[this->capacity];
}

DynamicArray::DynamicArray(const DynamicArray& other) : capacity(other.capacity), size(other.size)
{
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < this->size; ++i) {
		this->elems[i] = other.elems[i];
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
	if (this == &other) {
		return *this;
	}
	delete[] this->elems;
	this->elems = new TElem[other.capacity];
	this->capacity = other.capacity;
	this->size = other.size;
	for (int i = 0; i < this->size; ++i) {
		this->elems[i] = other.elems[i];
	}
	return *this;
}

void DynamicArray::add(TElem element)
{
	if (this->size == this->capacity) {
		this->_resize();
	}
	this->elems[this->size] = element;
	this->size++;
}

DynamicArray::~DynamicArray()
{
	delete[] this->elems;
}

#pragma once
#include "Dog.h"

//typedef Dog TElem; 
template <typename T>

class DynamicVector
{
private:
	T* elems; 
	int size; 
	int capacity; 
	void resize();

public:
	//default constructor 
	DynamicVector(int initial_capacity = 2);

	//copy constructor
	DynamicVector(const DynamicVector<T>& other); 

	//the equal operator  
	DynamicVector<T>& operator=(const DynamicVector<T>& other); //is with & because it shouldnt return a copy but assign everything to the other vector 

	//add elements 
	void add(T element); 

	int getSize() const { return this->size; }

	//delete an element 
	void remove(int element_id);

	//get all elements 
	//T getAll() { return this->elems; }

	//get element by id
	T& getElem(int index) const { return this->elems[index]; }

	//destroyer
	~DynamicVector();

};

template <typename T>
void DynamicVector<T>::resize()
{
	this->capacity *= 2;
	T* newBlock = new T[this->capacity];
	for (int i = 0; i < this->size; i++) newBlock[i] = this->elems[i];
	delete[] this->elems;
	this->elems = newBlock;
}

template <typename T>
DynamicVector<T>::DynamicVector(int initial_capacity)
{
	this->size = 0;
	this->capacity = initial_capacity;
	this->elems = new T[this->capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& other) //here other is a reference to an object NOT a pointer so I use . not ->
{
	this->capacity = other.capacity;
	this->size = other.size;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++) this->elems[i] = other.elems[i];
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& other)
{
	if (this == &other) return *this; //if the pointer to the current obj = the memory dress of the other vector => equal => return value at this address 
	delete[] this->elems; //deallocate the slot allocated previously 
	//create another slot of memory 
	this->elems = new T[other.capacity];
	this->capacity = other.capacity;
	this->size = other.size;
	for (int i = 0; i < this->size; i++) this->elems[i] = other.elems[i];
	return *this;
}

template <typename T>
void DynamicVector<T>::add(T element)
{
	if (this->size == this->capacity) resize();
	this->elems[this->size] = element;
	this->size++;
}

template <typename T>
void DynamicVector<T>::remove(int element_id)
{
	if (element_id < 0 || element_id >= getSize()) return;
	for (int i = element_id; i < getSize() - 1; i++)
	{
		this->elems[i] = this->elems[i + 1];
	}
	this->size--;
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}




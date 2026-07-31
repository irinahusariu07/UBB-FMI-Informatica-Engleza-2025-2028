#pragma once
#include "Song.h"

typedef Song TElem;

class DynamicArray
{
private:
	TElem* elems;
	int size;
	int capacity;

	void _resize();
public:
	DynamicArray(int intial_cap = 2);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
	void add(TElem element);
	int get_size() const {
		return this->size; }
	~DynamicArray();
};


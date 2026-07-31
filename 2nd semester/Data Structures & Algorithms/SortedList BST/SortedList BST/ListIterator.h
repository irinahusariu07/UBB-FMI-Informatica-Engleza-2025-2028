#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);
	int current_idx; 

	int* stack;
	int stack_capacity;
	int stack_top;
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
	~ListIterator(); 
};



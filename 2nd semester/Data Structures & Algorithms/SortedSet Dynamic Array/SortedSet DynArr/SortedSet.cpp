#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <exception>
using namespace std;

void SortedSet::resize()
{
	this->capacity *= 2; 
	TComp* new_elements = new TComp[this->capacity];
	for (int i = 0; i < this->size; i++) new_elements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = new_elements; 
}
//BC = WC = TC = Theta(size) - for loop 

SortedSet::SortedSet(Relation r) {
	this->relation = r; 
	this->capacity = 1; 
	this->size = 0; 
	this->elements = new TComp[this->capacity];
}
//BC = WC = TC = Theta(1) - initializing class variables 

SortedSet::SortedSet(SortedSet& other)
{
	this->capacity = other.capacity;
	this->size = other.size;
	this->relation = other.relation;
	this->elements = new TComp[this->capacity];
	for (int i = 0; i < this->size; i++) this->elements[i] = other.elements[i];
}
//BC = WC = TC = Theta(size) - for loop 

SortedSet SortedSet::operator=(SortedSet& other)
{
	if (this == &other) return *this;
	delete[] this->elements;
	this->capacity = other.capacity;
	this->size = other.size;
	this->relation = other.relation;

	this->elements = new TComp[this->capacity];
	for (int i = 0; i < this->size; i++) this->elements[i] = other.elements[i];

	return *this;
}
//BC = WC = TC = Theta(size) - for loop 

bool SortedSet::add(TComp elem) {
	//check if resize is needed 
	if (this->size == this->capacity) this->resize();

	//search where to insert elem = first position where relation(current, elem) = False 
	//this means that the current element shouldnt be placed BEFORE the new elem
	//=> we re meant to insert new elem BEFORE current elem
	int i = 0; 
	while (i < this->size && this->relation(this->elements[i], elem) == true)
	{
		if (this->elements[i] == elem) //we check for duplicate of the new elem => cant be added
			return false; 
		i++; 
	}
	//if the loop ended because of the relation = true -> check wheter current element is the same as the one to insert
	if (i < this->size && this->elements[i] == elem) return false;

	//found where to insert => make place => shift elements from the current until end 1 position to the right
	for (int j = this->size; j > i; j--)
		this->elements[j] = this->elements[j - 1];

	//insert the elem on the pos
	this->elements[i] = elem; 
	this->size++;
	return true; //success 
}
//BC : want to re add the first element (on 1st position and already existing) = Theta(1)
//WC : element to add should be on last position or on the first (have to go through every element) = Theta(size)
//TC = O(size)

bool SortedSet::remove(TComp elem) {
	int i = 0;

	//go through all elements or until the relation between current and element doesnt check anymore => passed it
	while (i < this->size && this->relation(this->elements[i], elem)) {
		if (this->elements[i] == elem) //found it -> remembers position
			break;
		i++;
	}

	//if not found <= we reached and or passed without finding
	if (i == this->size || this->elements[i] != elem)
		return false;

	//remove element = shift all elements a position to the left
	for (int j = i; j < this->size - 1; j++) 
		this->elements[j] = this->elements[j + 1];

	this->size--;
	return true;
}
//BC : entering the array i notice that the relation doesnt hold for the 1st elem => wont hold for either of them = Theta(1)
//WC : element to remove doesnt exist or is either on the last or on the first position = Theta(size)
//TC = O(size)


bool SortedSet::search(TComp elem) const {
	int i = 0;

	//i go through the elements until it reaches end and while the relation checks (current is good in front of element)
	while (i < this->size && this->relation(this->elements[i], elem)) {
		//if i find it => success 
		if (this->elements[i] == elem)
			return true;
		i++;
	}

	return false;
}
//BC : element is on the first position = Theta(1)
//WC : element is on the last position or doesnt exist = Theta(size)
//TC = O(size)

int SortedSet::getSize() const {
	return this->size;
}
//BC = WC = TC = Theta(1)


bool SortedSet::isEmpty() const {
	return (this->size == 0);
}
//BC = WC = TC = Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
//BC = WC = TC = Theta(1)

SortedSet::~SortedSet() {
	delete[] this->elements;
}
//BC = WC = TC = Theta(1)


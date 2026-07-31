#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std; 

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0)
	{
		throw exception();
	}
	this->capacity = capacity;
	this->mapSize = 0; 
	this->elements = new TElem[this->capacity]; //dynamic allocation 
}
//BC = WC = TC = Theta(1)

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}
//BC = WC = TC = Theta(1)

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->mapSize == this->capacity)
	{
		throw exception();
	}
	int count = 0; //count occurences of a key - max 2 
	int index = 0;
	while (count < 2 && index < this->mapSize)
	{
		if (this->elements[index].first == c) //first el in a pair is the key
			count++;
		index++;
	}
	if (count == 2) return false; //we cant add another 
	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;
	this->mapSize++;
	return true;
}
//BC : constant - 1st 2 keys are the ones we re looking for = Theta(1)
//WC : Theta(mapSize) - we need to go thru each and every element - appears 1 or 0 times in the map
//TC : O(mapSize)

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE; 
	int nrfound = 0;
	int index = 0; 
	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) 
		{
			if (nrfound == 0)
			{
				result.first = this->elements[index].second;
				nrfound++;
			}

			else
			{
				result.second = this->elements[index].second;
				nrfound++;
			}
		}
		index++;
	}
	return result;
}
//BC : constant - 1st keys are the ones we search for Theta(1)
//WC : Theta(mapSize)
//TC : O(mapSize)

bool FixedCapBiMap::remove(TKey c, TValue v){
	int index = 0;
	while (index < this->mapSize)
	{
		if (this->elements[index].first == c && this->elements[index].second == v) {
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true; 
		}
		index++;
	}
	return false;
}
//BC : Theta(1)
//WC : Theta(mapSize)
//TC : O(mapSize)

int FixedCapBiMap::size() const {
	return this->mapSize;
}
//BC = WC = TC = Theta(1)

bool FixedCapBiMap::isEmpty() const{
	return this->mapSize == 0; 
}
//BC = WC = TC = Theta(1)

bool FixedCapBiMap::isFull() const {
	return this->mapSize == this->capacity;
}
//BC = WC = TC = Theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
//BC = WC = TC = Theta(1) !! ca rezumat la ce am calculat la iterator 
//nu pt ca are o singura linie de cod 




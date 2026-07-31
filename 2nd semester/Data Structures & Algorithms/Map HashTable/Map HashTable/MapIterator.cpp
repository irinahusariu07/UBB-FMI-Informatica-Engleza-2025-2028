#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->first(); //position at first OCCUPIED slot
}


void MapIterator::first() {
	this->current_idx = 0; 
	//until i find OCCUPIED slot or end of capacity
	while (this->current_idx < map.capacity && map.table[this->current_idx].state != Map::OCCUPIED)
		this->current_idx++;

	//BC = Theta(1) : when table[0] is OCCUPIED 
	//WC = Theta(cap) : table is completely empty or all OCCUPIED slots are at the end
	//TC = O(cap)
}


void MapIterator::next() {
	if (!this->valid()) throw std::exception();

	//go to next occupied 
	this->current_idx++; 
	while (this->current_idx < map.capacity && map.table[this->current_idx].state != Map::OCCUPIED)
		this->current_idx++;

	//BC = Theta(1) : when the next element is OCCUPIED 
	//WC = Theta(cap) : first element and the next is separated by DELETED or EMPTY
	//TC = O(cap)
}


TElem MapIterator::getCurrent(){
	if (!this->valid()) throw std::exception();
	return map.table[this->current_idx].pair;

	//BC = WC = TC = Theta(1)
}


bool MapIterator::valid() const {
	return this->current_idx >= 0 && this->current_idx < map.capacity;

	//BC = WC = TC = Theta(1)
}




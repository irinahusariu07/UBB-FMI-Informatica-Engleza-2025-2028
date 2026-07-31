#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	current = map.head; 
}

void SMIterator::first(){
	current = map.head; 
}

void SMIterator::next(){
	if (!valid()) throw std::exception(); 
	current = map.next[current]; //next pos
}

bool SMIterator::valid() const{
	return (current != -1); //not the end of the list 
}

TElem SMIterator::getCurrent() const{
	if (!valid()) throw std::exception(); 
	return map.elems[current]; //current element
}



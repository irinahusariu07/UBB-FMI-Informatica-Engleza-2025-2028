#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->current = 0;
}
//BC = WC = TC = Theta(1)

void SortedSetIterator::first() {
	this->current = 0;
}
//BC = WC = TC = Theta(1)

void SortedSetIterator::next() {
	if (this->valid() == false) throw exception();
	this->current++;
}
//BC = WC = TC = Theta(1)

TElem SortedSetIterator::getCurrent()
{
	if (this->valid() == false) throw exception();
	return this->multime.elements[this->current];
}
//BC = WC = TC = Theta(1)

bool SortedSetIterator::valid() const {
	//valid if in the range of the multime
	return this->current < this->multime.size;
}
//BC = WC = TC = Theta(1)

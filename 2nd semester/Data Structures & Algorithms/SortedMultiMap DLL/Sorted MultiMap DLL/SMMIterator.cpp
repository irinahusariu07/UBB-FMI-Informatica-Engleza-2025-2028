#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->first(); 
}

void SMMIterator::first(){
	this->currentKey = map.head; 
	//if the key list is not empty <= head is not null  -> go to the first value 
	if (this->currentKey != nullptr) this->currentValue = this->currentKey->valHead;
	else this->currentKey = nullptr; //map empty 
}
//BC = WC = TC = Theta(1)

void SMMIterator::next(){
	if (!valid()) throw exception(); 
	this->currentValue = this->currentValue->next; //next value in the value list 

	//if all values for current key were finished => on to the next key 
	if (this->currentValue == nullptr)
	{
		this->currentKey = this->currentKey->next; 
		if (this->currentKey != nullptr) this->currentValue = this->currentKey->valHead; //the first value in the list 
	}
}
//BC = WC = TC = Theta(1)

bool SMMIterator::valid() const{
	return (this->currentKey != nullptr  && this->currentValue != nullptr);
}
//BC = WC = TC = Theta(1)

TElem SMMIterator::getCurrent() const{
	if (!valid()) throw exception(); 
	return pair<TKey, TValue>(this->currentKey->key, this->currentValue->info); 
}
//BC = WC = TC = Theta(1)



#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

void SortedMap::resize()
{
	int new_capacity = capacity * 2; 
	TElem* new_elems = new TElem[new_capacity];
	int* new_next = new int[new_capacity];

	//copy old elems into the new array 
	for (int i = 0; i < capacity; i++)
	{
		new_elems[i] = elems[i]; 
		new_next[i] = next[i]; 
	}

	//link the empty slots
	for (int i = capacity; i < new_capacity - 1; i++) new_next[i] = i + 1; 

	new_next[new_capacity - 1] = -1; //mark the end
	//the old firstEmpty = -1 now it shuld be the beginning of the empty slots
	//if (firstEmpty == -1) 
	firstEmpty = capacity; //the empty slots start after the array of len capacity 
	/*else
	{
		int current = firstEmpty; 
		while (next[current] != -1) current = next[current]; 
		next[current] = capacity; 
	}*/

	delete[] elems;
	delete[] next; 
	elems = new_elems; 
	next = new_next; 
	capacity = new_capacity; 
}

SortedMap::SortedMap(Relation r) {
	this->capacity = 1; 
	this->map_size = 0; 
	this->rel = r; 
	this->head = -1; //empty list

	this->elems = new TElem[this->capacity];
	this->next = new int[this->capacity]; 

	//point each position to the next available idx
	for (int i = 0; i < capacity - 1; i++) next[i] = i + 1; 
	next[capacity - 1] = -1; //end of the list for last pos 
	this->firstEmpty = 0; //first pos is also the first available in an empty array
}
//BC = WC = TC = Theta(n) : go through the entire next arrayto link 


TValue SortedMap::add(TKey k, TValue v) {
	int current = head;
	int prev = -1;

	//go through array until last position or while the relation holds
	while (current != -1 && rel(elems[current].first, k))
	{
		if (elems[current].first == k) //key found => replace value 
		{
			TValue old_value = elems[current].second;
			elems[current].second = v;
			return old_value; //return the old value 
		}
		prev = current; //used to link the inserted pair to the one before it 
		current = next[current]; //on to the next one 
	}

	//key doesnt exist => insert the whole pair on the 1st available spot 
	if (firstEmpty == -1) resize(); //if the next available pos doesnt exist amymore => expand 
	int new_pos = firstEmpty;
	firstEmpty = next[new_pos];
	elems[new_pos] = std::make_pair(k, v);

	if (prev == -1) //the new head
	{
		//insert at beginning (in front of old head)
		next[new_pos] = head;
		head = new_pos;
	}
	else
	{
		next[new_pos] = current;
		next[prev] = new_pos;
	}
	map_size++; 
	return NULL_TVALUE; //return null when added a new k-v pair 
}
//BC = Theta(1) : inserting (k,v) on the 1st position (new head OR list empty) 
//				  and there is at least one empty space (firstEmpty!=-1)
//WC = Theta(n) : map is full => resize 
//				  or key is at the very end 
//TC = O(n)


TValue SortedMap::search(TKey k) const {
	int current = head; 
	//go through the array of elements startng at head 
	while (current != -1)
	{
		if (elems[current].first == k) return elems[current].second; //found => return value
		
		//if the relation doesnt hold anymore 
		if (!rel(elems[current].first, k)) break; 

		current = next[current];
	}
	
	return NULL_TVALUE; //not found
}
//BC = Theta(1) : key is the first element (or all keys should be after k => no traversal)
//WC = Theta(n) : key is the last element or doesnt exist 
//TC = O(n) 

TValue SortedMap::remove(TKey k) {
	int current = head; 
	int prev = -1;
	//traverse until end or unti the key is found 
	while (current != -1 && elems[current].first != k)
	{
		prev = current; 
		current = next[current]; 
	}
	//if exited because current = -1 => key not found
	if (current == -1) return NULL_TVALUE; 

	TValue remove_value = elems[current].second; //the value of the key to remove (needs to be returned if removed)
	
	//removing the head = the following element becomes the head
	if (current == head) head = next[head];
	//else link the element before the deleted to one after the deleted (exclude deleted)
	else next[prev] = next[current]; 

	next[current] = firstEmpty; //the deleted element frees a slot => this is the first empty
	firstEmpty = current; 

	map_size--; 
	return remove_value; 
}
//BC = Theta(1) : key to remove is the head 
//WC = Theta(n) : key is the last or doesnt exist
//TC = O(n)

int SortedMap::size() const {
	return map_size;
}
//BC = WC = TC = Theta(1)

bool SortedMap::isEmpty() const {
	return (map_size == 0);
}
//BC = WC = TC = Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//BC = WC = TC = Theta(1)

SortedMap::~SortedMap() {
	delete[] this->elems; 
	delete[] this->next; 
}
//BC = WC = TC = Theta(1)
#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::KeyNode* SortedMultiMap::findKeyNode(TKey c) const
{
	KeyNode* current = this->head; 
	while (current != nullptr && rel(current->key, c))
	{
		if (current->key == c) return current; //if the key exists return a pointer to it 
		current = current->next; 
	}
	return current; //here only if the relation didnt hold -> c should be in front of this key 
}

SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r; 
	this->head = nullptr; 
	this->totalSize = 0; 
}
//BC = WC = TC = Theta(1) 

/*
SortedMultiMap::SortedMultiMap(SortedMultiMap& other)
{
	this->rel = other.rel; 
	this->head = nullptr; 
	this->totalSize = other.totalSize; 

	KeyNode* other_key = other.head; 
	KeyNode* last_key_added = nullptr; 

	while (other_key != nullptr)
	{
		//create a new KeyNode to be added to the dll (by copying from other)
		KeyNode* new_key = new KeyNode; 
		new_key->key = other_key->key;  //the info of the key node is the same as from the key node from other
		new_key->next = nullptr; //next we dont know yet 
		new_key->prev = last_key_added; //previous = pointer to the last key added 
		//head and tail of the value list 
		new_key->valHead = nullptr; 
		new_key->valTail = nullptr; 

		//if this would be the first key node added - it is the head 
		if (this->head == nullptr) this->head = new_key;
		//else link the last key next to the current one 
		else last_key_added->next = new_key;


		//add the value dll for the current new key 
		ValueNode* other_value = other_key->valHead;
		ValueNode* last_value_added = nullptr;

		while (other_value != nullptr) 
		{
			ValueNode* new_value = new ValueNode;
			new_value->info = other_value->info; //the info of the value node copyed from the other 
			new_value->next = nullptr; //next dont know yet 
			new_value->prev = last_value_added; //prev = pointer to the last value 

			//if this would be the first value in the list (the head is still null)
			if (new_key->valHead == nullptr) new_key->valHead = new_value;
			//else link the last value next to the current one 
			else last_value_added->next = new_value;
			new_key->valTail = new_value; // also make it the tail 
			other_value = other_value->next; //move to the next 
		}
		last_key_added = new_key;
		other_key = other_key->next; //move to the next key to copy 
	}
}
//BC = WC = TC = Theta(number of unique keys + total number of k-v pairs) //need to copy everything 

SortedMultiMap& SortedMultiMap::operator=(const SortedMultiMap& other)
{
	// check if they are the same 
	if (this == &other) return *this;

	//cleanup existing memory 
	KeyNode* current_key = this->head;
	while (current_key != nullptr)
	{
		//delete the list of values for this key 
		ValueNode* current_value = current_key->valHead;
		while (current_value != nullptr)
		{
			ValueNode* tmpV = current_value;
			current_value = current_value->next; //pass on to the next value (move forward)
			delete tmpV; //delete 
		}

		//remove the key 
		KeyNode* tmpK = current_key;
		current_key = current_key->next;
		delete tmpK;
	}

	//copy data from other (equal)
	this->rel = other.rel;
	this->head = nullptr;
	this->totalSize = other.totalSize;

	KeyNode* other_key = other.head;
	KeyNode* last_key_added = nullptr;

	while (other_key != nullptr)
	{
		//create a new KeyNode to be added to the dll (by copying from other)
		KeyNode* new_key = new KeyNode;
		new_key->key = other_key->key;  //the info of the key node is the same as from the key node from other
		new_key->next = nullptr; //next we dont know yet 
		new_key->prev = last_key_added; //previous = pointer to the last key added 
		//head and tail of the value list 
		new_key->valHead = nullptr;
		new_key->valTail = nullptr;

		//if this would be the first key node added - it is the head 
		if (this->head == nullptr) this->head = new_key;
		//else link the last key next to the current one 
		else last_key_added->next = new_key;


		//add the value dll for the current new key 
		ValueNode* other_value = other_key->valHead;
		ValueNode* last_value_added = nullptr;

		while (other_value != nullptr)
		{
			ValueNode* new_value = new ValueNode;
			new_value->info = other_value->info; //the info of the value node copyed from the other 
			new_value->next = nullptr; //next dont know yet 
			new_value->prev = last_value_added; //prev = pointer to the last value 

			//if this would be the first value in the list (the head is still null)
			if (new_key->valHead == nullptr) new_key->valHead = new_value;
			//else link the last value next to the current one 
			else last_value_added->next = new_value;
			new_key->valTail = new_value; // also make it the tail 
			other_value = other_value->next; //move to the next 
		}
		last_key_added = new_key;
		other_key = other_key->next; //move to the next key to copy 
	}
	return *this; 
}
//BC = Theta(1) : map1 = map1 (self assignment)
//WC = Theta(number of unique keys + total number of k-v pairs) : copy everything 
//TC = O(number of unique keys + total number of k-v pairs)
*/

void SortedMultiMap::add(TKey c, TValue v) {
	KeyNode* target = findKeyNode(c);

	//case 1 - key already exists 
	if (target != nullptr && target->key == c)
	{
		ValueNode* new_value = new ValueNode;
		new_value->info = v;
		new_value->next = nullptr;
		new_value->prev = target->valTail; //link to the current tail of the list 

		//if it is the 1st value in the list add on 1st else add at end
		if (target->valHead == nullptr) target->valHead = new_value;
		else target->valTail->next = new_value;
		target->valTail = new_value; //mark it as the new tail 
	}
	
	//case 2 - key doesnt exist => needs to be inserted in front of the node returned by find 
	else 
	{
		ValueNode* new_value = new ValueNode; 
		new_value->info = v;
		new_value->next = nullptr;
		new_value->prev = nullptr;
		
		KeyNode* new_node = new KeyNode; 
		new_node->key = c; 
		new_node->valHead = new_value;
		new_node->valTail = new_value; 
		new_node->next = target; //link it to the node that should be after it by findKeyNode()
		new_node->prev = nullptr; 

		//determine the prev = position where to insert
		KeyNode* prev_node = nullptr; 
		if (target != nullptr) prev_node = target->prev;
		else //passed the end of the list => need to be inserted on last position
		{
			//find the last node by going through the dll
			KeyNode* last = this->head; 
			if (last != nullptr)
			{
				while (last->next != nullptr) last = last->next;
			}
			prev_node = last;
		}

		//insert new node between prev and current 
		new_node->prev = prev_node;
		new_node->next = target;
		

		if (prev_node == nullptr) //this key should be the new head 
		{
			if (this->head != nullptr) this->head->prev = new_node; 
			this->head = new_node; 
		}
		else prev_node->next = new_node; 
		if (target != nullptr) target->prev = new_node; 
		
	}
	this->totalSize++; 
}
//BC = Theta(1) : key is the first one in the list (or list is empty) and we just add a value 
//WC = Theta(number of keys) : key is at the end or doesnt exist (insert at the end) 
//TC = O(number of keys)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector <TValue> values; 
	KeyNode* target = findKeyNode(c);

	if (target != nullptr && target->key == c)
	{
		ValueNode* currentV = target->valHead; //start taking values from the list 
		while (currentV != nullptr)
		{
			values.push_back(currentV->info);
			currentV = currentV->next;
		}
		return values;
	}
	return values; 
}

bool SortedMultiMap::remove(TKey c, TValue v)
{
	KeyNode* target = findKeyNode(c);
	if (target == nullptr || target->key != c) return false; //key not found


	//found the key - need to search for the value
	ValueNode* currentV = target->valHead; //start the list
	while (currentV != nullptr)
	{
		if (currentV->info == v) //found the value 
		{
			//check if the given value is the head of list 
			if (currentV->prev != nullptr) currentV->prev->next = currentV->next; //make the link skipping the current value(delete)
			else target->valHead = currentV->next;

			//check if the given value is the tail of the list 
			if (currentV->next != nullptr) currentV->next->prev = currentV->prev;
			else target->valTail = currentV->prev;

			delete currentV;
			this->totalSize--;

			//if there was the only one value and now the list is empty we need to delete it (also the key from the key list)
			if (target->valHead == nullptr)
			{
				if (target->prev != nullptr) target->prev->next = target->next;
				else this->head = target->next; //it was the head of key list 

				if (target->next != nullptr) target->next->prev = target->prev;
				delete target;
			}
			return true; //k-v pair removed
		}
		currentV = currentV->next;
	}
	return false; //went trough all values for this key and didnt find it 
}
//BC = Theta(1) : the key is the first in the list and the value is also the first in the value list 
//WC = Theta(number of unique keys + max(number of values for each key)) : the key is last and the value is at the end of the longest value list 
//TC = O(number of unique keys + max(number of values for each key)


int SortedMultiMap::size() const {
	return this->totalSize;
}
//BC = WC = TC = Theta(1)

bool SortedMultiMap::isEmpty() const {
	return (this->totalSize == 0);
}
//BC = WC = TC = Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//BC = WC = TC = Theta(1)

SortedMultiMap::~SortedMultiMap() 
{
	KeyNode* current_key = this->head;
	while (current_key != nullptr)
	{
		//delete the list of values for this key 
		ValueNode* current_value = current_key->valHead;
		while (current_value != nullptr)
		{
			ValueNode* tmpV = current_value;
			current_value = current_value->next; //pass on to the next value (move forward)
			delete tmpV; //delete 
		}

		//remove the key 
		KeyNode* tmpK = current_key;
		current_key = current_key->next;
		delete tmpK;
	}
}
//BC = WC = TC = Theta(number of unique keys + total number of k-v pairs) : everythig must be visited and deleted 
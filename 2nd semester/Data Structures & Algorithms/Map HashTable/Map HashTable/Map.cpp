#include "Map.h"
#include "MapIterator.h"

void Map::resize()
{
	int old_cap = this->capacity;
	HashNode* old_table = this->table; 

	this->capacity = old_cap * 2; 
	this->table = new HashNode[this->capacity];
	
	//every slot marked as empty
	for (int i = 0; i < this->capacity; i++) this->table[i].state = EMPTY;
	
	//rehash
	for (int i = 0; i < old_cap; i++)
	{
		if (old_table[i].state == OCCUPIED)
		{
			//rehashing process
			TKey k = old_table[i].pair.first;
			int base_hash = hashFunction(k);
			int step = 0;
			int current_idx = base_hash;

			while (this->table[current_idx].state != EMPTY) //if the slot where the pair should be placed is occupied
			{
				//quadratic probing
				step++;
				current_idx = (base_hash + (step*(step+1))/2) % this->capacity;
				if (current_idx < 0) current_idx += this->capacity;
			}

			//add it to the new table after hashing 
			this->table[current_idx].pair = old_table[i].pair;
			this->table[current_idx].state = OCCUPIED;
		}
	}

	delete[] old_table;


	//BC = WC = TC = Theta(new cap) : loop thru old table to rehash 

}

Map::Map() {
	this->capacity = 7; 
	this->map_size = 0; 
	this->max_load_factor = 0.7f; //threshold value when to resize
	this->table = new HashNode[this->capacity];

	//mark every slot in the table as empty at start 
	for (int i = 0; i < this->capacity; i++) this->table[i].state = EMPTY;
	
	
	//BC = WC = TC = Theta(cap)
}

Map::~Map() {
	delete[] this->table;

	//BC = WC = TC = Theta(1)
}

TValue Map::add(TKey c, TValue v){
	int base_hash = hashFunction(c); //the first hashing of the key
	int i = 0; //to count the number of trials for finding a slot -> used in quadratic probing
	int current_idx = base_hash;

	/*
	* when searching for a value DELETED slots are useful
	* so if i didnt find the key i want to add 
	* and i want to add it fresh in the table i can add it on a DELETED slot
	* => i need to remember the first DELETED i encountered 
	*/
	int first_deleted_idx = -1; 

	//loop until i find the key => update or find an empty slot => i can add it there
	while (table[current_idx].state != EMPTY)
	{
		if (table[current_idx].state == OCCUPIED)
		{
			if (table[current_idx].pair.first == c) //if the key already exists
			{
				//update value
				TValue old_val = table[current_idx].pair.second; //to return old value
				table[current_idx].pair.second = v; //update it
				return old_val;
			}
		}
		else if (table[current_idx].state == DELETED) //if there was a value there
		{
			if (first_deleted_idx == -1) first_deleted_idx = current_idx; 
			//remember the first deleted slot 
		}

		//if it reaches here it means the key wasnt the desired one => increment the attempt counter
		i++; 
		current_idx = (base_hash + (i * (i + 1)) / 2) % capacity; //quadratic probing
		if (current_idx < 0) current_idx += capacity; //if < 0 from hashing need to be made positive 
		//if i have mor attempts than capacity it means the table doesnt have any empty slots 
		if (i >= this->capacity) break; 
	}
	//if the loop stops => the key doesnt exist -> prepare to add
	int insertion_idx; 
	//insert on the first DELETED slot if it exists, if not, at the end
	if (first_deleted_idx != -1) insertion_idx = first_deleted_idx;
	else insertion_idx = current_idx;

	//insert in the table the k-v pair
	table[insertion_idx].pair = std::make_pair(c, v);
	table[insertion_idx].state = OCCUPIED; //mark as occupied
	this->map_size++;

	//if the current load factor = map_size / capacity exceeds the threshold 
	float load_factor = (float)map_size / capacity;
	if (load_factor > max_load_factor) resize(); 

	return NULL_TVALUE;


	//BC = Theta(1) : when keys base hash slot is EMPTY or OCCUPIED by the same key => just replace value
	//WC = Theta(cap) : key doesnt exist and the quadratic formula checks map_size slots before breaking
	//						 OR resize() triggered and everything has to be rehashed
	//TC = O(cap)
}

TValue Map::search(TKey c) const{
	/*
	* if the key isnt on the hashed spot or further down the line
	* computed with quadratic probing <=> if we reach an empty spot while searching 
	* this means that its not in the table and return null 
	* 
	* if i encounter a OCCUPIED or DELETED slot while searching i know i can continue the search
	* because the key may be further down the line
	*/

	int base_hash = hashFunction(c);
	int i = 0; 
	int current_idx = base_hash; 

	//loop until i hit an EMPTY slot 
	while (table[current_idx].state != EMPTY)
	{
		if (table[current_idx].state == OCCUPIED)
		{
			if (table[current_idx].pair.first == c)
				//key found => return value
				return table[current_idx].pair.second;
		}
		i++; //attempts 
		current_idx = (base_hash + (i*(i+1))/2) % capacity; 
		if (current_idx < 0) current_idx += capacity; //if < 0 need to be made positive
		//if i checked as many times as to exceed capacity -> key isnt here 
		if (i >= capacity) break; 
	}
	return NULL_TVALUE;


	//BC = Theta(1) : key found on its base hash slot 
	//WC = Theta(cap) : key not in the map and many DELETED before EMPTY slot
	//TC = O(cap)
}

TValue Map::remove(TKey c){

	int base_hash = hashFunction(c); 
	int i = 0; 
	int current_idx = base_hash; 

	//loop until i find a EMPTY slot (= key not in the table)
	while (table[current_idx].state != EMPTY)
	{
		if (table[current_idx].state == OCCUPIED)
		{
			if (table[current_idx].pair.first == c)
			{
				//key found
				TValue remove_val = table[current_idx].pair.second;

				//mark as DELETED 
				table[current_idx].state = DELETED;
				this->map_size--;

				return remove_val;
			}
		}
		//quadratic probing
		i++;
		current_idx = (base_hash + (i * (i + 1)) / 2) % capacity;
		if (current_idx < 0) current_idx += capacity; //if < 0 from hashing need to be made positive
		//if i checked as many times as capacity
		if (i >= capacity) break;
	}

	return NULL_TVALUE;


	//BC = Theta(1) : key locted on its base hash slot 
	//WC = Theta(cap) : key not in the map and many DELETED before EMPTY slot
	//TC = O(cap)
}


int Map::size() const {
	return this->map_size; 

	//BC = WC = TC = Theta(1)
}

bool Map::isEmpty() const{
	return this->map_size == 0; //true if it is empty 

	//BC = WC = TC = Theta(1)
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}




#pragma once
#include <utility>
#include<string>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)
class MapIterator;



class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	/*
		i need to keep the states of a slot
		empty = nothing was ever there, free
		occupied = something is there
		deleted = something has been there and was deleted
				so if any collisions happened and another elem was placed based on that position
				using quadratic probing and it encounters such a spot i should remember that i can find it based on the previously occupied spot
	*/
	enum SlotState { EMPTY, OCCUPIED, DELETED };

	struct HashNode
	{
		TElem pair;
		SlotState state;
	};

	private:
		HashNode* table; //dynamic array -> the hash table 
		int capacity; 
		int map_size; 
		float max_load_factor; //treshold factor 
		int hashFunction(TKey k) const { return std::abs(k) % this->capacity; } //the hash function to associate a key with a base idx
		void resize();

	public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

};




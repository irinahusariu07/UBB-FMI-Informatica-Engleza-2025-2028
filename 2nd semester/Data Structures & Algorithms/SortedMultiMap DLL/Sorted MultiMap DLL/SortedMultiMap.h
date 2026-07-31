#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;

    //struct for the DLL of values for each key 
    struct ValueNode
    {
        TValue info; 
        ValueNode* prev; //pointer to previous node (of type value)
        ValueNode* next; //pointer to next node (of type value) 
    };

    //struct for the DLL of all existing keys 
    struct KeyNode
    {
        TKey key; 
        ValueNode* valHead; //the head of the value list for this key 
        ValueNode* valTail; //the tail of the value list for this key (easier access)
        KeyNode* prev; //pointer to the previous node (of type key)
        KeyNode* next; //pointer to the next node (of type key)
    };

    private:
        KeyNode* head; 
        Relation rel; 
        int totalSize; 
        //helper function - returns the KeyNode* that contains c or the node that should follow c 
        KeyNode* findKeyNode(TKey c) const;

    public:

    // constructor
    SortedMultiMap(Relation r);

    /*
    //copy constructor (for a new object that i create from an existing one) 
    SortedMultiMap(SortedMultiMap& other);

    //equal operator (for 2 already existing objects)
    SortedMultiMap& operator=(const SortedMultiMap& other);
    */
    
	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};

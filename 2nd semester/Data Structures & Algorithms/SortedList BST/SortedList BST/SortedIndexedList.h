#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedIndexedList {

	struct BSTNode {
		TComp info;
		int left; //idx of left child 
		int right; //idx of right child 
		int left_count; //number of nodes in the left subtree 
	};

private:
	friend class ListIterator;
private:
	BSTNode* table; //dynamic array with the nodes of the tree
	int capacity; 
	int tree_size;
	int root; //idx of the root 
	int first_empty; //idx of first empty slot 
	Relation relation;
	void resize();

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// befor inserting element -> caim empty spot or trigger resize if no more empty spots
	int allocateNode(TComp e);
	// adds an element in the sortedList (to the corresponding position)
	void add(TComp e);

	//recursive removal of nodes 
	int removeRecursive(int current, int pos, bool& removed, TComp& removed_val);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

};

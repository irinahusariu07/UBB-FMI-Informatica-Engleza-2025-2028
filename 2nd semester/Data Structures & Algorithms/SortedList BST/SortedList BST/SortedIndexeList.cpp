#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

void SortedIndexedList::resize() {
	int old_capacity = this->capacity;
	this->capacity *= 2;
	BSTNode* new_table = new BSTNode[this->capacity];

	//copy existing nodes 
	for (int i = 0; i < old_capacity; i++) {
		new_table[i] = this->table[i];
	}

	//link all new empty slots 
	for (int i = old_capacity; i < this->capacity - 1; i++) {
		new_table[i].left = i + 1; //connect to the next empty slot 
		new_table[i].right = -1;
		new_table[i].left_count = 0;
	}
	new_table[this->capacity - 1].left = -1; //last empty slot 
	new_table[this->capacity - 1].right = -1;
	new_table[this->capacity - 1].left_count = 0;

	delete[] this->table;
	this->table = new_table;

	//empty positions start at last capacity position 
	this->first_empty = old_capacity;

	///BC = WC = TC = Theta(n)
}

SortedIndexedList::SortedIndexedList(Relation r) {
	this->capacity = 7; //initial capacity 
	this->tree_size = 0;
	this->root = -1; //no root yet = empty tree 
	this->first_empty = 0; //the first empty slot is the first one in the empty array 

	this->table = new BSTNode[this->capacity]; //a new array of init capacity
	//populate 
	for (int i = 0; i < this->capacity - 1; i++)
	{
		this->table[i].left = i + 1; //link the empry nodes <=> the next empty is the next node
		this->table[i].right = -1; //initially 
		this->table[i].left_count = 0; 
	}
	//last slot point to -1 because there arent any following empty slots
	this->table[this->capacity-1].left = -1;
	this->table[this->capacity - 1].right = -1;
	this->table[this->capacity - 1].left_count = 0; 
	this->relation = r; 
}

int SortedIndexedList::size() const {
	return this->tree_size;
	//BC = WC = TC = Theta(1)
}

bool SortedIndexedList::isEmpty() const {
	return this->tree_size == 0;
	//BC = WC = TC = Theta(1)
}

TComp SortedIndexedList::getElement(int pos) const{
	//if pos = left_count => there are left_count elements that should be before me => im the correct element for pos
	//if pos < left_count => search in the left subtree
	//if pos > left_count => search in the right subtree 
	if (pos < 0 || pos >= this->tree_size) throw std::exception(); //outside bounds
	int current = this->root; 
	while (current != -1) //there still are nodes 
	{
		int size_left_subtree = this->table[current].left_count;
		if (pos == size_left_subtree) //this is the desired node 
			return this->table[current].info; //return its info 

		else if (pos < size_left_subtree) //search in left subtree
			current = this->table[current].left; //take the left child and start the search

		else if (pos > size_left_subtree) { //search in right subtree
			//skipping over the left subtree and root to get to right subtree 
			//new position = position - (size of left + 1)
			pos = pos - (size_left_subtree + 1);
			current = this->table[current].right; //take the right child and start search 
		}
	}
	throw std::exception(); 

	//BC = Theta(1) : target is the root 
	//WC = Theta(n) : degenerate (linear) tree & get value of last leaf 
	//TC = O(n) 
}


int SortedIndexedList::search(TComp e) const {
	int current = this->root; 
	int skipped_elements = 0; //for pos computation 
	int first_found_pos = -1; //for duplicates 
	while (current != -1)
	{
		if (this->table[current].info == e)
		{
			first_found_pos = skipped_elements + this->table[current].left_count;
			current = this->table[current].left;
		}
		else if (this->relation(e, this->table[current].info)) //if e should be before current => go left
			current = this->table[current].left; 
		else //relation doesnt hold => go right 
		{
			skipped_elements += 1 + this->table[current].left_count; //skipping over all left subtree + root
			current = this->table[current].right; 
		}
	}
	return first_found_pos;
	//BC = Theta(1) : the searched node is a direct child of root OR tree is empty
	//WC = Theta(n) : degenerate tree and searched is at the last leaf or missing
	//TC = O(n) 
}

int SortedIndexedList::allocateNode(TComp e)
{
	if (this->first_empty == -1) this->resize(); //no more empty slots => resize
	//find the first empty (where to add) and then update first empty
	int allocated_idx = this->first_empty;
	this->first_empty = this->table[allocated_idx].left; //next empty slots becomes first 

	//init the new node 
	this->table[allocated_idx].info = e; 
	this->table[allocated_idx].left = -1; 
	this->table[allocated_idx].right = -1;
	this->table[allocated_idx].left_count = 0;

	return allocated_idx; //return the pos where i put the new node 

	//BC = Theta(1) : there is still space in current array and i find it easily with first_empty
	//WC = Theta(n) : resize is triggered
	//TC = O(n)
}

void SortedIndexedList::add(TComp e) {
	//case1 empty tree -> new node = root 
	if (this->root == -1) {
		int new_node = this->allocateNode(e); //grab empty spot (or resize)
		this->root = new_node;
		this->tree_size++;
		return;
	}

	//case2. find the exact spot where new node should be placed  
	int current = this->root;
	int parent = -1;
	//starting at root go until end 
	while (current != -1) {
		parent = current;
		if (this->relation(e, this->table[current].info)) {
			//relation hold => search in the left subtree
			this->table[current].left_count++; 
			//a new element will be added to the current nodes left subtree => increment left count
			current = this->table[current].left; //go to the left 
		}
		else current = this->table[current].right; //if relation doesnt hold => go right 
	}

	//exited while loop => found spot for it 
	int new_node = this->allocateNode(e); //grab empty spot

	//link to its parent - use relation to know if it becomes the left or right child
	if (this->relation(e, this->table[parent].info)) this->table[parent].left = new_node;
	else this->table[parent].right = new_node;

	this->tree_size++; //increase size

	//BC = Theta(1) : tree is empty 
	//WC = Theta(n) : tree is degenerate and destined spot is at the bottom
	//				OR array is full => resize is triggered
	//TC = O(n) 
}

TComp SortedIndexedList::remove(int pos) {
	if (pos < 0 || pos >= this->tree_size) {
		throw std::exception();
	}

	bool removed = false;
	TComp removed_val = NULL_TCOMP;

	this->root = removeRecursive(this->root, pos, removed, removed_val);

	if (removed) this->tree_size--;
	return removed_val;

	//BC = Theta(1) : target is root and has 0 or 1 child 
	//WC = Theta(n) : tree is degenerate and delete the last leaf 
	//				OR delete a node that has 2 children and right subtree is a degenerated subtree => move through all to reach last value 
	//TC = O(n)
}



int SortedIndexedList::removeRecursive(int current, int pos, bool& removed, TComp& removed_val) {
	if (current == -1) return -1; //dead end 

	int size_left_subtree = this->table[current].left_count;

	//reached desired position 
	if (pos == size_left_subtree) 
	{
		removed = true; //mark as removed 
		removed_val = this->table[current].info; //keep its value 

		// 0 or 1 child 
		//only has right child or is a leaf 
		if (this->table[current].left == -1) 
		{
			int right_child = this->table[current].right;
			//new first_empty gets this position 
			this->table[current].left = this->first_empty; //link to previous first empty
			this->first_empty = current;
			return right_child; //return the node that needs to be moved into deleted spot
		}

		//left child
		if (this->table[current].right == -1) {
			int left_child = this->table[current].left;
			//new empty gets this position
			this->table[current].left = this->first_empty;
			this->first_empty = current;
			return left_child;
		}

		//2 children
		int successor_parent = current; 
		int successor = this->table[current].right; //direct right node 

		//in subarborele drept merg pe partea stanga 
		//pt ca acolo sunt nodurile care ar veni mutate in pozitia stearsa fara sa sparga relatia
		while (this->table[successor].left != -1) {
			successor_parent = successor;
			successor = this->table[successor].left;
		}

		//cel mai mic nod mai mare ca nodul to delete
		//<=> urmatorul nod in arrayul sortat 
		//stiu ca toate numerele care raman pe partea dreapta dupa mutare sunt mai mari ca cel mutat 
		this->table[current].info = this->table[successor].info;

		//dupa mutare ramane o pozitie goala care are cel mult un right child 
		
		int successor_right_child = this->table[successor].right;
		if (successor_parent == current) {
			//daca ce am mutat a fost direct sub nodul to delete (adica nu a intrat in while)
			this->table[current].right = successor_right_child; //link the right child to the right of the node at deleted position
		}
		//daca am mai traversat inseamna ca ultima traversare a venit dinspre stanga 
		//si atunci right child devine partea stanga a successor_parent
		else this->table[successor_parent].left = successor_right_child;

		//decrement left_counts along the left part 
		int walk = this->table[current].right; //start at deleted pos
		//merg cat timp nu ajung la ultimul nod 
		while (walk != successor_right_child && walk != -1) {
			this->table[walk].left_count--; //pt fiecare nod ii scad left_count(pt ca am facut mutarea)
			walk = this->table[walk].left; //si merg spre stanga pt ca dinspre stanga am luat nodul de schimb 
		}

		//first empty primeste pozitia elementului care a fost mutat 
		this->table[successor].left = this->first_empty;
		this->first_empty = successor;

		return current; //din wrapper function parentul lui current trebuie sa pointeze pe el pt ca am schimbat doar valoarea
	}

	//keep looking for the target in the left branch 
	if (pos < size_left_subtree) 
	{
		//call recursively the before explained steps 
		this->table[current].left = removeRecursive(this->table[current].left, pos, removed, removed_val);
		if (removed) this->table[current].left_count--;
	}
	//keep looking for target in the righ branch 
	else 
	{
		int new_pos = pos - (size_left_subtree + 1); //jump over all left subtree and root
		this->table[current].right = removeRecursive(this->table[current].right, new_pos, removed, removed_val);
	}

	return current;

	//BC = Theta(1) : target is root and has 0 or 1 child 
	//WC = Theta(n) : tree is degenerate and delete the last leaf 
	//				OR delete a node that has 2 children and right subtree is a degenerated subtree => move through all to reach last value 
	//TC = O(n)
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete[] this->table;
}

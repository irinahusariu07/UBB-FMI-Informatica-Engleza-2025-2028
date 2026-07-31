#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) { 
    //initialize stack 
	this->stack_capacity = list.capacity;
	this->stack = new int[this->stack_capacity];
	this->first(); 
}

void ListIterator::first(){
    this->stack_top = -1; //reset stack to empty 
    this->current_idx = -1; 

    //start from root and go down following left 
    int node = this->list.root;
    while (node != -1) {
        this->stack[++this->stack_top] = node;//push current node idx
        node = this->list.table[node].left;//go left because there are elements that respect relation
    }

    //current element = top of the stack
    if (this->stack_top != -1) {
        this->current_idx = this->stack[this->stack_top];
    }

    //BC = Theta(1) : list empty or root doesnt have left child (root is also first el)
    //WC = Theta(n) : degenerate tree - first elem is at the bottom 
    //TC = O(n) 
}

void ListIterator::next(){
    if (!this->valid()) {
        throw std::exception();
    }

    //pop current node
    int popped_node = this->stack[this->stack_top--];

    //if popped node has a righ child -> push it and all left descendants 
    //the next node is the leftmost of right child => top of stack
    if (this->list.table[popped_node].right != -1) {
        int node = this->list.table[popped_node].right;
        while (node != -1) {
            this->stack[++this->stack_top] = node;
            node = this->list.table[node].left;
        }
    }
    if (this->stack_top != -1) {
        this->current_idx = this->stack[this->stack_top];
    }
    else {
        this->current_idx = -1;
    }

    //BC = Theta(1) : pop node that doesnt have right child 
    //WC = Theta(n) : pop a node whose right subtree is degenerate 
    //TC = O(n) 
}

bool ListIterator::valid() const{
    return this->current_idx != -1; //passed end of list
    //BC = WC = TC = Theta(1)
}

TComp ListIterator::getCurrent() const{
	if (!this->valid()) {
		throw std::exception();
	}
	return this->list.table[this->current_idx].info; 
    //BC = WC = TC = Theta(1)
}

ListIterator::~ListIterator()
{
    delete[] this->stack;
}



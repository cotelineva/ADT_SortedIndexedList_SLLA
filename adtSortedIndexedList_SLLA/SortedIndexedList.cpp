#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {

	this->relation = r;
	this->capacity = 8;
	this->elements = new TComp[capacity];
	this->next = new TComp[capacity];
	this->head = -1;
	this->nrElems = 0;

	for (int i = 0; i < capacity - 1; i++) {
		this->next[i] = i + 1;
	}
	this->next[capacity - 1] = -1;
	this->firstEmpty = 0;
}

int SortedIndexedList::size() const {
	//complexity: T(1)

	return this->nrElems;
}

bool SortedIndexedList::isEmpty() const {
	//complexity T(1)

	if (this->nrElems == 0) {
		return true;
	}
	else {
		return false;
	}
}

TComp SortedIndexedList::getElement(int i) const{
	//complexity: 
	//O(n), because of search(); 
	//T(1), if search() returns the first element

	if (i < 0 || i > this->nrElems - 1) {
		throw exception();
	}
	else {
		return this->elements[i];
	}
}

TComp SortedIndexedList::remove(int i) {
	//complexity: O(n)

	if (i < 0) {
		throw exception();
	}

	if (isEmpty() == true || search(this->elements[i]) == -1) {
		return NULL_TCOMP;
	}

	int current = this->head, previous = -1;
	TComp aux = this->elements[i];

	while (current != -1 && this->elements[current] != this->elements[i]) {
		previous = current;
		current = this->next[current];
	}

	if (current != -1) {
		if (current == this->head) {
			this->head = this->next[this->head];
		}
		else {
			this->next[previous] = this->next[current];
		}
		this->next[current] = this->firstEmpty;
		this->firstEmpty = current;
		this->nrElems--;
		
		return aux;
	}

	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
	//complexity: O(n)
	
	int current = this->head;
	while (current != -1 && this->elements[current] != e) {
		if (relation(e, this->elements[current]) == true) {
			return -1;
		}
		current = this->next[current];
	}
	if (current != -1) {
		return current;
	}
	else {
		return -1;
	}
	return -1;
}

void SortedIndexedList::add(TComp e) {
	//complexity: O(n)
	
	if (isEmpty() == true) {
		int new_position = this->firstEmpty;

		this->elements[new_position] = e;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[new_position] = this->head;
		this->head = new_position;

		this->nrElems++;
	}
	else {

		if (this->nrElems == this->capacity) {
			TComp* new_elements;
			new_elements = new TComp[this->capacity * 2];
			int* new_next;
			new_next = new int[this->capacity * 2];

			for (int i = 0; i < this->nrElems; i++) {
				new_elements[i] = this->elements[i];
				new_next[i] = this->next[i];
			}
			for (int i = this->nrElems - 1; i < this->capacity * 2 - 1; i++) {
				new_next[i] = i + 1;
			}
			new_next[this->capacity * 2 - 1] = -1;

			delete[] this->elements;
			delete[] this->next;

			this->firstEmpty = this->capacity;
			this->capacity *= 2;
			this->elements = new_elements;
			this->next = new_next;
		}

		int pos = 0;
		while (pos < this->nrElems && relation(e, this->elements[pos]) == false) {
			pos++;
		}

		int new_el = this->firstEmpty;
		this->firstEmpty = this->next[firstEmpty];
		this->elements[new_el] = e;
		this->next[new_el] = -1;	
		this->nrElems++;

		if (pos == 0) {
			if (this->head == -1) {
				this->head = new_el;
			}
			else {
				this->next[new_el] = this->head;
				this->head = new_el;
			}
		}
		else {
			int current_pos = 0;
			int current_el = this->head;
			
			while (current_el != -1 && current_pos < pos - 1) {
				current_pos++;
				current_el = this->next[current_el];
			}
			if (current_el != -1) {
				this->next[new_el] = this->next[current_el];
				this->next[current_el] = new_el;
			}
			else {
				//invalid position
				throw exception();
			}
		}
	}
}

SortedIndexedList SortedIndexedList::merge(SortedIndexedList l1, SortedIndexedList l2, Relation r) {
	//complexity: T(n + m); n is length of l1, m is length of l2

	int i = 0, j = 0;
	//SortedIndexedList l1 = SortedIndexedList(r);
	//SortedIndexedList l2 = SortedIndexedList(r);
	SortedIndexedList l3 = SortedIndexedList(r);

	while (i < l1.size() && j < l2.size()) {
		if (relation(l1.elements[i], l2.elements[j]) == true) {
			l3.add(l1.elements[i]);
			i++;
		}
		else {
			l3.add(l2.elements[j]);
			j++;
		}
	}

	if (i <= l1.size()) {
		for (int p = i; p < l1.size(); p++) {
			l3.add(l1.elements[p]);
		}
	}
	if (j <= l2.size()) {
		for (int p = j; p < l2.size(); p++) {
			l3.add(l2.elements[p]);
		}
	}

	return l3;
}

ListIterator SortedIndexedList::iterator(){

	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//complexity: O(n)

	delete[] this->elements;
	delete[] this->next;
}

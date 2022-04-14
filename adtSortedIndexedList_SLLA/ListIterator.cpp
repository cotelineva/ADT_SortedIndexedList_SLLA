#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {

	this->position = 0;
}

void ListIterator::first(){
	//complexity: T(1)

	this->position = this->list.head;
}

void ListIterator::next(){
	//complexity: T(1)
	
	if (valid() == false) {
		throw exception();
	}
	else {
		this->position++;
	}
}

bool ListIterator::valid() const{
	//complexity: T(1)

	if (list.isEmpty() == false && this->position < list.nrElems) {
		return true;
	}
	return false;
}

TComp ListIterator::getCurrent() const{
	//complexity: T(1)

	if (valid() == false) {
		throw exception();
	}
	else {
		return this->list.elements[this->position];
	}
	return NULL_TCOMP;
}



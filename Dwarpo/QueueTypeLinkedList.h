#pragma once
#include <string>
#include <sstream>
#include <iterator>

#define NULL 0
template <typename T>
class ListElem {
public:
	T* element = NULL;
	ListElem* next = NULL;
};
/**
* QueuTypeLinkedList can hold a potentially unlimited number of values, tho it stores pointers to them, this can be important, as these values may need to be freed later.
* all elements can be referenced using their indeces, tho only with diminishing speed the further down they are
* Only access to the first or last element is really, really fast
*/
template <typename T>
class QueueTypeLinkedList
{
private:
	ListElem<T>* firstElement;
	ListElem<T>* lastElement;
	unsigned long size;
public:
	QueueTypeLinkedList();
	~QueueTypeLinkedList();

	inline ListElem<T>** getElemP();
	inline ListElem<T>* firstListElem();
	inline ListElem<T>* lastListElem();
	inline int getSize();

	inline int add(const T newElement);

	inline int addBack(const T newElement);

	int push(T * newElement);

	int pushBack(T * newElement);

	std::string to_string();

	T get(unsigned int index);

	T getP(unsigned int index);

	T getLast();

	T getLastP();

	int removeElement(unsigned int index);

	int removeAndFreeElem(unsigned int index);

	int forEach(int(*fn)(T ele));

	int forEachInt(int(*fn)(int* ele));

	T begin() { return firstElement->element; }
	T end() { return lastElement->element; }

	T* pop();
	void incSize() {
		this->size++;
	}

	void decSize() {
		this->size--;
	}

	QueueTypeLinkedList<T> operator++() {
		this->firstElement = this->firstElement->next;
		return *this;
	}

};

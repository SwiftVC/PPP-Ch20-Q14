#ifndef CS_single_list_h_
#define CS_single_list_h_
#include <iostream>
#include <exception>
template<typename Iter> // requires Input_iterator<Iter>() (§19.3.3)
Iter high(Iter first, Iter last)
// return an iterator to the element in [first,last) that has the highest value
{
	Iter high = first;
	for (Iter p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

template<typename T>
class cs_slist_node {
public:
	cs_slist_node<T>* _tail;
	T _val;

	cs_slist_node<T>(T value) : _val{ value }, _tail{ nullptr } {}
	cs_slist_node<T>* _next() { return _tail; }
	int& operator*() { return _val; }
};

template<typename T>
class cs_slist {
public:
	class iterator;
private:
	cs_slist_node<T>* get_node(iterator p);
	cs_slist_node<T>* get_node_before(iterator p);
public:
	cs_slist<T>(T i) {
		front_ptr = new cs_slist_node<T>(i);
		size = 1;
	}
	cs_slist<T>() : front_ptr{ nullptr }, size{ 0 } {}
	~cs_slist<T>();
	iterator begin() { return iterator(front_ptr); }
	iterator end();
	iterator last();
	void push_back(int i);
	void push_front(int i);
	void pop_front() { erase(begin()); }
	void pop_back() { erase(last()); }
	iterator erase(iterator p); // used to handle all list deleting
	iterator insert(iterator p, const int& v); // insert node{v} as head/prev of p
	int& front()				// the first intent
	{
		return **front_ptr;
	}
	int& back()				// the last intent
	{
		return  **(get_node(last()));
	}

private:
	cs_slist_node<T>* front_ptr;
	int size{ 0 };


};

template<typename T>
class cs_slist<T>::iterator {
public:
	cs_slist_node<T>* curr; // current link
	iterator(cs_slist_node<T>* p) : curr{ p } { }
	iterator& operator++() { curr = curr->_next(); return *this; } // forward, *this returns an object equivalent to this one.
	int& operator*() { return curr->_val; } // get value (dereference)
	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!= (const iterator& b) const { return curr != b.curr; }
	cs_slist_node<T>* _next() { return curr->_tail; }
};

#include "CS_singlelist_template_functions.h"

#endif
#ifndef CS_singlelist_template_functions_h_
#define CS_singlelist_template_functions_h_
#include "CS_singlelist.h"

template<typename T>
cs_slist<T>::~cs_slist<T>() {
	if (size > 0)
	{
		while (size > 0)
		{
			auto temp = front_ptr->_tail;
			delete front_ptr;
			front_ptr = temp;
			size--;
		}
	}
}

template<typename T>
cs_slist_node<T>* cs_slist<T>::get_node(cs_slist<T>::iterator p) {
	cs_slist_node<T>* temp = front_ptr;
	cs_slist<T>::iterator temp_iter = cs_slist<T>::iterator(temp);
	int error_check{ 0 };
	while (temp_iter != p)
	{
		temp = temp->_next();
		++temp_iter;
		++error_check;
		if (error_check > size)
			throw std::exception("Invalid iterator passed to list.erase(..)");
	}
	return temp;
}

template<typename T>
cs_slist_node<T>* cs_slist<T>::get_node_before(cs_slist<T>::iterator p) {
	cs_slist_node<T>* temp = front_ptr;
	cs_slist<T>::iterator temp_iter = cs_slist<T>::iterator(temp);
	int error_check{ 0 };
	while (temp_iter != p)
	{
		cs_slist<T>::iterator next_check{ temp_iter };
		++next_check;
		if (next_check == p)
			return temp;

		temp = temp->_next();
		++temp_iter;
		++error_check;

		if (error_check > size)
			throw std::exception("Invalid iterator passed to list.erase(..)");
	}
	throw std::exception("Invalid iterator passed to list.erase(..)");
}

template<typename T>
void cs_slist<T>::push_back(int i) {
	cs_slist_node<T>* temp = new cs_slist_node<T>{ i };
	cs_slist_node<T>* second_last = get_node(last());
	temp->_tail = nullptr;
	if (second_last)	// case where push_back called for empty list
		second_last->_tail = temp;
	else
		front_ptr = temp;
	size++;
}

template<typename T>
void cs_slist<T>::push_front(int i) {
	cs_slist_node<T>* temp = new cs_slist_node<T>(i);
	temp->_tail = front_ptr;
	front_ptr = temp;
	size++;
}

template<typename T>
typename cs_slist<T>::iterator cs_slist<T>::insert(cs_slist<T>::iterator p, const int& v) {
	// no entries - return nullptr
	if (size == 0)
		return nullptr;
	// insert at front
	if (p == cs_slist<T>::iterator(front_ptr)) {
		push_front(v);
		return cs_slist<T>::iterator(front_ptr);
	}
	// insert between two entries
	if (p != end()) {
		cs_slist_node<T>* temp = new cs_slist_node<T>{ v };
		cs_slist_node<T>* node_after_insertion = get_node(p);
		cs_slist_node<T>* node_before_insertion = get_node_before(p);
		node_before_insertion->_tail = temp;
		temp->_tail = node_after_insertion;
		size++;
		return cs_slist<T>::iterator(temp);
	}
	else if (p == end()) {
		cs_slist_node<T>* temp = new cs_slist_node<T>{ v };
		cs_slist_node<T>* last_node = get_node(last());
		temp->_tail = nullptr;
		last_node->_tail = temp;
		size++;
		return cs_slist<T>::iterator(temp);
	}
	throw std::exception("Uncaught insert iterator");
}

template<typename T>
typename cs_slist<T>::iterator cs_slist<T>::erase(cs_slist<T>::iterator p) {		// used to handle all list deleting
	//no entries
	if (size == 0)
		return nullptr;
	// only entry
	else if (cs_slist<T>::iterator(front_ptr) == p && !(*front_ptr)._tail)
	{
		delete front_ptr;
		front_ptr = nullptr;
		size--;
		return nullptr;
	}
	// first in list
	else if (cs_slist<T>::iterator(front_ptr) == p) {
		auto temp = front_ptr->_next();
		front_ptr = front_ptr->_next();
		delete temp;
		size--;
		return cs_slist<T>::iterator(front_ptr);
	}
	// from second to end
	else {
		// skip to match iterator
		cs_slist_node<T>* temp = get_node(p);
		// set previous
		cs_slist_node<T>* before_temp = get_node_before(temp);
		before_temp->_tail = temp->_next();
		if (temp->_next() != nullptr)
		{
			cs_slist_node<T>* after_temp = (*temp)._next();
		}
		delete temp;
		size--;
		return cs_slist<T>::iterator(before_temp);
	}
}

template<typename T>
typename cs_slist<T>::iterator cs_slist<T>::last()
{
	cs_slist<T>::iterator it{ front_ptr };
	cs_slist<T>::iterator temp{ front_ptr };
	while (it != nullptr)
	{
		temp = it;
		++it;
	}
	return temp;
}

template<typename T>
typename cs_slist<T>::iterator cs_slist<T>::end()
{
	cs_slist<T>::iterator it(front_ptr);
	while (it != nullptr)
		++it;
	return it;
}

#endif
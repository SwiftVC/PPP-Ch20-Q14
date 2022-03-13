/*
*	Author: CS
*	Date:	2022_03_13
*
*	cs_slist has a forward iterator, the user can only increment it forwards.
*	cs_slist is an edited version of the Ch20Q13 list implementation without using the _head pointers in the member functions to edit the list.
*	aswell as
*	-	a corrected iterator namespace
*	-	generalization
* 
*	Important template lesson:
*		template<typename T>
*		typename cs_slist<T>::iterator cs_slist<T>::erase(cs_slist<T>::iterator p)
*		^ "typename" is needed when declaring variables whos class is a member of a template-dependent type
*		"there is a C++ parsing rule that says that qualified dependent names should be parsed as non-types
*		even if it leads to a syntax error"
*		Delays like this will be prevented when the Template Metaprogramming is covered.
*/

#include "CS_singlelist.h"
int main() {
	try {
			cs_slist<int> newlist(5);	// initializes a list with the number 5 as the first element
			
			newlist.push_front(8);
			newlist.push_front(80);
			newlist.back() = 50;
			
			newlist.erase(++(++newlist.begin()));	// deleting the third element, 50, with a forward iterator.
			newlist.insert(newlist.end(), 650);
			newlist.push_back(200);
			newlist.push_back(900);
			newlist.push_back(50);
			cs_slist<int>::iterator it = newlist.begin();
			std::cout << "Using the forward iterator to print the list:\n";
			while (it != newlist.end())
			{
				std::cout << *it << std::endl;
				++it;
			}
			std::cout << "Testing the list with a function of STL style:\n";
			std::cout << "The highest is:\t" << *high(newlist.begin(), newlist.end()) << std::endl;
			std::cout << "Iterators with the list object work as expected.\n";
			std::cout << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
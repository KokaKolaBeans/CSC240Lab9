//============================================================================
// Name        : LinkedCQDr.cpp
// Author      : Ivan Temesvari (edited by Kazim Zaidi)
// Version     : 10/4/2026
// Description : Linked CQ with Iterator
//============================================================================

//========================================================================================================================================================
/*
															Creative Final Feature

1. What does your feature do?
	It adds STL iterator traits and a post-increment operator, elevating the iterator to a standard-compliant Forward Iterator.
	This allows it to plug directly into C++ standard library algorithms like std::distance.
2. What concept from your AI Learning Query did it use?
	It built on our discussions about standard C++ iterator contracts and the rule of least surprise, ensuring the custom class
	behaves exactly like built-in standard containers do.
3. What did you try that did not work?
	I learned that post-increment requires returning a copy by value, rather than by reference like pre-increment
4. What would you do next if you had another week?
	Implement a const_iterator class so that range-based loops can safely traverse constant queue objects without risking accidental data modification.
*/
//========================================================================================================================================================

#include <iostream>
#include "LinkedCQ.h"
#include "LinkedCQIterator.h"
using namespace std;

int main()
{
	cout << "Print():" << endl;
	QueType<int> q;
	q.Enqueue(8);
	q.Enqueue(6);
	q.Enqueue(7);
	q.Enqueue(5);
	q.Enqueue(3);
	q.Enqueue(0);
	q.Enqueue(9);
	q.Print();

	cout << "Explicit Iterator: ";
	for (LinkedCQIterator<int> it = q.begin(); it != q.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	cout << "Range-based for: ";
	for (auto x : q)
	{
		cout << x << " ";
	}
	cout << endl;

	cout << "Doubling every item through the iterator..." << endl;
	for (int &x : q)
	{
		x = x * 2;
	}

	cout << "Range-based for: ";
	for (auto x : q)
	{
		cout << x << " ";
	}
	cout << endl;

	cout << "Print():" << endl;
	q.Print();

	// Single-element queue test
	QueType<int> p;
	p.Enqueue(42);

	cout << "Single-element queue: ";
	for (auto x : p)
	{
		cout << x << " ";
	}
	cout << endl;

	// Using a ternary operator to print "true"/"false" instead of 1/0
	cout << "begin() != end() on one: " << (p.begin() != p.end() ? "true" : "false") << endl;

	// Empty queue test
	QueType<int> emptyQ;
	cout << "Empty queue: ";
	for (auto x : emptyQ)
	{
		cout << x << " ";
	}
	cout << "(nothing printed)" << endl;
	cout << "begin() != end() on empty: " << (emptyQ.begin() != emptyQ.end() ? "true" : "false") << endl;

	return 0;
}
// g++ CSC240_LinkedQueue_Driver.cpp -o main && ./main

// g++ -std=c++17 LinkedCQDr.cpp -o LinkedCQDriver && ./LinkedCQDriver
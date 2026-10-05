#ifndef LINKEDCQITERATOR_H
#define LINKEDCQITERATOR_H
#include <stddef.h>
#include <iterator>
#include <cstddef>
#include "NodeType.h"

// ========================================================================================================================
/*
                                            Design and Documentation Question 1 [LAB 9]

Invariant: The 'item' pointer always points to the node exactly 'location' steps away from the front of the queue,
// with 'location' strictly tracking the number of forward advancements.

*/
// ========================================================================================================================

// A template for an iterator that implements the contract required by the
// range-based for-loop.

template <class T>
class LinkedCQIterator
{
public:
    // STL Iterator Traits
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    // Customize the constructor to work with the ADT.
    LinkedCQIterator(NodeType<T> *start, int loc);
    T &operator*();
    // Customize to return the proper iterator class.
    LinkedCQIterator<T> &operator++();
    LinkedCQIterator<T> operator++(int);
    // Customize to receive the correct Iterator class.
    bool operator!=(const LinkedCQIterator<T> &it) const;

    bool operator==(const LinkedCQIterator<T> &it) const;

private:
    NodeType<T> *item;
    int location;
};

// Implementation must be in header for templates

// Function: Parameterized constructor for the iterator.
// Pre:  start points to a valid node in the queue or is nullptr. loc is a non-negative integer representing the starting step count.
// Post: Iterator is initialized with the item pointer set to start and the location counter set to loc.

template <class T>
LinkedCQIterator<T>::LinkedCQIterator(NodeType<T> *start, int loc)
{

    this->item = start;
    this->location = loc;
}

// Function: Dereference operator.
// Pre:  The iterator's item pointer points to a valid, non-null node.
// Post: Returns a reference to the info data member stored inside the current node, allowing for read and write access.

template <class T>
T &LinkedCQIterator<T>::operator*()
{
    return item->info;
}

// Function: Pre-increment operator to advance the iterator.
// Pre:  The iterator points to a valid node.
// Post: The item pointer is advanced to the next node in the sequence, the location counter is incremented by 1, and a reference to this updated iterator is returned.

template <class T>
LinkedCQIterator<T> &LinkedCQIterator<T>::operator++()
{
    if (item != nullptr)
    {
        item = item->next;
    }
    location++;
    return *this;
}

// Function: Post-increment operator to advance the iterator.
// Pre:  The iterator points to a valid node.
// Post: The iterator advances its state by one node and one location step, but a copy of the iterator's state prior to the advancement is returned by value.

template <class T>

LinkedCQIterator<T> LinkedCQIterator<T>::operator++(int)
{
    LinkedCQIterator<T> temp = *this;
    ++(*this);
    return temp;
}

// Function: Inequality comparison operator.
// Pre:  This iterator and the passed iterator (it) have been initialized.
// Post: Returns true if either the item memory addresses or the location counters differ between the two iterators; returns false otherwise.

template <class T>
bool LinkedCQIterator<T>::operator!=(const LinkedCQIterator<T> &it) const
{

    return (this->item != it.item || this->location != it.location);
}

// Function: Equality comparison operator.
// Pre:  This iterator and the passed iterator (it) have been initialized.
// Post: Returns true only if both the item memory addresses and the location counters are identical between the two iterators; returns false otherwise.

template <class T>
bool LinkedCQIterator<T>::operator==(const LinkedCQIterator<T> &it) const
{
    return (this->item == it.item && this->location == it.location);
}

#endif
#ifndef LINKEDCQITERATOR_H
#define LINKEDCQITERATOR_H
#include <stddef.h>
// NodeType struct definition

template <class T>
struct NodeType
{
    T info;
    NodeType<T> *next;
};
// A template for an iterator that implements the contract required by the
// range-based for-loop.
template <class T>
class LinkedCQIterator
{
public:
    // Customize the constructor to work with the ADT.
    LinkedCQIterator(NodeType<T> *start, int loc);
    T &operator*();
    // Customize to return the proper iterator class.
    LinkedCQIterator<T> &operator++();
    // Customize to receive the correct Iterator class.
    bool operator!=(const LinkedCQIterator<T> &it) const;

    bool operator==(const LinkedCQIterator<T> &it) const;

private:
    // The start of the linked list.
    NodeType<T> *item;
    int location;
};

// Implementation must be in header for templates
template <class T>
LinkedCQIterator<T>::LinkedCQIterator(NodeType<T> *start, int loc)
{
    // First Draft
    this->item = start;
    this->location = loc; // ??
}

template <class T>
T &LinkedCQIterator<T>::operator*()
{
    T deref = item->info; // Is this right? Should the deref deref the NodeType Struct or the specific T info that sits there?
    return deref;
}

template <class T>
LinkedCQIterator<T> &LinkedCQIterator<T>::operator++()
{
    // First Draft
    item = item->next;
    location++;
}

template <class T>
bool LinkedCQIterator<T>::operator!=(const LinkedCQIterator<T> &it) const
{
    // First Draft
    return item != it.item;
}

template <class T>
bool LinkedCQIterator<T>::operator==(const LinkedCQIterator<T> &it) const
{
    // First Draft
    return item == it.item;
}

#endif
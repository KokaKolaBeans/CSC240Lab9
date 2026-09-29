#ifndef LINKEDQUEUETYPEITERATOR_H
#define LINKEDQUEUETYPEITERATOR_H
#include <stddef.h>
// NodeType struct definition
template <class ItemType>
struct NodeType
{
    ItemType info;
    NodeType<ItemType>* next;
};
// A template for an iterator that implements the contract required by the
// range-based for-loop.
template <class ItemType>
class LinkedQueueTypeIterator
{
    public:
    // Customize the constructor to work with the ADT.
    LinkedQueueTypeIterator(NodeType<ItemType>* start, int loc);
    ItemType& operator*();
    // Customize to return the proper iterator class.
    LinkedQueueTypeIterator<ItemType>& operator++();
    // Customize to receive the correct Iterator class.
    bool operator!=(const LinkedQueueTypeIterator<ItemType>& it) const;
    private:
    // The start of the linked list.
    NodeType<ItemType>* item;
    int location;
};

// Implementation must be in header for templates
template <class ItemType>
LinkedQueueTypeIterator<ItemType>::LinkedQueueTypeIterator(NodeType<ItemType>* start,
int loc)
{
//TODO
}

template <class ItemType>
ItemType& LinkedQueueTypeIterator<ItemType>::operator*()
{
//TODO
}

template <class ItemType>
LinkedQueueTypeIterator<ItemType>& LinkedQueueTypeIterator<ItemType>::operator++()
{
//TODO
}

template <class ItemType>
bool LinkedQueueTypeIterator<ItemType>::operator!=(const
LinkedQueueTypeIterator<ItemType>& it) const
{
//TODO
}

#endif
// Header file for Queue ADT.
// Template version of the Linked Queue using a front and rear pointer.
#ifndef LINKEDCQ_H
#define LINKEDCQ_H
#include "LinkedCQIterator.h"
#include "NodeType.h"

#include <new>
#include <iostream>
#include <cstddef>

// ================================================================================================
/*                                Design and Documentation Question 1 [LAB 8]

  State the invariant relating rear, rear->next, and length that holds after every operation.
  Write this as a comment in your header.

  In a circular linked Queue ADT, elements are removed from the front and added to the rear.
  The length data member strictly represents the total number of nodes in the queue, where
  length == 0 if and only if rear is nullptr. When length > 0, rear points to the most recently
  added element, and rear->next points to the element added earliest (the front of the queue).
  In a one-element list (length = 1), rear and rear -> next point to the same NodeType struct because
  the element added earliest is also the element added last and rear = front. For any list where
  length >= 1, traversing exactly 'length' nodes starting from rear->next will return to rear.

*/
// ================================================================================================

// ================================================================================================
/*                                Creative Final Feature(s)

  1. What does your feature do?
     I added an overloaded equality comparison operator (==), an IsRearNull() getter function
     (returns true if rear is nullptr, indicating an empty list with length == 0), and a move
     constructor that efficiently transfers ownership of heap resources from a temporary object.

  2. What concept from your AI Learning Query did it use?
     It applied the circular list traversal logic and pointer-reset principles discussed during
     the destructor query. Walking the nodes without a null terminator was essential for implementing
     the node-by-node comparison in the == operator, and proper pointer handoff prevented errors.

  3. What did you try that did not work?
     I initially attempted to implement the comparison operator as a friend function before realizing
     it needed full member access. I also tested a move constructor that forgot to nullify the
     source object's rear pointer, which caused a double-free crash upon destruction.

  4. What would you do next if you had another week?
     I would implement a move assignment operator and integrate comprehensive try-catch blocks
     for cleaner error handling.

*/
// ================================================================================================

// template <class T>

// struct NodeType
// {
//   T info;
//   NodeType<T> *next;
// };

class FullQueue
{
};
class EmptyQueue
{
};

template <class T>
class QueType
{
public:
  QueType();
  // Class constructor.
  // Because there is a default constructor, the precondition
  // that the queue has been initialized is omitted.
  QueType(int max);
  // Parameterized class constructor.
  ~QueType();
  // Class destructor.
  QueType(const QueType &anotherQue);
  // Copy constructor
  void MakeEmpty();
  // Function: Initializes the queue to an empty state.
  // Post: Queue is empty.
  bool IsEmpty() const;
  // Function: Determines whether the queue is empty.
  // Post: Function value = (queue is empty)
  bool IsFull() const;
  // Function: Determines whether the queue is full.
  // Post: Function value = (queue is full)
  void Enqueue(T newItem);
  // Function: Adds newItem to the rear of the queue.
  // Post: If (queue is full) FullQueue exception is thrown
  //       else newItem is at rear of queue.
  void Dequeue(T &item);
  // Function: Removes front item from the queue and returns it in item.
  // Post: If (queue is empty) EmptyQueue exception is thrown
  //       and item is undefined
  //       else front element has been removed from queue and
  //       item is a copy of removed element.
  void Print();
  // Function: Display the contents of the QueType in the console output.
  // Post: The QueType remains unchanged.
  QueType<T> &operator=(const QueType &anotherQue);
  // Function: Copy Assignment Operator
  // Pre:  This queue and anotherQue have been initialized.
  // Post: This queue is a deep copy of anotherQue;
  //       a reference to this queue (*this) is returned.
  bool operator==(const QueType &anotherQue) const;
  // Function: Equality Comparison Operator
  // Pre:  This queue and anotherQue have been initialized.
  // Post: Returns true if both queues contain the same elements in the
  //       same relative order; false otherwise.
  QueType(QueType &&anotherQue) noexcept;
  // Function: Move Constructor
  // Pre:  anotherQue has been initialized.
  // Post: This queue takes ownership of anotherQue's resources;
  //       anotherQue is left in a valid, empty state.

  bool IsRearNull() const;
  // Function: Determines whether the internal rear pointer is null.
  // Pre:  Queue has been initialized.
  // Post: Returns true if rear is nullptr; false otherwise.
  //       The queue remains unchanged.

  LinkedCQIterator<T> begin();
  LinkedCQIterator<T> end();

private:
  NodeType<T> *rear;
  int length;
};

template <class T>
void QueType<T>::Print() // rewrote to circular
{
  if (IsEmpty())
  {
    throw EmptyQueue();
  }
  else
  {
    NodeType<T> *tempPtr = rear;
    tempPtr = tempPtr->next;
    std::cout << "Front:";
    while (tempPtr != rear)
    {
      std::cout << tempPtr->info << " ";
      tempPtr = tempPtr->next;
    }
    std::cout << tempPtr->info << ":Rear" << std::endl;
  }
}

template <class T>

QueType<T>::QueType() // Class constructor. // rewrote to circular
// Post:  front and rear are set to NULL.
{
  rear = nullptr;
  length = 0;
}

template <class T>

void QueType<T>::MakeEmpty() // rewrote to circular

// Post: Queue is empty; all elements have been deallocated.
{
  if (IsEmpty()) // special case 0-node
  {
    return; // throwing here is a poor design decision
  }

  NodeType<T> *tempPtr;
  tempPtr = rear->next; // tempPtr -> first node
  rear->next = nullptr; // final element is marked

  while (tempPtr->next != nullptr) // after while, tempPtr -> final node
  {
    rear = tempPtr;
    tempPtr = tempPtr->next;
    delete rear;
  }
  delete tempPtr; // final node; special case 1-node;
  rear = nullptr; // empty queue invariant
  length = 0;
}

// Class destructor.
template <class T> // this works - no backing structure to delete after MakeEmpty(); no rewrite to circular
QueType<T>::~QueType()
{
  MakeEmpty();
}

template <class T> // no rewrite to circular
bool QueType<T>::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
  NodeType<T> *location;
  try
  {
    location = new NodeType<T>;
    delete location;
    return false;
  }
  catch (std::bad_alloc &)
  {
    return true;
  }
}

template <class T> // rewrote to circular
bool QueType<T>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
  return (length == 0);
}

template <class T>                  // Deep Copy
void QueType<T>::Enqueue(T newItem) // rewrote to circular
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.

{
  if (IsFull())
    throw FullQueue();
  else
  {
    NodeType<T> *newNode;
    newNode = new NodeType<T>; // pointer to newNode
    newNode->info = newItem;

    if (IsEmpty())
    {
      rear = newNode;
      newNode->next = rear;
    }
    else
    {
      newNode->next = rear->next;
      rear->next = newNode;
      rear = newNode;
    }
    length++;
  }
}

template <class T> // rewrote to circular
void QueType<T>::Dequeue(T &item)
// Removes front item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the front of the queue has been
//       removed and a copy returned in item;
//       othersiwe a EmptyQueue exception has been thrown.
{
  if (IsEmpty()) // special case 0-node
  {
    throw EmptyQueue();
  }

  item = rear->next->info; // return info to caller;

  if (length == 1) // special case 1-node rear->next == rear
  {
    delete rear;
    rear = nullptr;
  }
  else // general case n-node
  {

    NodeType<T> *tempPtr;
    tempPtr = rear->next;          // tempPtr points to first element
    rear->next = rear->next->next; // last element points to second element
    delete tempPtr;
  }
  length--;
  return;
}

template <class T> // rewrote to circular copy construtor
QueType<T>::QueType(const QueType &anotherQue)
{

  rear = nullptr;
  length = 0;

  if (anotherQue.IsEmpty()) // special case 0-node
  {
    return;
  }

  NodeType<T> *ptrArg = anotherQue.rear->next;

  for (int k = 0; k < anotherQue.length; k++)
  {
    Enqueue(ptrArg->info);
    ptrArg = ptrArg->next;
  }
  return;
}

template <class T>
QueType<T> &QueType<T>::operator=(const QueType<T> &anotherQue)
{
  if (this == &anotherQue) // compare memory addresses; check for self-assignment
  {
    return *this;
  }
  else
  {
    MakeEmpty();
    if (anotherQue.IsEmpty())
    {
      return *this;
    }

    NodeType<T> *ptrArg = anotherQue.rear->next; // for arg

    for (int k = 0; k < anotherQue.length; k++)
    {
      Enqueue(ptrArg->info);
      ptrArg = ptrArg->next;
    }
    return *this;
  }
}

template <class T>
bool QueType<T>::operator==(const QueType<T> &anotherQue) const
{

  if (length != anotherQue.length) // lengths are equal
  {
    return false;
  }

  if (length == 0)
  {
    return true;
  }

  NodeType<T> *ptrArg;
  NodeType<T> *ptrThis;

  ptrArg = anotherQue.rear->next;
  ptrThis = rear->next;

  for (int k = 0; k < length; k++)
  {
    if (ptrArg->info != ptrThis->info)
    {
      return false;
    }
    ptrThis = ptrThis->next;
    ptrArg = ptrArg->next;
  }
  return true;
}

template <class T>
QueType<T>::QueType(QueType<T> &&anotherQue) noexcept
{
  length = anotherQue.length;
  rear = anotherQue.rear;

  anotherQue.rear = nullptr;
  anotherQue.length = 0;
}

template <class T>

bool QueType<T>::IsRearNull() const
{
  return (rear == nullptr);
}

// Function: Returns an iterator representing the beginning of the queue.
// Pre:  Queue has been initialized.
// Post: If the queue is empty, returns an iterator initialized with nullptr and location 0.
//       Otherwise, returns an iterator starting at the front node (rear->next) with location 0.
//       The queue remains unchanged.

template <class T>
LinkedCQIterator<T> QueType<T>::begin()
{
  if (length == 0)
  {
    return LinkedCQIterator<T>(nullptr, 0);
  }
  return LinkedCQIterator<T>(rear->next, 0);
}

// Function: Returns an iterator representing the past-the-end boundary of the queue.
// Pre:  Queue has been initialized.
// Post: If the queue is empty, returns an iterator initialized with nullptr and location 0.
//       Otherwise, returns an iterator pointing to the front node (rear->next) with location equal to the queue's length.
//       The queue remains unchanged.

template <class T>
LinkedCQIterator<T> QueType<T>::end()
{
  if (length == 0)
  {
    return LinkedCQIterator<T>(nullptr, length);
  }
  return LinkedCQIterator<T>(rear->next, length);
}

#endif

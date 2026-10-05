// Header file for Queue ADT.
// Template version of the Linked Queue using a front and rear pointer.
#ifndef LINKEDCQ_H
#define LINKEDCQ_H
#include <new>
#include <iostream>
#include <cstddef>

// ================================================================================================
/*                                Design and Documentation Question 1

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

template <class T>

struct NodeType
{
  T info;
  NodeType<T> *next;
};

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

  LinkedQueueTypeIterator<T> begin();
  LinkedQueueTypeIterator<T> end();

private:
  NodeType<T> *rear;
  int length;
};

template <class ItemType>
void QueType<ItemType>::Print() // rewrote to circular
{
  if (IsEmpty())
  {
    throw EmptyQueue();
  }
  else
  {
    NodeType<ItemType> *tempPtr = rear;
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

template <class ItemType>

QueType<ItemType>::QueType() // Class constructor. // rewrote to circular
// Post:  front and rear are set to NULL.
{
  rear = nullptr;
  length = 0;
}

template <class ItemType>

void QueType<ItemType>::MakeEmpty() // rewrote to circular

// Post: Queue is empty; all elements have been deallocated.
{
  if (IsEmpty()) // special case 0-node
  {
    return; // throwing here is a poor design decision
  }

  NodeType<ItemType> *tempPtr;
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
template <class ItemType> // this works - no backing structure to delete after MakeEmpty(); no rewrite to circular
QueType<ItemType>::~QueType()
{
  MakeEmpty();
}

template <class ItemType> // no rewrite to circular
bool QueType<ItemType>::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
  NodeType<ItemType> *location;
  try
  {
    location = new NodeType<ItemType>;
    delete location;
    return false;
  }
  catch (std::bad_alloc &)
  {
    return true;
  }
}

template <class ItemType> // rewrote to circular
bool QueType<ItemType>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
  return (length == 0);
}

template <class ItemType>                         // Deep Copy
void QueType<ItemType>::Enqueue(ItemType newItem) // rewrote to circular
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.

{
  if (IsFull())
    throw FullQueue();
  else
  {
    NodeType<ItemType> *newNode;
    newNode = new NodeType<ItemType>; // pointer to newNode
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

template <class ItemType> // rewrote to circular
void QueType<ItemType>::Dequeue(ItemType &item)
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

    NodeType<ItemType> *tempPtr;
    tempPtr = rear->next;          // tempPtr points to first element
    rear->next = rear->next->next; // last element points to second element
    delete tempPtr;
  }
  length--;
  return;
}

template <class ItemType> // rewrote to circular copy construtor
QueType<ItemType>::QueType(const QueType &anotherQue)
{

  rear = nullptr;
  length = 0;

  if (anotherQue.IsEmpty()) // special case 0-node
  {
    return;
  }

  NodeType<ItemType> *ptrArg = anotherQue.rear->next;

  for (int k = 0; k < anotherQue.length; k++)
  {
    Enqueue(ptrArg->info);
    ptrArg = ptrArg->next;
  }
  return;
}

template <class ItemType>
QueType<ItemType> &QueType<ItemType>::operator=(const QueType &anotherQue)
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

    NodeType<ItemType> *ptrArg = anotherQue.rear->next; // for arg

    for (int k = 0; k < anotherQue.length; k++)
    {
      Enqueue(ptrArg->info);
      ptrArg = ptrArg->next;
    }
    return *this;
  }
}

template <class ItemType>
bool QueType<ItemType>::operator==(const QueType &anotherQue) const
{

  if (length != anotherQue.length) // lengths are equal
  {
    return false;
  }

  if (length == 0)
  {
    return true;
  }

  NodeType<ItemType> *ptrArg;
  NodeType<ItemType> *ptrThis;

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

template <class ItemType>
QueType<ItemType>::QueType(QueType &&anotherQue) noexcept
{
  length = anotherQue.length;
  rear = anotherQue.rear;

  anotherQue.rear = nullptr;
  anotherQue.length = 0;
}

template <class ItemType>

bool QueType<ItemType>::IsRearNull() const
{
  return (rear == nullptr);
}

template <class ItemType>

QueType<ItemType> begin()
{
}

template <class ItemType>

QueType<ItemType> end()
{
}

#endif

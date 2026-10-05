LinkedCQ.h -> a linked circular queue class template from Lab8
LinkedCQDr.h -> the driver designed to demonstrate LinkedCQ
LinkedCQIterator.h -> an iterator for LinkedCQ

-> We are supposed to add these to the LinkedQueueType (LinkedCQ.h)

LinkedQueueTypeIterator<ItemType> begin();
LinkedQueueTypeIterator<ItemType> end();

-> but shouldn't it be this?
template <class ItemType>

QueType<ItemType> begin()
{
}

template <class ItemType>

QueType<ItemType> end()
{
}

LinkedCQ was originally called LinkedQueType

1. State the invariant relating rear, rear->next, and length that holds after every operation. Write this as a comment in your header.

length
rear
front

-> FRONT: Remove; REAR: add
-> Length: number of NodeType structs; = 0 iff rear is nullptr
-> Length > 0: REAR - most recently added
-> Length = 1: rear and rear->next SAME (front == rear)
-> Length >=1: starting at rear->next (front) and traversing 'length' nodes lands you at rear

2. Show the code in your destructor that guarantees termination. How does it know it has come all the way around, and what would happen if you had written the loop condition as while (p != nullptr)?

LINE 156 -> destructor calls MakeEmpty()
Line 141, 143 (MakeEmpty()) -> I DO use while (p!= nullptr), but this works because I disconnect the final node before looping and destroying. -> this relies on proper disconnection and indicates the end of the while
If I instead used length to iterate through the nodes to delete them, the final node's 'next' would be a dangling pointer to deallocated memory --> double-free

3. Your copy constructor produces an independent queue. Point to the line that allocates new nodes. Then describe precisely what would go wrong at the end of main if you had copied the pointer instead.

LINE 249 -> Copy Constructor calls Enqueue
LINE 187 -> Enqueue allocates new nodes and places them before the previous last and the first element
Copy Pointers -> same memory location; both objects go out of scope -> double-free. We need to make deep copies that create independent objects with unique pointers when copied

4. Your operator= has a case the copy constructor does not: self-assignment (q = q). Show how you handled it, or say honestly that you did not.
   LINE 274 -> checks to see if both L and RHS objects occupy the same memory address

5. Dequeue from a one-item queue. What does rear have to become, and does your code do it? Then dequeue from an empty queue and show what happens.

-> rear has to become nullptr (LINE 231)

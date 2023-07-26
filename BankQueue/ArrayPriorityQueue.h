#pragma once

#include "QueueInterface.h" 
//const int MAX_QUEUE = 50; 

template<class ItemType>
class ArrayPriorityQueue : public QueueInterface<ItemType>
{
private:
   ItemType items[MAX_QUEUE];  // Array of queue items 
   int       front;                // Index to front of queue 
   int       back;                 // Index to back of queue 
   int       count;                // Number of items currently in the queue 
public:
   ArrayPriorityQueue();
   // Copy constructor and destructor supplied by compiler 
   bool isEmpty() const;
   bool enqueue(const ItemType& newEntry);
   bool dequeue();
   ItemType peekFront()  const;
}; // end ArrayPriorityQueue


template<class ItemType>
ArrayPriorityQueue<ItemType>::ArrayPriorityQueue() : front(0), back(MAX_QUEUE - 1), count(0)
{ } // end default constructor 

template<class ItemType>
bool ArrayPriorityQueue<ItemType>::isEmpty() const
{
   return count == 0;
} // end isEmpty 

template<class ItemType>
bool ArrayPriorityQueue<ItemType>::enqueue(const ItemType& newEntry)
{
   bool result = false;
   if (count < MAX_QUEUE) {

      int insert_pos = front;
      back = (back + 1) % MAX_QUEUE;//make room for insert
      while (items[insert_pos] < newEntry && insert_pos != back) {
         insert_pos = (insert_pos + 1) % MAX_QUEUE;
      }// Finding spot to insert
      for (int pos = back; pos != insert_pos; pos = (pos - 1) % MAX_QUEUE) {
         items[pos] = items[pos - 1];
      }//Shuffling to make room for insert

      items[insert_pos] = newEntry; //inserting
      count++;// counting the thing we inserted
      result = true;// We did it :)
   }
   return result;
} // end enqueue 

template<class ItemType>
bool ArrayPriorityQueue<ItemType>::dequeue()
{
   //REMOVE HIGHEST PRIORITY ENTRY, DUE TO THE NATURE OF ENQUEUE THIS IS ALWAYS THE TOP ELEMENT.
   bool result = false;
   if (!isEmpty())
   {
      front = (front + 1) % MAX_QUEUE;
      count--;
      result = true;
   }  // end if 
   return result;
} // end dequeue 

template<class ItemType>
ItemType ArrayPriorityQueue<ItemType>::peekFront() const
{
   // Enforce precondition 
   if (isEmpty())
      throw std::string("peekFront() called with empty queue");
   // Queue is not empty; return front 
   return items[front];
} // end peekFront   
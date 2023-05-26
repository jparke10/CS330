/*************************************
CIS 330 Lab 7: Operator overloading, namespaces, and static members

The idea of this lab is to improve a simple queue data structure by adding overloaded operators for common tasks.
Specifically, you will:

  1) Overload the << operator so that objects of class IntQueue can be inserted into ostreams.
     For example, if Q is an object of class IntQueue, the expression `cout << Q` should print the contents of Q on standard out.

  2) Overload the << operator so that it can be used to enqueue ints.
     For example, if Q is an object of class IntQueue, the expression `Q << 10 << 20 << 30` should push 10, 20, and 30 onto the queue in that order.

  3) Overload the >> operator so that it can be used to dequeue ints.
     For example, if Q is an object of class IntQueue with some values already enqueued and a, b, and c are int variables,
     the expression `Q >> a >> b >> c` should dequeue the top three values from the queue and store them in a, b, and c.

Extra:

  Find and fix my memory leak

*************************************/

#include <iostream>

//
// A namespace to hold the queue class and other related functions, variables, and constants.
//
namespace Mem {

  //
  // This class provides a generic linked-list element
  //
  template <class T>
  class Elem {
    T data;
    Elem *next;
    int id;

    //
    // This static data member is incremented each time an Elem object is constructed,
    // allowing the generation of a unique id for each Elem object.
    // Clearly this is overkill for this lab, but you can imagine where this might be useful.
    //
    static int count;

  public:
    //
    // Constructors
    //
    Elem() : next(NULL), id(count++) {}
    Elem(T newData) : data(newData), next(NULL), id(count++) {}
    Elem(T newData, Elem *newNext) : data(newData), next(newNext), id(count++) {}
    
    //
    // Allow access to `Next` data member through getter and setter
    //
    Elem * setNext(Elem *newNext) { next = newNext; return this; }
    Elem * getNext() { return next; }
    
    //
    // Allow access to `Data` data member through getter and setter
    //
    Elem * setData(T newData) { data = newData; return this; }
    T getData() { return data; }

    //
    // Accept overloaded << operator as friend
    //
    template <class J>
    friend std::ostream & operator<<(std::ostream &s, Elem<J> *e);
  };

  
  //
  // This class implements a queue of ints on a linked list of Elem objects
  //
  class IntQueue {

    Elem<int> *head;
    Elem<int> *tail;

  public:
    //
    // Constructor
    //
    IntQueue(): head(NULL), tail(NULL) {}

    //
    // Basic queue methods
    //
    void Enqueue(int newValue);
    int Dequeue();

    // TODO: Add overloaded operator declarations and / or friend statements here
    friend std::ostream& operator<<(std::ostream& output, IntQueue& intq);
  };

  // TODO: Add prototypes for any of IntQueue's friends here
  //
  std::ostream& operator<<(std::ostream& output, IntQueue& intq) {
	  Elem<int> *element = intq.head;
	  while (element != NULL) {
		  output << element;
		  element = element->getNext();
	  }
	  return output;
  }
}

//
// The static counter for the `Elem` class must be initialized outside of the class definition.
//
template <class T>
int Mem::Elem<T>::count = 0;

//
// Implementation of enqueue method
//
void
Mem::IntQueue::Enqueue(int newValue)
{
  Elem<int> *tmp = new Elem<int>(newValue);
  if (tail == NULL) {
    head = tail = tmp;
  } else {
    tail->setNext(tmp);
    tail = tmp;
  }
}

//
// Implementation of dequeue method
//
int
Mem::IntQueue::Dequeue()
{
  Elem<int> *tmp = head;
  if (head == NULL) {
    return -1;
  }
  head = head->getNext();
  if (head == NULL) {
    tail = NULL;
  }
  return tmp->getData();
}

//
// Note that we overload << to take a pointer to an object of type Elem and follow the pointer to print the object's actual fields.
// This is because the methods that deal with Elem objects (Enqueue, Dequeue) deal with pointers:
// it is then useful to be able to directly insert an object into a stream just from its pointer.
// 
template <class T>
std::ostream &
Mem::operator<<(std::ostream &s, Mem::Elem<T> *e)
{
  if (e == NULL) {
    s << "EmptyElem()" << std::endl;
  } else {
    s << "Elem(id=" << e->id << ", data=" << e->data << ", next=" << static_cast<void*>(e->next) << ")" << std::endl;
  }
  return s;
}

// TODO: Add overloaded operator implementations here
Mem::IntQueue& operator<<(Mem::IntQueue& queue, int num) {
	queue.Enqueue(num);
	return queue;
}

Mem::IntQueue& operator>>(Mem::IntQueue& queue, int& num) {
	num = queue.Dequeue();
	return queue;
}
//
// Test program 
//
int
main()
{
  Mem::IntQueue Q;

  std::cout << Q.Dequeue() << std::endl;

  Q.Enqueue(10);
  Q.Enqueue(20);
  Q.Enqueue(30);

  std::cout << Q.Dequeue()
     << " " << Q.Dequeue()
     << " " << Q.Dequeue() << std::endl;

  // TODO: Add some code to test your overloaded operators
  // For example:
  std::cout << std::endl << std::endl;
  int tmp[4];

  // Enqueue some items
  Q << 2 << 3 << 5 << 7;

  // Print the contents of the queue
  std::cout << Q << std::endl;

  // Dequeue some items
  Q >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3];

  // Check one of the items we dequeued
  std::cout << tmp[3] << std::endl;

  return 0;
}

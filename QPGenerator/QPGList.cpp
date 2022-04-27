#include <iostream>
#include <string>
#include "QPGList.h"

template <class E>
QPGList<E>::QPGList()			        // constructor
    : head(NULL) { }

template <class E>
QPGList<E>::~QPGList()			        // destructor
{
    getFirst();
    while (!isEmpty()) remove();
}

template <class E>
bool QPGList<E>::isEmpty() const		    // is list empty?
{ return head == NULL; 
}

template <class E>
const E& QPGList<E>::getFirst() const	    // set position to first element and return first element
{
    previous = NULL;
    current = head;
    return getCurrent(); }

template <class E>
const E& QPGList<E>::getCurrent() const	    // return current position element
{   return current->elem; }

template <class E>
const E& QPGList<E>::getNext() const	    // move position to next element and return the element
{
    previous = current;
    current = current->next;
    return getCurrent();
}

template <class E>
void QPGList<E>::add(const E& e){
    QPGNode<E>* v = new QPGNode<E>;				// create new node
    v->elem = e;					            // store data
    tail->next = v;					            // add at the end
    tail = v;	                                // not tail as new item
}

template <class E>
bool QPGList<E>::remove() {
    if (current == NULL) return false;

    if (current == head) {
        previous = NULL;
        head = current->next;
        delete current;
        current = head;
    }
    else
    {
        previous->next=current->next;
        delete current;
        current = previous->next;
    }
    return true;
}
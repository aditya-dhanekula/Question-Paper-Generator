#pragma once
#include <stddef.h>
template <class E>
class QPGNode {					        // singly linked list node
public:
    E* elem=NULL;					        // linked list element value
    QPGNode<E>* next=NULL;				    // next item in the list
    template <typename E> 
    friend class QPGList;		    // provide QPGList access
};

template <class E>
class QPGList {				            // a singly linked list
public:
    QPGList();				            // empty list constructor
    ~QPGList();				           // destructor
    bool isEmpty() const;			    // is list empty?
    void add(E* e);
    bool remove();                   // remove current position element and set current to next item
    void removeAll();               //remove all elements from the list
    E* getFirst() ;			    // return first element in the Queue
    E* getCurrent() ;
    E* getNext() ;
    void sort();

private:
    QPGNode<E>* head;
    QPGNode<E>* tail;				        // head of the list
    QPGNode<E>* previous;                   // previous item in the list 
    QPGNode<E>* current;                    //Current item in the list
};


#include <iostream>
#include <string>
#include "QPGList.h"

template <class E>
QPGList<E>::QPGList()			        // constructor
    : head(NULL), tail(NULL), previous(NULL), current(NULL) { }

template <class E>
QPGList<E>::~QPGList()			        // destructor
{
    removeAll();
}

template <class E>
bool QPGList<E>::isEmpty() const		    // is list empty?
{
    return head == NULL;
}

template <class E>
 E* QPGList<E>::getFirst() 	    // set position to first element and return first element
{
    previous = NULL;
    current = head;
    return getCurrent();
}

template <class E>
E* QPGList<E>::getCurrent() 	    // return current position element
{
    if (current != NULL)
        return current->elem;
    else
        return NULL;
}

template <class E>
 E* QPGList<E>::getNext() 	    // move position to next element and return the element
{
    previous = current;
    current = current->next;
    return getCurrent();
}

template <class E>
void QPGList<E>::add( E* e) {
    QPGNode<E>* v = new QPGNode<E>;				// create new node
    v->elem = e;					            // store data
    if (tail == NULL) {
        tail = v;
        head = v;
        head->next = NULL;
    }
    else{
    tail->next = v;					            // add at the end
    tail = v;	                                // not tail as new item
    tail->next = NULL;
    }
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
        previous->next = current->next;
        delete current;
        current = previous->next;
    }
    return true;
}

template <class E>
void QPGList<E>::removeAll() {
    getFirst();
    while (!isEmpty()) remove();
    head = NULL;
    tail = NULL;
    previous = NULL;
    current = NULL;
}

template <class E>
void QPGList<E>::sort() {
    if (head == NULL) return;
    for (QPGNode<E>* ptr1 = head; ptr1->next != NULL; ptr1 = ptr1->next) {
        QPGNode<E>* min = ptr1;
        for (QPGNode<E>* ptr2 = ptr1->next; ptr2!= NULL; ptr2 = ptr2->next) {
            if ( E(ptr2->elem) < E(min->elem)) {
                min = ptr2;
            }
        }
        if (min != ptr1) {
            E* temp = min->elem;
            min->elem = ptr1->elem;
            ptr1->elem = temp;
        }
    }
}


#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"



template <typename ValueType>
class DoublyLinkedList
{
    // The forward declarations of these classes allows us to establish
    // that they exist, but delay displaying all of the details until
    // later in the file.
    //
    // (This is generally a good style, with the most important details
    // appearing earlier in the class declaration.  That's the same
    // reason why we're implementing the bodies of the member functions
    // outside of the class declaration.)
public:
    class Iterator;
    class ConstIterator;


private:
    struct Node;


public:

    void printList();
    // Initializes this list to be empty.
    DoublyLinkedList() noexcept;

    // Initializes this list as a copy of an existing one.
    DoublyLinkedList(const DoublyLinkedList& list);

    // Initializes this list from an expiring one.
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;


    // Destroys the contents of this list.
    virtual ~DoublyLinkedList() noexcept;


    // Replaces the contents of this list with a copy of the contents
    // of an existing one.
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    // Replaces the contents of this list with the contents of an
    // expiring one.
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


    // addToStart() adds a value to the start of the list, meaning that
    // it will now be the first value, with all subsequent elements still
    // being in the list (after the new value) in the same order.
    void addToStart(const ValueType& value);

    // addToEnd() adds a value to the end of the list, meaning that
    // it will now be the last value, with all subsequent elements still
    // being in the list (before the new value) in the same order.
    void addToEnd(const ValueType& value);

    void insert(const ValueType& value);
    // removeFromStart() removes a value from the start of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the first one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromStart();

    // removeFromEnd() removes a value from the end of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the last one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromEnd();


    // first() returns the value at the start of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& first() const;
    ValueType& first();


    // last() returns the value at the end of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& last() const;
    ValueType& last();


    // isEmpty() returns true if the list has no values in it, false
    // otherwise.
    bool isEmpty() const noexcept;


    // size() returns the number of values in the list.
    unsigned int size() const noexcept;



    // There are two kinds of iterators supported: Iterators and
    // ConstIterators.  They have similar characteristics; they both
    // allow you to see what values are in the list and move back and
    // forth between them.  The difference is that ConstIterators allow
    // you to see the elements but not modify them, while Iterators also
    // support modification of the list (both by modifying the elements
    // directly, and also by inserting or removing values at arbitrary
    // locations).
    //
    // At any given time, an iterator refers to a value in the list.
    // There are also two additional places it can refer: "past start"
    // and "past end", which are the positions directly before the
    // first value and directly after the last one, respectively.
    // Except with respect to those boundaries, they can be moved
    // both forward and backward.
    //
    // Note, too, that the reason we have a ConstIterator class instead
    // of just saying "const Iterator" is because a "const Iterator"
    // is something different: It's an Iterator object that you can't
    // modify (i.e., you can't move it around).  What a ConstIterator
    // holds constant isn't the iterator; it's the list that's protected
    // by it.


    // iterator() creates a new Iterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    Iterator iterator();


    // constIterator() creates a new ConstIterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    ConstIterator constIterator() const;


public:
    // The IteratorBase class is the base class for our two kinds of
    // iterators.  Because there are so many similarities between them,
    // we write those similarities in a base class, then inherit from
    // that base class to specify only the differences.
    class IteratorBase
    {
    public:
        // Initializes a newly-constructed IteratorBase to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        IteratorBase(const DoublyLinkedList& list) noexcept;


        // moveToNext() moves this iterator forward to the next value in
        // the list.  If the iterator is refrering to the last value, it
        // moves to the "past end" position.  If it is already at the
        // "past end" position, an IteratorException will be thrown.
        void moveToNext();


        // moveToPrevious() moves this iterator backward to the previous
        // value in the list.  If the iterator is refrering to the first
        // value, it moves to the "past start" position.  If it is already
        // at the "past start" position, an IteratorException will be thrown.
        void moveToPrevious();


        // isPastStart() returns true if this iterator is in the "past
        // start" position, false otherwise.
        bool isPastStart() const noexcept;


        // isPastEnd() returns true if this iterator is in the "past end"
        // position, false otherwise.
        bool isPastEnd() const noexcept;
    
    protected:
        // You may want protected member variables and member functions,
        // which will be accessible to the derived classes.
        const DoublyLinkedList<ValueType>* ll;
        DoublyLinkedList<ValueType>::Node* itHead;
        const DoublyLinkedList<ValueType>::Node* notChangeHead;
        const DoublyLinkedList<ValueType>::Node* itTail;
        bool isPast;
        bool isPastS;

    };


    class ConstIterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed ConstIterator to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        ConstIterator(const DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        const ValueType& value() const;

    private:
        DoublyLinkedList<ValueType>::Node* constHead;
        const  DoublyLinkedList<ValueType>* constLL;
    };


    class Iterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        Iterator(DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        ValueType& value() const;


        // insertBefore() inserts a new value into the list before
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past start" position, an IteratorException
        // is thrown.
        void insertBefore(const ValueType& value);


        // insertAfter() inserts a new value into the list after
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past end" position, an IteratorException
        // is thrown.
        void insertAfter(const ValueType& value);


        // remove() removes the value to which this iterator refers,
        // moving the iterator to refer to either the value after it
        // (if moveToNextAfterward is true) or before it (if
        // moveToNextAfterward is false).  If the iterator is in the
        // "past start" or "past end" position, an IteratorException
        // is thrown.
        void remove(bool moveToNextAfterward = true);

    private:
        DoublyLinkedList<ValueType>* iterLL;
        DoublyLinkedList<ValueType>::Node* iterHead;

    };


private:
    // A structure that contains the vital parts of a Node in a
    // doubly-linked list, the value and two pointers: one pointing
    // to the previous node (or nullptr if there isn't one) and
    // one pointing to the next node (or nullptr if there isn't
    // one).
    struct Node
    {
        ValueType value;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;

   unsigned int currSize;
};



template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
    :head{new Node()}, tail{new Node()}, currSize{0}
{
    head = nullptr;
    head = nullptr;

    tail = nullptr;
    tail = nullptr;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
    :head{new Node()}, tail{new Node()}, currSize{0}
{
    head->prev = list.head->prev;
    head->next = list.head->next;

    tail->prev = list.tail->prev;
    tail->next = list.tail->next;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
{
}


template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
    return *this;
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
    return *this;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{
    Node* newNode = new Node();
    newNode->value = value;

    if (currSize == 0)
    {
        head = newNode;
        tail = newNode;
    }
    else
    { 
        newNode->value = value;
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
            newNode->next->prev = newNode;
        }
    }

    currSize += 1;    
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::insert(const ValueType& value)
{
    Node* newNode = new Node();
    newNode->value = value;

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->prev = head->prev;
        newNode->next = head;
        head = newNode;
    }

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
    Node* newNode = new Node();
    newNode->value = value;

    if (tail == nullptr)
    {
        head = newNode;
        tail = head;
    }
    else
    {
        newNode->next = nullptr;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;

    }

    currSize += 1;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{
   
    if (head == tail) 
    { 
        head = nullptr;
        tail = nullptr;
    }
    else 
    {              
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
    if (currSize > 0)
    {
        currSize -= 1;
    }
   
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
    if (tail == head) 
    { 
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else    
    {   
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
       
    } 
    if (currSize > 0)
    {
        currSize -= 1;
    }
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
    if (currSize == 0)
    {
        throw EmptyException();
    }
    return head->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
    if (currSize == 0)
    {
        throw EmptyException();
    }
   return head->value;
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
    if (currSize == 0)
    {
        throw EmptyException();
    }
    return tail->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
    if (currSize == 0)
    {
        throw EmptyException();
    }
    return tail->value;
}


template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return currSize;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
    return currSize == 0;
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}


template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
    :isPast{false}, isPastS{false}
{
    
    ll = &list;

    if (ll->head != nullptr)
    {
        itHead = ll->head;
        notChangeHead = ll->head;
    }
    else{itHead = nullptr;}

    if (ll->tail != nullptr)
    {
        itTail = ll->tail;
    }
    else{itTail = nullptr;}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
    if (!isPast)
    {
        if (itHead->next != nullptr)
        {
            if (itHead->next != nullptr)
            {
                itHead = itHead->next;
            }
            else
            {
                itHead = nullptr;
            }
        }
        else
        {
            isPast = true;
        }
    }
    else
    {
        throw IteratorException();
    }
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
    if (!isPastS)
    {
        if (itHead->prev != nullptr)
        {
            if (itHead->prev != nullptr)
            {
                itHead = itHead->prev;
            }
            else
            {
                itHead = nullptr;
            }
        }
        else
        {
            isPastS = true;
        }
    }
    else
    {
        
        throw IteratorException();
    }
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
    if (itHead == nullptr || isPastS)
    {
        return true;
    }
    return false;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{
    if (itHead == nullptr || isPast)
    {
        return true;
    }
    return false;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
    constLL = &list;
    IteratorBase::itHead = constLL->head;
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
    if (IteratorBase::isPastStart() || IteratorBase::isPastEnd())
    {
        throw IteratorException();
    }
    return IteratorBase::itHead->value;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
    iterLL = &list;
    IteratorBase::itHead = iterLL->head;
    iterLL->head = IteratorBase::itHead;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
    
    return IteratorBase::itHead->value;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
    iterLL->insert(value);
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
    iterLL->addToEnd(value);
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
}

template <typename ValueType>
void DoublyLinkedList<ValueType>::printList()
{
    Node* node = head;
    while(node != nullptr)
    {
        node = node->next;
    }
}

#endif


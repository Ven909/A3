// FILE: sequence4.h 
// TEMPLATE CLASS PROVIDED:
//   sequence<Item> (part of the namespace CISP430_A3)
//   This is a container class for a sequence of items,
//   where each List may have a designated item called the current item).
//   The template parameter <value_type> is the data type of the items
//   in the List. It may be any of the C++ built-in types (int, char, etc.),
//   or a class with a default constructor, an assignment operator,
//   and a copy constructor.
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   sequence<Item>::value_type
//     Thisis the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   sequence<Item>::size_type
//     This is the data type of any variable that keeps track of
//     how many items are in a sequence.
//
// CONSTRUCTOR for the sequence<Item> class:
//   sequence( )
//     Postcondition: The sequence has been initialized as an empty sequence.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence<Item> class:
//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence<Item> class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.

#ifndef SEQUENCE4_H
#define SEQUENCE4_H
#include <cstdlib>  // Provides size_t
#include "node2.h"  // Provides node class

namespace CISP430_A3
{
    template <class Item>
    class sequence
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
       typedef Item value_type;
       typedef size_t size_type;
		
        // CONSTRUCTORS and DESTRUCTOR
        sequence( );
        sequence(const sequence& source);
	~sequence( );
        // MODIFICATION MEMBER FUNCTIONS
        void start( );
        void advance( );
        void insert(const value_type& entry);
        void attach(const value_type& entry);
        void operator =(const sequence& source);
	void remove_current( );
        // CONSTANT MEMBER FUNCTIONS
        size_type size( ) const { return many_nodes; }
        bool is_item( ) const { return (cursor != NULL); }
        value_type current( ) const;
    private:
	node<Item> *head_ptr;
	node<Item> *tail_ptr;
	node<Item> *cursor;
	node<Item> *precursor;
	size_type many_nodes;
    };
}

// The implementation of a template class must be included in its header file:
#include "sequence4.cpp"
#endif



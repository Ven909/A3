// File Name: sequence4.cpp<<<<<-------------------------------need to chane to ".template" extension-----------------
// Implemented from sequence4.h


//Author: Venkata G. Ande
//Student ID: W2030666
//Assignment number: A3
//Class: CISP 430
//PURPOSE: This program is an advanced container class that is very similar
// to A2. The key difference is that this program uses the templates
// functionality instead of typedef to improve efficiency and code-reusability


// Required includes
#include <cassert>      //Provides assert() functionality
//#include "sequence4.h"  //Includes the sequence4 header file<------------may not need this----------------
#include <iostream>     // Provides cin and cout
#include <algorithm>    //Provides copy function
using namespace std;
using namespace CISP430_A3;

// Ensure appropriate namespace
namespace CISP430_A3
{
    // CONSTRUCTOR
	// The constructor initializes the member variables 
	// in the sequence4 class. All the pointers are set 
    // to the default value, NULL. The many_nodes variable, 
    // which tracks teh number of nodes, is set to 0.
    template <class Item>
    sequence<Item> :: sequence ()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializing many_nodes (or our counter) to 0
        many_nodes = 0;
    } 
    // END CONSTRUCTOR FUNCTION

    // COPY CONSTRUCTOR
	// This Copy constructor is used to initialize the members 
	//	of a newly created sequence object by copying the members of 
	//	an already existing sequence object.//<<<<<<------------------------do this-------------------
    template <class Item>
    sequence<Item> :: sequence(const sequence& source)
    {
        sequence();     // call constructor to initialize all pointers to NULL 
        *this = source;    //set source object equal to this pointer to copy contents
    }
    // END COPY CONSTRUCTOR FUNCTION

    // DESTRUCTOR
	// This Destructor is a member function that is invoked 
	//	automatically whenever a sequence object is going 
	//	to be destroyed. This will be the last function 
	//	that is going to be called before a 
	//	sequence object is destroyed
    template <class Item>
    sequence<Item>:: ~sequence()
    {
        list_clear(head_ptr);   //return the data to the heap
        many_nodes = 0;         //set many_nodes to 0  

        //set all nodes to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;

        return;
    }
    // END DESTRUCTOR FUNCTION

    // MODIFICATION MEMBER FUNCTIONS

    // START function
	// The start function sets the index of a sequence object
	// to the first index or index 0. However, if the sequence
	// object is empty, then there is no current index	
    template <class Item>
    void sequence<Item> :: start()
    {
        cursor = head_ptr; //set the cursor to the head pointer(the first node in the sequence)
        precursor = NULL;   // set the precursor pointer to NULL since nothing is before the head pointer

        return;
    }
    // END START FUNCTION

    // ADVANCE function
	// The advance function increments the current sequence item
	//	by one, only if the next index contains a valid piece of data
    template <class Item>
    void sequence<Item> :: advance()
    {
        // Protect pre-condition. If false then terminate the program,
        // otherwise continue execution of sequence::advance().
        assert(is_item());

        precursor = cursor; // increment the precursor by setting the current cursor equal to precursor 
        cursor = cursor -> link();  // increment the current cursor to adjust accordingly

        return;
    }
    // END ADVANCE FUNCTION

    // INSERT function <---------------------------------rework the comments!!!!!!-------------------------------
	// The insert function inserts the data in the sequence at
	//	a specified location, before the current element.
    template <class Item>
    void sequence<Item> :: insert(const Item& entry)
    {
        //Testing precursor precondition
        // If sequence is empty or no current item...
        if ((precursor == NULL) || (!is_item()))
        {
            //Inserts a value at the head 
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;          // Set current to head
            precursor = NULL;           // Precursor is now NULL

            // If sequence is empty...
            if (many_nodes == 0)
                tail_ptr = head_ptr;    //Set tail pointer to head
            
            ++many_nodes;               //increment number of nodes accordingly
        }
        else //if the sequence is empty & there is a current item...
        {
            list_insert(precursor, entry);          //Insert a value before the current item. 
            cursor = precursor -> link();           //Set cursor to one node past "precursor" which is the new item
            ++many_nodes;                           //increment number of nodes accordingly
        }
        return;
    }
    // END INSERT FUNCTION

    // ATTACH function <---------------------------------rework the comments!!!!!!-------------------------------
	//	The attach function attaches a new data value at the end 
	//	of the sequence object or right after the current index element.
    template<class Item>
    void sequence<Item>::attach(const Item& entry)
    {
        // check if item is in sequnce
        if (is_item( ))
        {
            //Attach a value after the current item
            precursor = cursor;     // increment the precursor by setting the current cursor equal to precursor 
            list_insert(cursor, entry);     //insert new node
            cursor = cursor->link();      // increment the current cursor to adjust accordingly

            // Check if tail pointer needs to be updated
            if (cursor == tail_ptr)
                tail_ptr = tail_ptr -> link();  //increment tail accordingly <---------------------------may cause problems!!!------------------------
        }
        else    //else item is not in the sequence
        {
            //If the sequence is empty...
            if ((head_ptr == NULL) && (tail_ptr == NULL)) // check if first and lasy pointers are empty
            {
                list_head_insert (head_ptr, entry);     //insert the node at the front 
                cursor = head_ptr;                      //set the current cursor to the first node at the front 
                precursor = NULL;                       //set Precursor to NULL sicne nothing is before the head pointer
                tail_ptr = head_ptr;                    //set the last pointer at the front only for now  
            }
            else    //else if there is no current item 
            {
                //precursor = list_locate(head_ptr,list_length(head_ptr)); <------------------------------may need this------------------
                //else attach at end of list
                list_insert(precursor,entry);
                cursor = precursor->link();     //advance cursor accordingly to adjust
                tail_ptr = tail_ptr -> link();  //advance tail pointer accordingly to adjust
            }
        }
	    ++many_nodes;                          //increment number of nodes accordingly
    }
    // END ATTACH FUNCTION

    // OPERATOR= function <---------------------------------this might not work!!!!!!!!-------------------------------
	//	The OPERATOR= overolad the "=" operator to be able to set 
	//	one sequence object equal to another. All of the right-hand
	//	side's values are copied to the left-hand side
    template <class Item>
    void sequence<Item> :: operator =(const sequence& source)
    {
        //check for self-assignment
        // if so, return
        if (this == &source)
            return;
        list_copy(source.head_ptr, head_ptr, tail_ptr);     //use the list_copy to copy the list from front to back
        
        many_nodes = source.many_nodes;                     // copy many_nodes from the source object 
        start();                                            // call start() function to set all cursors to NULL
        
        node<Item> *tmp = source.head_ptr;                        // create temporary node and set it to user object's head node
        // while the temporary node is not at the source's current cursor node..
        while(tmp != source.cursor) 
        {                       
            advance();                                      // call advance() to keep the cursor incrementing 
            tmp = tmp->link();                              // advance the temporary node
        }

    }
    // END OPERATOR= FUNCTION

    // REMOVE_CURRENT function <---------------------------------rework the comments!!!!!!-------------------------------
	// The remove_current function removes the current item 
	// in the sequence. The next element is now the current item
    template <class Item>
    void sequence<Item> :: remove_current()
    {
        // Check the precondition. Make sure cursor is pointing to something before advancing
        assert(is_item());
        
        // If the current cursor node is at the front of the list...                                
        if(cursor == head_ptr) 
        {                            
            if(head_ptr == tail_ptr) // If there is only one node in the list
            {                      
                list_head_remove(head_ptr);                 // remove the head node 
                // set all of the other pointers to NUll
                head_ptr = NULL;                            
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
            else // else if list has more than 1 node
            {                                          
                list_head_remove(head_ptr);                 // remove the head node 
                cursor = head_ptr;                          // set the current cursor node to the new head pointer
                precursor = NULL;                           // set the precursor pointer to NULL since nothing is before the head pointer
            }
        }
        else if(cursor == tail_ptr) // else if the current cursor node is at the end of the list
        {                       
            list_remove(precursor);                         // delete the node after precursor
            tail_ptr = precursor;                           // set the tail pointer to the new precursor node by shifting left 
            cursor = NULL;                                  // set the cursor pointer to NULL since nothing is after the last node in the list
        }
        else //otherwise.... <-------------------------MAY NOT NEED THIS--------------------------------------
        {                                              
            list_remove(precursor);                         // delete the node after precursor
            cursor = cursor->link();                        // increment the current cursor node to adjust accordingly
        }
        many_nodes--;   //decrement the number of nodes accordingly
    }
    // END REMOVE_CURRENT FUNCTION

    // CURRENT function <---------------------------------rework the comments!!!!!!-------------------------------
	// The current function returns the current item in the sequence.
    template <class Item>
    typename sequence<Item> :: value_type sequence<Item> :: current() const
    {
        // Protect pre-condition. If false then terminate the program,
        assert (is_item());
        return cursor->data();  // return the data at the current cursor location
    }
    // END CURRENT FUNCTION
    
}
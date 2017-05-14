//  sequence3d.cpp
//  Data Structures Programming Assignment 2
//
//  Created by Michael Alexander on 2/24/17.
//  Copyright © 2017 Michael Alexander. All rights reserved.
//

#include "sequence3d.h"
#include <cassert>
using namespace DSProject02;

sequence::sequence(){
    
    head_ptr = NULL;
    tail_ptr = NULL;
    cursor = NULL;
    many_nodes = 0;
    
}
//Copy constructor
sequence::sequence(const sequence& source){

    list_copy(source.head_ptr, head_ptr, tail_ptr);
   
    node* tempNode = source.head_ptr; //create temp to save the original value
    
    cursor = head_ptr;
    
    while(tempNode != source.cursor){ // while cursors not at head, shift to next
    
        tempNode = tempNode->nlink();
        
       cursor = cursor->nlink();
 
    }
 
    many_nodes = source.many_nodes;

}

sequence::~sequence(){
    
    list_clear(head_ptr); // deletes allocated memory
   
    many_nodes = 0;
    
}

void sequence::start(){
    
    cursor = head_ptr; // set cursor to first node in the sequence
    
}

void sequence::advance(){
    
  cursor = cursor->nlink();
   

  cursor = cursor->plink();

}

void sequence::insert(const value_type& entry){
   
    if(head_ptr == NULL){ //if sequence is empty, insert at head
        
        list_head_insert(head_ptr, entry);
        cursor = head_ptr;
        tail_ptr = head_ptr;
        
    }
    //if cursors at head or equal to NULL
    else if(cursor == head_ptr || cursor == NULL){
        
        list_head_insert(head_ptr, entry);
        cursor = head_ptr;
    
    }
    else{ // else insert and shift to previous
        
        list_insert(cursor, entry); //inserts at cursors current
        cursor = cursor->plink();
        
    }
    ++many_nodes;
}

void sequence::append(const value_type& entry){
    
    if(head_ptr == NULL){ // empty sequence
    
        list_head_insert(head_ptr, entry);
        cursor = head_ptr;   //update pointers
        tail_ptr = head_ptr;
 
    }else if(cursor == NULL){ //if cursors not pointing to a value
       
        cursor = list_locate (head_ptr, list_length (head_ptr));
        list_append (cursor, entry);
        cursor = cursor -> nlink();
    
    } else { // else append and shift to next
    
        list_append(cursor, entry);
        cursor = cursor->nlink();
    
    }
    ++many_nodes;
    
}


void sequence::operator =(const sequence& source){
    if(this==&source)
        return;
    
    list_clear(head_ptr);

    list_copy(source.head_ptr, head_ptr, tail_ptr);
    
    node* tempNode = source.head_ptr; //copy to manipulate temp but keep value
    
    cursor = head_ptr;
    
    
    while(tempNode != source.cursor){ //keep shifting until head equals cursor
        
        tempNode = tempNode->nlink();
        
        cursor = cursor->nlink();
 }
 
    many_nodes = source.many_nodes;
   
}

void sequence::remove_current( ){
   
   //if cursors at head node,remove and shift to next
 if(cursor == head_ptr){
     
     cursor = head_ptr->nlink();
     
     list_head_remove(head_ptr);
     
     head_ptr=cursor;
    
 }
    //if cursors at tail node, shift back and remove tail
    else if(cursor == tail_ptr){
        
        cursor = cursor->plink();
        
        list_head_remove(tail_ptr);
        
        tail_ptr = cursor;
    
    }
    // assign cursor->next to tempNode, remove cursor and assign to tempNode
    else{
        
        node * tempNode = cursor->nlink();
        
        list_remove(cursor);
        
        cursor = tempNode;
   }
    
    --many_nodes;

}

sequence::value_type sequence::current( ) const{
    
    return cursor->data();
    
}

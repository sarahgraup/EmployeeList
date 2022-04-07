//
//  list.cpp
//  list
//
//  Created by Sarah Graup on 1/18/22.
//  Copyright © 2022 Sarah Graup. All rights reserved.
//

#include <iostream>
#include "list.hpp"
Node::Node(std::string s){
    data = s;
    previous = nullptr;
    next = nullptr;
}

List::List(){
    first = nullptr;
    last = nullptr;

}

void List::push_front(std::string data){
    Node* newNode = new Node(data); //creates new node with string data
    if(last==nullptr){ //the list is empty
        first=newNode; //newNode is set to first and last
        last=newNode;
    }
    else{
        newNode->next = first;//newNodes next pointer points to the first position in list
        first->previous = newNode; //the first's previous pointer now points to newNode
        first = newNode; //first position is now newNode
    }

  

}

void List::push_back(std::string data){
    Node* newNode = new Node(data); //creates a new node with the string data
    if(last==nullptr){ //the list is empty
        first = newNode; //the newNode is set to first and last pointers
        last = newNode;
    }
    else{
        newNode->previous = last; //the newNode's previous pointer points to the node designated as the last position
        last->next = newNode; //the last position's next pointer now points to newNode
        last = newNode; //now last is the newNode
    }


}
void List::reverse(){
      if(first == NULL)
         {
             return;
         }
         Node* current = first;
         Node* prev = NULL;
         while(current!=NULL)
         {
             //store previous
             prev = current->previous;
             //reverse currents next and previous pointers
             current->previous = current->next;
             current->next = prev;
             //move current pointer to next node
             current = current->previous;
         }
         last = first;
         first = prev->previous;

    
}
       
void List::swap(Iterator iter1, Iterator iter2){
    assert(iter1.position!=nullptr); //assert position is not past end
    assert(iter2.position!=nullptr); //assert position is not past end
    Node* current = iter1.position; //naming node iter1 is currently pointing to
    Node* beforeCurrent = current->previous; //naming node's previous and next nodes
    Node* afterCurrent = current->next;
    Node* current2 = iter2.position; //naming node iter2 is currently pointing to
    Node* beforeCurrent2 = current2->previous; //naming node's previous and next nodes
    Node* afterCurrent2 = current2->next;

    current->previous = beforeCurrent2; //current node's previous node is now current2's previous node
    current->next = afterCurrent2; //current's next node is now current2's next node
    if(afterCurrent2==nullptr){
        last = current->next; //if the node after current2 is after the end of the list then current is now last in list
    }
    else{
        afterCurrent2->previous = current; //else, aftercurrent2's previous now points to current
    }
    if(beforeCurrent2==nullptr){
        first = current;//if the node before current is null, then current is first in list
    }
    else{
        beforeCurrent2->next= current; //else, beforecurrent2 next pointer now points to current
    }

    current2->previous = beforeCurrent;
    current2->next = afterCurrent;
    if(afterCurrent==nullptr){
        last = current2;
    }
    else
    {
        afterCurrent->previous = current;
    }
    if(beforeCurrent==nullptr){
        first = current2;
    }
    else{
        beforeCurrent->next = current2;
    }
    iter1.position = current2;
    iter2.position = current;
    
    

    
}

Iterator List::erase(Iterator iter){
    assert(iter.position!=nullptr); //assert that the position is not past the end
    Node* toBeRemoved = iter.position; //define node to be removed at iterators position
    Node* before = toBeRemoved->previous; //define the node toBeRemoved previous position
    Node* after = toBeRemoved->next; //define the node toBeRemoved next position
    if(toBeRemoved==first){//check to make sure that the removed node is at the first position
        first = after; //need to make the first node the node after toBeRemoved
    }
    else{
        before->next = after;//stating that the node before toBeRemoved now points to toBeRemoved's after
    }
    if(toBeRemoved ==last){//if the toBeRemoved is the last node in list
        last = before; //the last node in list is now toBeRemoved's previous node
    }
    else{
        after->previous = before; //toBeRemoved's next node's previous now points to toBeRemoved's previous node
    }
    delete toBeRemoved;
    Iterator i;
    i.position = after; //iterator now points to the node after toBeRemoved
    i.container = this;
    return i; //returns iterator at new position

}

Iterator List:: begin(){
    Iterator iter;
    iter.position = first;
    iter.container = this;
    return iter;
}

Iterator List:: end(){
    Iterator iter;
    iter.position = nullptr;
    iter.container = this;
    return iter;

}

Iterator::Iterator(){
    position = nullptr;
    container = nullptr;

}
std::string Iterator:: get() const{
    assert(position!=nullptr);
    return position->data;


}

void Iterator:: next(){
    assert(position!=nullptr);
    position = position->next;

}
   
void Iterator:: previous(){
    assert(position!=container->first);
    if(position==nullptr){
        position = container->last;
    }
    else{
        position=position->previous;
    }

}
  
bool Iterator:: equals(Iterator b) const{
    return position == b.position;

}

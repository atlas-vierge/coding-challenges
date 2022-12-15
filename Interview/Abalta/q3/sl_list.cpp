/**  Author: Angela To
 *   Date: 11/29/14
 *   Description: Question 3 
 */

#include "sl_list.h"
#include <iostream> 
#include <cstddef> // For NULL

using namespace std; 

/** Node Constructor */
Node::Node(int d, Node* n) { 
	this->data = d; 
	this->next = n; 
} 

/** Node data modifier */
void Node::set_data(int d) { 
	this->data = d; 
} 

/** Node data accessor */
int Node::get_data() { 
	return this->data; 
}

/** Node next modifier */
void Node::set_next(Node* n) { 
	this->next = n; 
} 

/** Node next accessor */
Node* Node::get_next() { 
	return this->next; 
} 



/** List Constructor */
List::List() { 
	this->head = NULL; 
};


/** Add two lists together */
List List::add(List list_2) {
    int val = 0, carry = 0;
    List res;
        
    int l1_size = this->get_size();
    int l2_size = list_2.get_size();

    // Reversing the lists makes it easier to sum and carry 
    this->reverse_list();
    list_2.reverse_list();
        
    // Get pointers to each head of list    
    Node *l1 = head;
    Node *l2 = list_2.head;

    while (l1 != NULL || l2 != NULL) {
        if (l1 != NULL && l2 != NULL) {
            val = 0;                     
            val = l1->get_data() + l2->get_data() + carry;
            carry = val/10; 
            // If beginning a new summation 
	    if (res.head == NULL) {
                Node *new_node = new Node(val%10, NULL);
                res.head = new_node;
            } 
            else res.append_node_front(val%10); 
            // Increment the pointers
            l1 = l1->get_next();
            l2 = l2->get_next();
        } 
        // If l1 is longer
        else if (l1 != NULL && l2 == NULL) {
           val = 0;
           val = l1->get_data() + carry;
           carry = val/10; 
           res.append_node_front(val%10);
           l1 = l1->get_next();  
        }
        // If l2 is longer ...
        else if (l1 == NULL && l2 != NULL) {
           val = 0;
           val = l2->get_data() + carry;
           carry = val/10; 
           res.append_node_front(val%10);
           l2 = l2->get_next();  
        }
    }
    // Append the last carry over if > 0
    if (carry > 0) res.append_node_front(carry);
    return res; 
}


/** Reverse the list */
void List::reverse_list() {
	// If list is empty or consists of only one node
	if (this->head == NULL || this->get_size() < 2) return;

       	Node *tmp = head; 
	Node *second = tmp->get_next();

        // If only two nodes in the list
        if (this->get_size() == 2) {
            second->set_next(tmp);
            tmp->set_next(NULL);
            head = second;
            return;
        } 
 
        // If 2+ nodes in the list
        if (this->get_size() > 2) {
	    Node *third = second->get_next();

	    second->set_next(tmp); 
	    tmp->set_next(NULL);

	    if (third == NULL) return;

	    Node *curr_node = third;
    	    Node *prev_node = second;

	    while(curr_node != NULL) {
                Node *next_node = curr_node->get_next();
		curr_node->set_next(prev_node);
		prev_node = curr_node;
		curr_node = next_node;
	    }
	    head = prev_node;
    }
 }


/** Retrieves the size of the list */
int List::get_size(){
	Node *tmp = head; 
	if ( tmp == NULL ) {
        cout << "size: " << 0 << endl; 
		return 0; 
	}
    int size = 0;
    while (tmp != NULL) {
        size++;
        tmp = tmp->get_next();
    } 
    return size;
}


/** Print the contents of the list */ 
void List::print_list() { 
	Node *tmp = head; 
	// If list is empty
	if (tmp == NULL) return; 

	// Increment through the list and print each node's value
    while (tmp != NULL) {
        cout << tmp->get_data() << " ";
        tmp = tmp->get_next();
    }
    // cout << "NULL" << endl;
} 


/** Append node to the back of the list */ 
void List::append_node_back(int data) { 
	Node* new_node = new Node(); 
	new_node->set_data(data); 
	new_node->set_next(NULL); 

	Node *tmp = head; 

    // If list is empty
    if (tmp == NULL) {
    	head = new_node;
    	return;
    }

    // Iterate to the end of the list and append new node
	while ( tmp->get_next() != NULL ) tmp = tmp->get_next(); 
	tmp->set_next(new_node); 
} 


/** Append node to the front of the list */ 
void List::append_node_front(int data) { 
    Node* new_node = new Node(); 
    new_node->set_data(data);

    // If empty list
    if (head == NULL) { 
        new_node->set_next(NULL);
        return;
    }

    // Reset head to point to new node
	new_node->set_next(head);
	head = new_node;
}


/** Delete a node from the list */ 
void List::delete_node(int data) {
	Node *tmp = head; 
	// If list is empty
	if ( tmp == NULL ) return; 

//	// Last node of the list 
//	if ( tmp->get_next() == NULL ) { 
//		delete tmp; 
//	 	head = NULL; 
//	 	return;
//	} 

	Node *prev_node; 
	// Iterate through the list until we find the node containing the value
 	while (tmp != NULL) {
     	if (tmp->get_data() == data) break;
     	prev_node = tmp;
     	tmp = tmp->get_next();
 	}
 	prev_node->set_next(tmp->get_next());
 	delete tmp; 
} 

/** Clear the list */
void List::clear_list() {
    Node *tmp = head;
    Node *next_node;
    while (tmp != NULL) {
        next_node = tmp->get_next();
        delete tmp;
        tmp = next_node;
    }
    this->head = NULL;
}

// EOF


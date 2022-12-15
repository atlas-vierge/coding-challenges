/**  Author: Angela To
 *   Date: 11/29/14
 *   Description: Question 3 
 */

#include <cstddef> // For NULL

class Node { 
	private:
		int data; 
		Node* next; 

	public: 
		Node() {}; 
		Node(int d, Node* n); 
		void set_data(int d); 
		void set_next(Node* n); 
		int get_data(); 
		Node* get_next();

	friend class List;
}; 


class List { 
	private:
		Node *head;

	public: 
		List();
		void print_list(); 
		void append_node_front(int d); 
		void append_node_back(int d); 
		void delete_node(int d);
                void clear_list(); 
		void reverse_list();
		int get_size();
		List add(List l2);
}; 

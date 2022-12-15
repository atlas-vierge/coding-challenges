#include <iostream>
using namespace std;

class A { 
    A(); 
    ~A(); 
    void display() const { 
    	std::cout << "A\n";
    } 
    int* data; 
}; 

class B : public A { 
	B(); 
	~B(); 
	void display () const { 
		std::cout << "B\n"; 
	} 
}; 


void method (A* p) { 
	int num_list[5] = {0, 1, 2, 3, 4}; 
	p->data = num_list; 
} 

int main() { 
	A *ptr1 = new B; 
	A *ptr2 = new A; 
	method (ptr1); 
	ptr1->display(); 
	ptr1 = ptr2; 
	ptr1->display(); 
	return 0; 
}

/////#include <iostream> 
using namespace std; 

class A { 
public:	// default scope specifier is 'private' 
A() {/*NOP*/} 
~A() {/*NOP*/} 
// virtual modifier is missing!! 
virtual void display() const { 
std::cout << "A!\n"; 
} 
int* data; 
}; 

class B : public A { 
public: 
B() {/*NOP*/} 
~B() {/*NOP*/} 
void display () const { 
std::cout << "B!\n"; 
} 
}; 


// Auto variables (including an array?, I am not sure, though) 
// will be destroyed when exiting the function or the block. 
// You have to use a static modifier to avoid this. 
void method (A* p) { 
static int e[5] = {0, 1, 2, 3,4}; 
p->data = e; 
} 

int main() { 
A *ptr1 = new B; 
A *ptr2 = new A; 
method (ptr1); 
ptr1->display(); 
ptr1 = ptr2; 
ptr1->display(); 
return 0; 
}

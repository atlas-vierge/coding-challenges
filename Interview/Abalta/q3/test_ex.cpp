#include "sl_list.h"
#include <iostream>

using namespace std;

int main() { 
	 // New list 
	 List list; 
         List l5, l6, res3;

         l5.append_node_back(2);  
         l5.append_node_back(2);
//         l5.append_node_back(9);  
//         l5.append_node_back(0);
/*
         l5.append_node_back(2);  
         l5.append_node_back(2);
         l5.append_node_back(2);  
         l5.append_node_back(2);
         l5.append_node_back(2);  
         l5.append_node_back(2);
*/
/*        
         l6.append_node_back(2);  
         l6.append_node_back(2);
         l6.append_node_back(2);  
         l6.append_node_back(2);
         l6.append_node_back(2);  
         l6.append_node_back(2);
*/  
         l6.append_node_back(2);
         l6.append_node_back(2);  
//         l6.append_node_back(5);
//         l6.append_node_back(8);

         cout << endl << "L5: " << endl;
         l5.print_list();
         cout << endl;
         cout << endl << "L6: " << endl;
         l6.print_list();
         cout << endl; 

 	 cout << "L5 SIZE: " << l5.get_size() << endl;
	 cout << "L6 SIZE: " << l6.get_size() << endl;
/*
         cout << "L5 Reversed: " << endl;
         l5.reverse_list();
         l5.print_list();
         cout << endl;
         cout << "L6 Reversed: " << endl;
         l6.reverse_list();
         l6.print_list();
         cout << endl;
*/
 	 cout << "L5 SIZE: " << l5.get_size() << endl;
	 cout << "L6 SIZE: " << l6.get_size() << endl;


         res3 = l5.add(l6);
         cout << "RES: " << endl;
         res3.print_list();
	 cout << endl;
         cout << "CLEAR RES:" << endl;
         res3.clear_list();
         res3.print_list();
         cout << "RES SIZE: " << res3.get_size() << endl;         

} 

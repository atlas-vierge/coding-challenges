#include "sl_list.h"
#include <iostream>
#include <string>

using namespace std;

int main() { 
    cout << endl << endl;
    cout << "///////////////////////////////////////////////////" << endl;
    cout << "Linked Lists Adder: " << endl;
    cout << "Directions: Enter integers into each list by first " << endl;
    cout << "specifying the size of each list (the number of "    << endl;
    cout << "digits in each integer), then input each digit one " << endl;
    cout << "at a time (starting with the most significant digit)"<< endl;
    cout << "///////////////////////////////////////////////////" << endl;

    char c;
    int stop = 0; 
    List l1, l2, res;
    int l1_size;
    int l2_size;
    int n1;
    int n2;
    int i; 

    while (!stop) {
        cout << endl;
        cout << "Please enter size of first integer (# digits): ";
        cin >> l1_size;
 
        cout << "Please enter integers to be inserted into List 1:" << endl;
        for (i=0; i < l1_size; i++) {
            cout << (i+1) << ": ";
            cin >> n1;
            l1.append_node_back(n1);
        }

        cout << endl;
        cout << "Please enter size of second integer (# digits): ";
        cin >> l2_size;
 
        cout << "Please enter integers to be inserted into List 1:" << endl;
        for (int i=0; i < l2_size; i++) {
            cout << (i+1) << ": ";
            cin >> n2;
            l2.append_node_back(n2);
        }

        cout << endl;
        cout << "List 1: ";
        l1.print_list();
        cout << endl;
    
        cout << "List 2: ";
        l2.print_list();
        cout << endl;
 
        res = l1.add(l2);
        cout << "Summed lists: ";
        res.print_list();
        cout  << endl;   
        cout << endl << endl;

        l1.clear_list();
        l2.clear_list(); 
 
        cout << "Do you want to coninue adding numbers? (y/n): ";
        cin >> c;
        if (c == 'n') stop = 1;
    }
} 

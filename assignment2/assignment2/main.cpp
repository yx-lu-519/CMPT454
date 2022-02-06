#include "extensiblehashtable.h"
#include <cstdlib>
#include<iostream>

using namespace std;

int main(){
    ExtensibleHashTable new_table;

    new_table.insert(0);
    new_table.print();
    new_table.insert(0);
    new_table.print();
    new_table.insert(4);
    new_table.print();
    new_table.insert(2);
    new_table.print();
    new_table.insert(4);
    new_table.print();
    new_table.insert(3);
    new_table.print();
    new_table.insert(1);
    new_table.print();
    new_table.insert(7);
    new_table.print();
    new_table.insert(7);
    new_table.print();
    new_table.insert(7);
    new_table.print();
    new_table.insert(32);
    new_table.print();
    new_table.insert(7);
    new_table.print();
    new_table.insert(7);
    new_table.print();
    cout << endl;
    ExtensibleHashTable new_table2;
    new_table2 = new_table;
    cout << "This is assign operator" << endl;
    new_table2.print();
    cout << endl;
    ExtensibleHashTable new_table3(new_table);
    cout << "This is copy" << endl;
    new_table3.print();
    system("pause");
	return 0;
}
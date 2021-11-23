#include <iostream>
#include "Search_tree.h"
#include <string>

using namespace std;

void print(string func, int actual, int expected){
	string result;
	expected == actual ? result = "Okay" : result = "Failed";

	cout << func << "\t" << to_string(actual) << "\t" << to_string(expected) << "\t" << result << endl;
}
void print(string func, Search_tree<int>::Iterator actual, Search_tree<int>::Iterator expected){
	string result;
	expected == actual ? result = "Okay" : result = "Failed";

	cout << func << "\t\t\t" << result << endl;
}

int main() {
	Search_tree<int> tree;

	cout << "format: tested function | actual value | expected value | pass/fail" << endl;
    for (int i = 1; i <= 20; i++){
		tree.insert(i);
        print("height", tree.height(), i);
	}
    print("height", tree.height(), 4);
	for (int i = 21; i <= 30; i++){
		tree.insert(i);
        print("height", tree.height(), i);
	}
	print("height", tree.height(), 4);
	print("insert", tree.insert(31), 1);
	print("height", tree.height(), 4);
	print("insert", tree.insert(32), 1);
	print("height", tree.height(), 5);
	print("insert", tree.insert(33), 1);
	print("height", tree.height(), 5);
	for (int i = 31; i <= 44; i++){
		tree.insert(i);
        print("height", tree.height(), i);
	}
	print("height", tree.height(), 5);
	for (int i = 1; i <= 15; i++){
		tree.erase(i);
        print("eheight", tree.height(), i);
	}
	print("height", tree.height(), 5);
	tree.erase(16);
	print("height", tree.height(), 4);

	for (int i = 0; i <= 45; i++){
		tree.erase(i);
        print("eheight", tree.height(), i);
	}
return 0;
}
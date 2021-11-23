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

	// general
	print("empty", tree.empty(), 1);
	print("size", tree.size(), 0);
	print("height", tree.height(), -1);
    print("find", tree.find(1), tree.end());
    print("find", tree.find(0), tree.end());
	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(10), 0);
	print("front", tree.front(), 10);
	print("back", tree.back(), 10); 
	print("empty", tree.empty(), 0);
	print("size", tree.size(), 1);
	print("height", tree.height(), 0);
    print("find", *tree.find(10), 10);
	print("insert", tree.insert(9), 1);
	print("insert", tree.insert(9), 0);
	print("size", tree.size(), 2);
	print("height", tree.height(), 1);
	print("front", tree.front(), 9);
	print("back", tree.back(), 10);
	print("insert", tree.insert(8), 1);
	print("insert", tree.insert(8), 0);
	print("size", tree.size(), 3);
	print("height", tree.height(), 1);
	print("front", tree.front(), 8);
	print("back", tree.back(), 10);
    print("find", *tree.find(8), 8);
	tree.clear();
	print("empty", tree.empty(), 1);
	print("size", tree.size(), 0);
	print("height", tree.height(), -1);
    print("find", tree.find(10), tree.end());
    print("find", tree.find(0), tree.end());
    print("find", tree.find(8), tree.end());
	print("insert", tree.insert(8), 1);
	print("insert", tree.insert(9), 1);
	print("insert", tree.insert(10), 1);
	print("height", tree.height(), 1);
	print("front", tree.front(), 8);
	print("back", tree.back(), 10);

	print("insert", tree.insert(1), 1);
	print("insert", tree.insert(2), 1);
	print("insert", tree.insert(11), 1);
	print("insert", tree.insert(12), 1);
	print("size", tree.size(), 7);
	print("height", tree.height(), 2);
	print("front", tree.front(), 1);
	print("back", tree.back(), 12);
	print("insert", tree.insert(0), 1);
	print("size", tree.size(), 8);
	print("height", tree.height(), 3);
	print("front", tree.front(), 0);
	print("back", tree.back(), 12);
    print("find", *tree.find(12), 12);
    print("find", *tree.find(11), 11);
    print("find", *tree.find(1), 1);
    print("find", *tree.find(0), 0);

	tree.clear();
	print("empty", tree.empty(), 1);
	print("size", tree.size(), 0);
	print("height", tree.height(), -1);

	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(100), 1);
	print("insert", tree.insert(50), 1);
	print("front", tree.front(), 10);
	print("back", tree.back(), 100);
	print("empty", tree.empty(), 0);
	print("size", tree.size(), 3);
	print("height", tree.height(), 1);
	tree.clear();
	print("empty", tree.empty(), 1);
	print("size", tree.size(), 0);
	print("height", tree.height(), -1);

	print("insert", tree.insert(100), 1);
	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(50), 1);
	print("front", tree.front(), 10);
	print("back", tree.back(), 100);
	print("empty", tree.empty(), 0);
	print("size", tree.size(), 3);
	print("height", tree.height(), 1);
    print("find", *tree.find(100), 100);
    print("find", *tree.find(50), 50);

	// test height
	tree.clear();
	for (int i = 1; i <= 20; i++){
		tree.insert(i);
	}
	print("height", tree.height(), 4);
	for (int i = 21; i <= 30; i++){
		tree.insert(i);
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
	}
	print("height", tree.height(), 5);
	for (int i = 1; i <= 15; i++){
		tree.erase(i);
	}
	print("height", tree.height(), 5);
	tree.erase(16);
	print("height", tree.height(), 4);

	for (int i = 0; i <= 45; i++){
		tree.erase(i);
	}
	print("height", tree.height(), -1);
	print("size", tree.size(), 0);
	print("empty", tree.empty(), 1);

	print("insert", tree.insert(5), 1);
	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(15), 1);
	print("insert", tree.insert(20), 1);
	print("insert", tree.insert(25), 1);
	print("insert", tree.insert(30), 1);
	print("insert", tree.insert(35), 1);
	print("front", tree.front(), 5);
	print("back", tree.back(), 35);
	print("height", tree.height(), 2);

	tree.clear();
	print("height", tree.height(), -1);
	print("size", tree.size(), 0);
	print("empty", tree.empty(), 1);

	print("insert", tree.insert(5), 1);
	print("insert", tree.insert(20), 1);
	print("insert", tree.insert(15), 1);
	print("insert", tree.insert(30), 1);
	print("insert", tree.insert(35), 1);
	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(25), 1);
	print("front", tree.front(), 5);
	print("back", tree.back(), 35);
	print("height", tree.height(), 3);
	print("insert", tree.insert(28), 1);
	print("height", tree.height(), 3);
	print("insert", tree.insert(32), 1);
	print("insert", tree.insert(6), 1);
	print("insert", tree.insert(12), 1);
	print("height", tree.height(), 3);
	tree.clear();

	// test imbalances
	// left left
	for (int i = 10; i > 0; i--){
		tree.insert(i);
	}
	print("height", tree.height(), 3);
	print("size", tree.size(), 10);
	print("empty", tree.empty(), 0);
	print("front", tree.front(), 1);
	print("back", tree.back(), 10);

	tree.clear();
	print("height", tree.height(), -1);
	print("size", tree.size(), 0);
	print("empty", tree.empty(), 1);
	
	// right right
	for (int i = 0; i < 10; i++){
		tree.insert(i);
	}
	print("height", tree.height(), 3);
	print("size", tree.size(), 10);
	print("empty", tree.empty(), 0);
	print("front", tree.front(), 0);
	print("back", tree.back(), 9);

	tree.clear();
	print("height", tree.height(), -1);
	print("size", tree.size(), 0);
	print("empty", tree.empty(), 1);

	// left left
	print("insert", tree.insert(40), 1);
	print("insert", tree.insert(30), 1);
	print("insert", tree.insert(20), 1);
	print("height", tree.height(), 1);
	print("insert", tree.insert(10), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(5), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(4), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(3), 1);
	print("height", tree.height(), 2);

	tree.clear();

	print("insert", tree.insert(30), 1);
	print("height", tree.height(), 0);
	print("insert", tree.insert(10), 1);
	print("height", tree.height(), 1);
	print("insert", tree.insert(5), 1);
	print("height", tree.height(), 1);
	print("insert", tree.insert(1), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(20), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(15), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(14), 1);
	print("height", tree.height(), 3);
	print("insert", tree.insert(13), 1);
	print("height", tree.height(), 3);

	tree.clear();

	// left right
	print("insert", tree.insert(50), 1);
	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(40), 1);
	print("height", tree.height(), 1);
	print("insert", tree.insert(5), 1);
	print("insert", tree.insert(35), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(20), 1);
	print("height", tree.height(), 2);

	// right left
	print("insert", tree.insert(45), 1);
	print("height", tree.height(), 2);

	// left right
	print("insert", tree.insert(15), 1);
	print("insert", tree.insert(25), 1);
	print("height", tree.height(), 3);
	print("insert", tree.insert(28), 1);
	print("height", tree.height(), 3);

	print("insert", tree.insert(1), 1);
	print("insert", tree.insert(2), 1);
	print("height", tree.height(), 3);

	// right left
	print("insert", tree.insert(26), 1);
	print("height", tree.height(), 3);

	// left right
	print("insert", tree.insert(8), 1);
	print("height", tree.height(), 3);
    print("find", *tree.find(8), 8);
    print("find", *tree.find(10), 10);
    print("find", *tree.find(2), 2);

	tree.clear();

	// right left
	print("insert", tree.insert(10), 1);
	print("insert", tree.insert(100), 1);
	print("insert", tree.insert(50), 1);
	print("height", tree.height(), 1);
	print("insert", tree.insert(200), 1);
	print("insert", tree.insert(150), 1);
	print("height", tree.height(), 2);
	print("insert", tree.insert(125), 1);
	print("height", tree.height(), 2);

	// right right
	print("insert", tree.insert(120), 1);
	print("insert", tree.insert(130), 1);
	print("insert", tree.insert(175), 1);
	print("insert", tree.insert(300), 1);
	print("height", tree.height(), 3);
	print("insert", tree.insert(160), 1);
	print("height", tree.height(), 3);
    print("front", tree.front(), 10);
    print("back", tree.back(), 300);
    print("find", *tree.find(125), 125);
    print("find", *tree.find(175), 175);
    print("find", *tree.find(130), 130);
    print("find", *tree.find(150), 150);

    for (int i = 0; i < 400; i++){
        tree.erase(i);
    }
	print("height", tree.height(), -1);
	print("size", tree.size(), 0);
	print("empty", tree.empty(), 1);
    print("find", tree.find(0), tree.end());
    print("find", tree.find(100), tree.end());
    print("find", tree.find(300), tree.end());
    print("find", tree.find(120), tree.end());

	// test interators
    auto itr = tree.end();
    print("++itr", ++itr, tree.end());
    print("++itr", ++itr, tree.end());
    itr = tree.rend();
    print("--itr", --itr, tree.rend());
    print("--itr", --itr, tree.rend());
    print("==", tree.end() == tree.rend(), 0);
    print("==", tree.end() == tree.end(), 1);
    print("==", tree.begin() == ++tree.rend(), 1);
    print("==", tree.rbegin() == --tree.end(), 1);
    print("==", tree.find(0) == tree.end(), 1);
    print("!=", tree.begin() != tree.rend(), 1);
    print("!=", tree.rbegin() != tree.end(), 1);
    print("!=", tree.find(0) != tree.end(), 0);
    print("!=", tree.end() != tree.rend(), 1);

    cout << "should all be 1: ";
    for (int i = 0; i < 100; i++){
        cout << tree.insert(i);
    }
    cout << endl << endl;
    cout << "should all be 0: ";
    for (int i = 0; i < 100; i++){
        cout << tree.insert(i);
    } 
    cout << endl << endl;;

    cout << "should print 0 to 99: "; 
    for (auto itr = tree.begin(); itr != tree.end(); ++itr){
        cout << *itr << " ";
    }
    cout << endl << endl;

    cout << "should also print 0 to 99: "; 
    for (auto itr = tree.find(0); itr != tree.end(); ++itr){
        cout << *itr << " ";
    }
    cout << endl << endl;

    cout << "should also also print 0 to 99: "; 
    for (int i = 0; i < 100; i++){
        cout << *tree.find(i) << " ";
    }
    cout << endl << endl;

    cout << "should print 99 to 0: "; 
    for (auto itr = tree.find(99); itr != tree.rend(); --itr){
        cout << *itr << " ";
    }
    cout << endl << endl;;

    cout << "should also print 99 to 0: "; 
    for (auto itr = tree.rbegin(); itr != tree.rend(); --itr){
        cout << *itr << " ";
    }
    cout << endl << endl;;

    cout << "should also also print 99 to 0: "; 
    for (int i = 99; i >= 0; i--){
        cout << *tree.find(i) << " ";
    }
    cout << endl << endl;;

    cout << "should print 0 to 49: ";
    for (auto itr = tree.find(0); itr != tree.find(50); ++itr){
        cout << *itr << " ";
    }
    cout << endl << endl;;

    cout << "should print 99 to 50: ";
    for (auto itr = tree.find(99); itr != tree.find(49); --itr){
        cout << *itr << " ";
    }
    cout << endl << endl;

    print("==", tree.end() == tree.end(), 1);
    print("==", tree.find(99) == --tree.end(), 1);
    print("==", tree.find(0) == ++tree.rend(), 1);
    print("==", tree.begin() == ++tree.rend(), 1);
    print("==", tree.rbegin() == --tree.end(), 1);
    print("==", tree.begin() == tree.find(0), 1);
    print("==", tree.rbegin() == tree.find(99), 1);
    
    print("!=", tree.end() != tree.end(), 0);
    print("!=", tree.find(0) != ++tree.rend(), 0);
    print("!=", tree.find(99) != --tree.end(), 0);
    print("!=", tree.begin() != ++tree.rend(), 0);
    print("!=", tree.rbegin() != --tree.end(), 0);
    print("!=", tree.begin() != tree.find(0), 0);
    print("!=", tree.rbegin() != tree.find(99), 0);

    print("!=", tree.end() != tree.rend(), 1);
    print("!=", tree.end() != tree.find(99), 1);
    print("!=", tree.rend() != tree.find(0), 1);

    print("==", tree.end() == tree.rend(), 0);
    print("==", tree.end() == tree.find(99), 0);
    print("==", tree.rend() == tree.find(0), 0);


	return 0;
}

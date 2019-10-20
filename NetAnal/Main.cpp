// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;


int main() {

	string name;
	int beg;
	int end;
	vector<Node> nodes;

	int i = 0;
	while (i++ < 3) {
		cout << "\nEnter da node man: ";
		cin >> name >> beg >> end;
		nodes.push_back(Node(name, beg, end));
	}

	int j = 0;
	while (j < nodes.size()) {
		cout << nodes.at(j++).name << endl;
	}

	return 0;
}
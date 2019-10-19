#include <iostream>
#include <sstream>
#include "Node.h"
using namespace std;

Node::Node(string aName, int aEnd, int aBeg) {
	name = aName;
	end = aEnd;
	beg = aBeg;
	
	cout << "Node " << name << " created." << endl;
	cout << "Add adjacent nodes. Enter done when done." << endl;
	
	string input;
	string neighbour;
	int distance;
	while (true) {
		//TODO temporary way of constructing network; does not handle input
		cout << "Name: ";
		cin >> neighbour;
		if (neighbour == "done") break;
		cout << "Distance from " << name << ": ";
		cin >> distance;
		
		neighbours.emplace_back(neighbour, distance);
	}
}


#include <iostream>
#include "Node.h"
using namespace std;

Node::Node(string aName, int aEnd, int aBeg) {
	name = aName;
	end = aEnd;
	beg = aBeg;
	cout << "Node " << name << " created." << endl;
}


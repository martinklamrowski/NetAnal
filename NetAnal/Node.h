#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

#pragma once
class Node {
	public:
		string name;								// name of the node: letter/number...
		int end;									// is this an end node
		int beg;									// is this a beginning node
		vector<tuple<string, int>> neighbours;		// list of tuples of all adjacent nodes (name, distance)

		Node(string aName, int aEnd, int aBeg);
};


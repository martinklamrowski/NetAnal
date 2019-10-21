#include <iostream>
#include <vector>
using namespace std;

#pragma once
class Node {
	public:
		string name;								// name of the node: letter/number...
		int end;									// is this an end node
		int beg;									// is this a beginning node
		vector<pair<string, int>> neighbours;		// list of pairs of all adjacent nodes (name, distance)

		Node(string aName, int aEnd, int aBeg);
};
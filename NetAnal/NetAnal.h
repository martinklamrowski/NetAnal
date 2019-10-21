#include <iostream>
#include <unordered_map> 
#include "Node.h"
using namespace std;

#pragma once
class NetAnal {
public:
	unordered_map<string, Node> nodes;			// all the nodes in this network analysis
	string beg;									// the start (in) node for this network analysis
	string end;									// the end (out) node for this network analysis

	NetAnal(unordered_map<string, Node> aNodes, string aBeg, string aEnd);
	int shortestpath();
};
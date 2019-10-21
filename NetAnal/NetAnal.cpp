// NetAnal.cpp : This file contains the NetAnal class.
//
#include <iostream>
#include <vector>
#include <unordered_map> 
#include "Node.h"
#include "NetAnal.h"
using namespace std;

NetAnal::NetAnal(unordered_map<string, Node> aNodes, string aBeg, string aEnd) {
	nodes = aNodes;
	beg = aBeg;
	end = aEnd;
}

/*
Finds the length of the shortest path between the start and end node.
*/
int NetAnal::shortestpath() {
	return 1;
}

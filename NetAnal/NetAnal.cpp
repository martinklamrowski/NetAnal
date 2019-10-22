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
	
	unordered_map<string, Node>::const_iterator current_node = nodes.find(beg);	// iterator to the current node pair
	unordered_map<string, Node>::const_iterator end_node = nodes.find(end);		// iterator to the end node 

	unordered_map<string, int> solved_nodes = { {beg, 0} };						// {node name, candidate distance from start}
	unordered_map<string, int> arc_set;											// {arc name, arc length}
	
	vector<pair<string, int>> neighbours;										// <name of neighbour, distance from current node>
	pair<string, int> closest_neighbour;										// <current closest neighbour, distance from current node>

	int candidate_distance;
	int reached_target = 0;
	int solved_node = 0;

	while (!reached_target) {

		for (unordered_map<string, int>::const_iterator s = solved_nodes.begin(); s != solved_nodes.end(); s++) {
			current_node = nodes.find(s->first);
			neighbours = (current_node->second).neighbours;

			for (vector<pair<string, int>>::const_iterator n = neighbours.begin(); n != neighbours.end(); n++) {
				
				// check if neighbour is already solved
				if (!(solved_nodes.count(n->first))) {
					// is not a solved node so compute candidate distance
					candidate_distance = n->second + s->second;
					if (candidate_distance < closest_neighbour.second || closest_neighbour.second == 0) {
						closest_neighbour = pair<string, int> (n->first, candidate_distance);

						if (n->first == end_node->first) {
							reached_target = 1;
						}
					}
				}
			}
		}
		solved_nodes.emplace(closest_neighbour);
		closest_neighbour = pair<string, int>("", 0);
		
		cout << "SOLVED NODES:" << endl;
		for (unordered_map<string, int>::const_iterator test = solved_nodes.begin(); test != solved_nodes.end(); test++) {
			cout << test->first << test->second << endl;
		}
	}

	
	
	
	
	return 1;
}

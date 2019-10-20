// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Node.h"
using namespace std;

vector<Node> parsefile(string textfile) {
	string name, neighbour_node;
	int beg, end, num_neighbours, distance;
	vector<Node> nodes;

	ifstream data(textfile);

	while (true) {
		data >> name >> beg >> end >> num_neighbours;
		
		// end of file reached?
		if (name == "END") break;

		// create the node
		Node new_node = Node(name, beg, end);
		for (int i = 0; i < num_neighbours; i++) {
			data >> neighbour_node >> distance;

			// add neighbouring node as tuple to neighbours vector			
			new_node.neighbours.emplace_back(neighbour_node, distance);
		}
		// finally, update the nodes vector
		nodes.push_back(new_node);
	}
	return nodes;
}



int main() {

	string name;
	int beg;
	int end;
	vector<Node> nodes;

	/*Parse network data from file. Format is:
		name beg end num_neighbours
		neighbour_name distance
		.
		.
		.
		name beg end num_neighbours
		.
		.
		.
	*/
	nodes = parsefile("sample_network.txt");

	cout << nodes.at(0).name << endl;
	cout << nodes.at(1).name << endl;
	cout << nodes.at(2).name << endl;
	cout << nodes.at(3).name << endl;
	cout << nodes.at(4).name << endl;

	return 0;
}
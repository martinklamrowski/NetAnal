#pragma once

#include "unordered_set"

class Node
{
public:
	Node(char name, int posx, int posy);
	~Node();

	char name;
	int posx;
	int posy;
	bool selected;
	std::unordered_set<char> neighbours;

	bool addNeighbour(char neighbour);
};


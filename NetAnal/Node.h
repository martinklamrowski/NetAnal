#pragma once

#include "unordered_map"

class Node
{
public:
	Node(char name, int posx, int posy, int beg, int end);
	~Node();

	char name;
	int posx;
	int posy;
	int beg;
	int end;
	bool selected;
	std::unordered_map<char, double> neighbours;

	bool addNeighbour(char neighbour, double dist);
};


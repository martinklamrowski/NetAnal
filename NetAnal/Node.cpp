#include "Node.h"


Node::Node(char name, int posx, int posy, int beg, int end)
{
	this->name = name;
	this->posx = posx;
	this->posy = posy;
	this->beg = beg;
	this->end = end;
	selected = false;
}
Node::~Node()
{

}

bool Node::addNeighbour(char neighbour, double dist)
{
	if (neighbours.count(neighbour))
	{
		return false; // will return false if add failed
	}
	else
	{
		neighbours.emplace(neighbour, dist);
		return true;
	}
}



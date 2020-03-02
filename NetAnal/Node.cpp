#include "Node.h"


Node::Node(char name, int posx, int posy)
{
	this->name = name;
	this->posx = posx;
	this->posy = posy;
	selected = false;
}
Node::~Node()
{

}

bool Node::addNeighbour(char neighbour)
{
	if (neighbours.count(neighbour))
	{
		return false; // will return false if add failed
	}
	else
	{
		neighbours.emplace(neighbour);
		return true;
	}
}



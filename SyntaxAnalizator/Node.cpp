#include "Node.h"

void Node::print(ofstream& out, int level)
{
	for (int i = 0; i < level; ++i)
	{
		out << "   ";
	}
	out << data << '\n';
	for (int i = 0; i < children.size(); ++i)
	{
		children[i].print(out, level + 1);
	}
}
#ifndef _EDGE
#define _EDGE
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#include "point.h"

//An edge connects two nodes
//The nodes are referred to by their index number
class Edge
{
	private:
		int index;
		int nodeA, nodeB;
		string relation;

	public:
		Edge();
		Edge(int edgeIndex, string rel, int n1, int n2);

		inline string getRelation() {return relation;}
		inline int getNodeA() {return nodeA;}
		inline int getNodeB() {return nodeB;}
		inline int getIndex() {return index;}
		inline void setIndex(int ind){index = ind;}
};
//Basic Edge Constructor
Edge::Edge()
{
	index = -1;
	nodeA = -1;
	nodeB = -1;
	relation = "";
}
//Edge Constructor for dynamic edge creation
Edge::Edge(int edgeIndex, string rel, int n1, int n2)
{
	index = edgeIndex;
	nodeA = n1;
	nodeB = n2;
	relation = rel;
}

#endif

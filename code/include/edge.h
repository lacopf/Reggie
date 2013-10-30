#ifndef _EDGE
#define _EDGE

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#include "node.h"
#include "point.h"

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

		void draw();
};

Edge::Edge()
{
	index = -1;
	nodeA = -1;
	nodeB = -1;
	relation = "";
}
Edge::Edge(int edgeIndex, string rel, int n1, int n2)
{
	index = edgeIndex;
	nodeA = n1;
	nodeB = n2;
	relation = rel;
}
void Edge::draw()
{
	glLineWidth(2.5); 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(nodeA.getPoint().getX(), nodeA.getPoint().getY());
	glVertex2f(nodeB.getPoint().getX(), nodeB.getPoint().getY());
	glEnd();
}

#endif

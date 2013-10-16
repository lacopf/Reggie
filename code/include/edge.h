#ifndef _edge_h_
#define _edge_h_

#include "node.h"

class Edge{
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

#endif

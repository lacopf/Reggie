#ifndef _edge_h_
#define _edge_h_

#include "node.h"

class Edge{
	private:
	  int index;
	  Node* nodeA;
	  Node* nodeB;
	  string relation;
	  
	public:
	  Edge();
	  Edge(Node* n1, Node* n2, string rel, int ind);
	  
	  inline string getRelation() {return relation;}
  
};

Edge::Edge()
{
	index = -1;
	nodeA = NULL;
	nodeB = NULL;
	relation = "";
}
Edge::Edge(Node* n1, Node* n2, string rel, int ind)
{
	index = ind;
	nodeA = n1;
	nodeB = n2;
	relation = rel;
}

#endif

#ifndef _edge_h_
#define _edge_h_
#include "node.h"

class Edge{
	private:
	  Node* nodeA;
	  Node* nodeB;
	  string relation;
	  
	public:
	  Edge();
	  Edge(Node* n1, Node* n2, string rel);
	  
	  string inline get_relation() {return relation;}
  
};

Edge::Edge()
{
	nodeA = NULL;
	nodeB = NULL;
	relation = "";
}
Edge::Edge(Node* n1, Node* n2, string rel)
{
	nodeA = n1;
	nodeB = n2;
	relation = rel;
}



#endif

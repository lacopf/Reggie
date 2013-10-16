#ifndef _edge_h_
#define _edge_h_
#include "node.h"

class Edge{
	private:
	  Node* node1;
	  Node* node2;
	  string relation;
	  
	public:
	  Edge();
	  Edge(Node* n1, Node* n2, string relation);
	  
	  string get_relation() {return relation;}
  
};

Edge::Edge()
{
	node1 = NULL;
	node2 = NULL;
	relation = "";
}




#endif

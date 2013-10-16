#ifndef _GRAPH
#define _GRAPH

#include "node.h"
#include "edge.h"
#include <vector>

using namespace std;

class Graph
{
	public:
		vector<Node> getNodes(){ return nodes; }
		vector<Edge> getEdges(){ return edges; }

		void addNode(Node node){ nodes.push_back(node); }
		void addEdge(Edge edge){ edges.push_back(edge); }

		
	private:
		vector<Node> nodes;
		vector<Edge> edges;
};

#endif

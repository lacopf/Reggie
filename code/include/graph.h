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

	inline void addNode(Node node){ nodes.push_back(node); }
        void addNode(string info, vector<string> tags, int index);
	void addEdge(int n1, int n2, string rel);
        void printNodes();
        void removeEdge(int index);
        void removeNode(int index);
        void printGraph();

		
	private:
		vector<Node> nodes;
		vector<Edge> edges;
};


void Graph::addNode(string info, vector<string> tags, int index){
	Node n1(info, index, tags, NULL);
	nodes.push_back(n1);
    
	//parent edge
	if(index != -1)
	{
		addEdge(index, nodes.size() - 1, "tree_edge");
	}
}

void Graph::addEdge(int n1, int n2, string rel){
	Edge e(edges.size(), rel, n1, n2);
	edges.push_back(e);
	Edge* p = &(edges.back());
	nodes[n2].addInEdge(p);
	nodes[n1].addOutEdge(p);    
}

void Graph::printNodes(){
	for(int i=0; i<nodes.size(); i++){
		cout << i << ": " << nodes[i].getInformation() << endl;
	}
}

void Graph::removeEdge(int index){
	//removes edge from source node
	Node& n1 = nodes[(edges[index]).getNodeA()];
	n1.removeOutEdge(&edges[index]);

	//removes edge from target node    
	Node& n2 = nodes[(edges[index]).getNodeB()];
	n2.removeInEdge(&edges[index]);
    
	//moves back of edges to index position and pops back
	edges[index] = edges.back();
	edges[index].setIndex(index);
	edges.pop_back();
}

void Graph::removeNode(int index){
	Node& n = nodes[index];

	//removes all ingoing edges from graph
	const vector<Edge*>& inedges = n.getInEdges();
	for(int i=0; i<inedges.size(); i++){
		removeEdge(inedges[i] -> getIndex());
	}

	//removes all outgoing edges from graph
	const vector<Edge*>& outedges = n.getOutEdges();
	for(int i=0; i<outedges.size(); i++){
		removeEdge(outedges[i] -> getIndex());
	}

	//removes node from nodes vector    
	nodes[index] = nodes.back();
	nodes[index].setIndex(index);
	nodes.pop_back();    
}


//prints all in and out edges for each node in the graph
void Graph::printGraph(){
	for(int i=0; i<nodes.size(); i++){
		cout << i << ": " << endl;
		cout << "    in edges: ";
		const vector<Edge*>& in_edges = nodes[i].getInEdges();
		for(int j=0; j<in_edges.size(); j++){
			cout << (in_edges[j]->getNodeA)()<< " ";  
		}
		cout << endl;
		cout << "    out edges: ";
		const vector<Edge*>& out_edges = nodes[i].getOutEdges();
		for(int j=0; j<out_edges.size(); j++){
			cout << (out_edges[j]->getNodeB)()<< " ";  
		}
		cout << endl;
	}
}
#endif

#ifndef _GRAPH
#define _GRAPH

#include <stdio.h>
#include <fstream>
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
		void save(string filename);
		void draw();
                
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
        if(index != 0){
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
        else{
                cout << "You cannot delete the root node" << endl;
        }
}


//prints all in and out edges for each node in the graph
void Graph::printGraph(){
        for(int i=0; i<nodes.size(); i++){
                cout << i << ": " << endl;
                cout << " in edges: ";
                const vector<Edge*>& in_edges = nodes[i].getInEdges();
                for(int j=0; j<in_edges.size(); j++){
                        cout << (in_edges[j]->getNodeA)()<< " ";
                }
                cout << endl;
                cout << " out edges: ";
                const vector<Edge*>& out_edges = nodes[i].getOutEdges();
                for(int j=0; j<out_edges.size(); j++){
                        cout << (out_edges[j]->getNodeB)()<< " ";
                }
                cout << endl;
        }
}
//saves the graph to the file
void Graph::save(string filename)
{
	//open file for saving info as .xml
	filename += ".xml";

	cout << "The filename is " << filename << endl;

	ofstream saveFile;
	saveFile.open(filename.c_str());
	
	saveFile << "-<nodeList>\n";
	//save all the nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		saveFile << " -<node>\n";

		//save index and node information
		saveFile << "   <index>" << nodes[i].getIndex() << "</index>" << endl;
		saveFile << "   <info>" << nodes[i].getInformation() << "</info>" << endl;

		//save node tags
		vector<string> tags = nodes[i].getTags();
		saveFile << "   <tags>" << tags[0];
		for (int tg = 1; tg < tags.size(); tg++)
			saveFile << "," << tags[tg];
		saveFile << "</tags>" << endl;

		//save in edges by edge index
		vector<Edge*> inedges = nodes[i].getInEdges();
		if ( inedges.size() != 0 )
		{	
			saveFile << "   <inedges>" << inedges[0]->getIndex();
			for (int ne = 1; ne < inedges.size(); ne++)
				saveFile << "," << inedges[ne]->getIndex();
			saveFile << "</inedges>" << endl;
		}

		//save out edges by edge index
		vector<Edge*> oedges = nodes[i].getOutEdges();
		if ( oedges.size() != 0 )
		{
			saveFile << "   <outedges>" << oedges[0]->getIndex();
			for (int ne = 1; ne < oedges.size(); ne++)
				saveFile << "," << oedges[ne]->getIndex();
			saveFile << "</outedges>" << endl;
		}

		saveFile << "  </node>" << endl;
	}
	
	saveFile << "\n-<edgeList>\n";
	//save all the edges
	for (int i = 0; i < edges.size(); i++)
	{
		saveFile << " -<edge>\n";

		//save index and node information
		saveFile << "   <index>" << edges[i].getIndex() << "</index>" << endl;
		saveFile << "   <relation>" << edges[i].getRelation() << "</relation>" << endl;
		saveFile << "   <nodeA>" << edges[i].getNodeA() << "</nodeA>" << endl;
		saveFile << "   <nodeB>" << edges[i].getNodeB() << "</nodeB>" << endl;		

		saveFile << "  </edge>" << endl;
	}
	
	saveFile.close();
}

#endif

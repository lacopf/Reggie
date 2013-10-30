#ifndef _GRAPH
#define _GRAPH

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#include "node.h"
#include "edge.h"

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
		void load(string filename);
		void draw();

	private:
		vector<Node> nodes;
		vector<Edge> edges;
};


void Graph::addNode(string info, vector<string> tags, int index)
{
	Node n1(info, index, tags);
	nodes.push_back(n1);
}

void Graph::addEdge(int n1, int n2, string rel)
{
	Edge e(edges.size(), rel, n1, n2);
	edges.push_back(e);
	Edge* p = &(edges.back());
	nodes[n2].addInEdge(p);
	nodes[n1].addOutEdge(p);
}

void Graph::printNodes()
{
	for(int i=0; i<nodes.size(); i++)
	{
		cout << i << ": " << nodes[i].getInformation() << endl;
	}
}

void Graph::removeEdge(int index)
{
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

void Graph::removeNode(int index)
{
	if(index != 0)
	{
		Node& n = nodes[index];
		//removes all ingoing edges from graph
		const vector<Edge*>& inedges = n.getInEdges();
		for(int i=0; i<inedges.size(); i++)
		{
			removeEdge(inedges[i] -> getIndex());
		}

		//removes all outgoing edges from graph
		const vector<Edge*>& outedges = n.getOutEdges();
		for(int i=0; i<outedges.size(); i++)
		{
			removeEdge(outedges[i] -> getIndex());
		}

		//removes node from nodes vector
		nodes[index] = nodes.back();
		nodes[index].setIndex(index);
		nodes.pop_back();
	}
	else
	{
		cout << "You cannot delete the root node" << endl;
	}
}


//prints all in and out edges for each node in the graph
void Graph::printGraph()
{
        for(int i=0; i < nodes.size(); i++)
        {
				//print index, info and tags
                cout << i << ": " << nodes[i].getInformation() << endl;
				vector<string> temptags =  nodes[i].getTags();
				cout << "tags: " << temptags[0];
				for (int tgs = 1; tgs < temptags.size(); tgs++)
					cout << ", " << temptags[tgs];
				cout << endl;

                cout << " in edges: ";
                const vector<Edge*>& in_edges = nodes[i].getInEdges();
                for(int j=0; j<in_edges.size(); j++)
                {
                        cout << (in_edges[j]->getNodeA)()<< " ";
                }
                cout << endl;
                cout << " out edges: ";
                const vector<Edge*>& out_edges = nodes[i].getOutEdges();
                for(int j=0; j<out_edges.size(); j++)
                {
                        cout << (out_edges[j]->getNodeB)()<< " ";
                }
                cout << endl << endl;
        }
}
//saves the graph to the file
void Graph::save(string filename)
{
	int p = filename.find(".xml");
	cout << filename.substr(filename.size() - 4, 4) << endl;
	if (p == string::npos || filename.length() < 4 || filename.substr(filename.size() - 4, 4).compare(".xml") != 0 )
		filename += ".xml";

	cout << "The filename is " << filename << endl;

	ofstream saveFile;
	saveFile.open(filename.c_str());

	saveFile << "<graph>\n";
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
		{
			saveFile << "," << tags[tg];
		}
		saveFile << "</tags>" << endl;

		//save in edges by edge index
		vector<Edge*> inedges = nodes[i].getInEdges();
		if ( inedges.size() != 0 )
		{	
			saveFile << "   <inedges>" << inedges[0]->getIndex();
			for (int ne = 1; ne < inedges.size(); ne++)
			{
				saveFile << "," << inedges[ne]->getIndex();
			}
			saveFile << "</inedges>" << endl;
		}

		//save out edges by edge index
		vector<Edge*> oedges = nodes[i].getOutEdges();
		if ( oedges.size() != 0 )
		{
			saveFile << "   <outedges>" << oedges[0]->getIndex();
			for (int ne = 1; ne < oedges.size(); ne++)
			{
				saveFile << "," << oedges[ne]->getIndex();
			}
			saveFile << "</outedges>" << endl;
		}

		saveFile << "  </node>" << endl;
	}
	saveFile << " </nodeList>\n";
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

	saveFile << " </edgeList>\n";
	saveFile << "</graph>\n";
	saveFile.close();
}
void Graph::load(string filename)
{
	//assume the filename has the proper extension
	ifstream source;
	source.open( filename.c_str() );
	if ( !source.is_open() )
	{
		filename += ".xml";
		source.open( filename.c_str() );
		if ( !source.is_open() )
		{
			cout << "Invalid file name\n";
			return;
		}
	}

	string line = "";
	Node dummyNode;
	Edge dummyEdge;
	vector<Node> loadedNodes;
	vector<Edge> loadedEdges;
	vector<vector<int> > nodeInEdges;
	vector<vector<int> > nodeOutEdges;


	getline( source, line, '\n');
	if ( line.find("graph") == string::npos )
	{
		cout << "Not a graph file\n";
		return;
	}

	getline( source, line, '\n');
	if ( line.find("nodeList") == string::npos )
	{
		cout << "Not a valid file to load from\n";
		return;
	}	
	
	getline(source, line, '\n');
	while ( line.find("/nodeList") == string::npos )
	{
		//new node information
		int node_index;
		string info;
		vector<string> tags;
		vector<int> nedges;
		vector<int> oedges;

		//get the line with the index information
		getline(source, line, '\n');
		int parse_index = line.find("<index>");
		
		//not a valid file
		if (parse_index == string::npos)
		{
			cout << "Invalid load file\n";
			return;
		}

		//get to the index location in the line
		parse_index += 7;

		if (line[parse_index] == '-')
			node_index = -1;
		else
		{
			char* number = &line[parse_index];
			node_index = atoi( number );
		}

		//get the line with the node information
		getline(source, line, '\n');
		parse_index = line.find("<info>");
		int endIndex = line.find("</info>");

		//not a valid file
		if (parse_index == string::npos || endIndex == string::npos)
		{
			cout << "Invalid load file\n";
			return;
		}
		else
		{
			int len = endIndex - parse_index - 6;
			info = line.substr(parse_index + 6, len);
		}

		//get the line with the tags
		getline(source, line, '\n');
		parse_index = line.find("<tags>");
		endIndex = line.find("</tags>");

		//not a valid file
		if (parse_index == string::npos || endIndex == string::npos)
		{
			cout << "Invalid load file\n";
			return;
		}
		else 
		{
			string tL = line.substr(parse_index + 6, endIndex - parse_index - 6);
			char* tagList = &tL[0];

			char* singleTag;
			singleTag = strtok(tagList, ",");

			while ( singleTag != NULL)
			{
				tags.push_back(singleTag);
				singleTag = strtok(NULL, ",");
			}
		}

		//get the line with the in edges
		getline(source, line, '\n');
		parse_index = line.find("<inedges>");
		endIndex = line.find("</inedges>");

		if (parse_index != string::npos)
		{
			string neL = line.substr(parse_index + 9, endIndex - parse_index - 9);
			char* nedgeList = &neL[0];

			char* singleEdge;
			singleEdge = strtok(nedgeList, ",");

			while ( singleEdge != NULL)
			{
				nedges.push_back( atoi(singleEdge) );
				singleEdge = strtok(NULL, ",");
			}
			
			//get the line with the out edges
			getline(source, line, '\n');
		}
	
		parse_index = line.find("<outedges>");
		endIndex = line.find("</outedges>");

		if (parse_index != string::npos)
		{
			string oeL = line.substr(parse_index + 10, endIndex - parse_index - 10);
			char* oedgeList = &oeL[0];

			char* singleEdge;
			singleEdge = strtok(oedgeList, ",");

			while ( singleEdge != NULL)
			{
				oedges.push_back( atoi(singleEdge) );
				singleEdge = strtok(NULL, ",");
			}
			//get the line with the out edges
			getline(source, line, '\n');
		}

		//if the next line is the end of the nodeList, the loop ends
		//else, it continues reading in nodes
		getline(source, line, '\n');

		Node tempNode(info, node_index, tags);
		loadedNodes.push_back(tempNode);
		nodeInEdges.push_back(nedges);
		nodeOutEdges.push_back(oedges);
		
	}

	getline(source, line, '\n');
	getline(source, line, '\n');

	//read in edges
	while ( line.find("/edgeList") == string::npos )
	{
		int edgeIndex;
		string relation;
		int nA,nB;

		getline(source, line, '\n');
		getline(source, line, '\n');
		
		int parse_index = line.find("<index>");
		if (parse_index == string::npos)
		{
			cout << "INDInvalid file to load from\n";
			return;
		}

		char* p = &line[parse_index + 7];
		edgeIndex = atoi( p );

		getline(source, line, '\n');
		parse_index = line.find("<relation>");
		int endIndex = line.find("</relation>");
		if (parse_index == string::npos || endIndex == string::npos)
		{
			cout << "RELInvalid file to load from\n";
			return;
		}

		relation = line.substr(parse_index + 10, endIndex - parse_index - 10);

		//get the Node A
		getline(source, line, '\n');
		parse_index = line.find("<nodeA>");
		
		if (parse_index == string::npos)
		{
			cout << "NAInvalid file to load from\n";
			return;
		}

		p = &line[parse_index + 7];
		nA = atoi( p );


		//get Node B
		getline(source, line, '\n');
		parse_index = line.find("<nodeB>");
		if (parse_index == string::npos)
		{
			cout << "NBInvalid file to load from\n";
			return;
		}


		p = &line[parse_index + 7];
		nB = atoi( p );

		//chew up remainder of lines before next line of relevant info
		getline(source, line, '\n');
		getline(source, line, '\n');

		//add read in info to list of read in edges
		Edge tempEdge(edgeIndex, relation, nA, nB);
		loadedEdges.push_back(tempEdge);
		
	}

	//close the input file
	source.close();
	
	//clear the current graph object and load in the new vector of nodes and edges
	nodes.clear();
	edges.clear();

	for (int i = 0; i < loadedNodes.size(); i++)
		nodes.push_back(loadedNodes[i]);
	for (int i = 0; i < loadedEdges.size(); i++)
		edges.push_back(loadedEdges[i]);

	//reassign edges to nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int numInEdges = 0; numInEdges < nodeInEdges[i].size(); numInEdges++)
		{
			for(int searchEdges = 0; searchEdges < edges.size(); searchEdges++)
				if (edges[searchEdges].getIndex() == nodeInEdges[i][numInEdges])
				{
					nodes[i].addInEdge(&edges[searchEdges]);
				}
		}
		for (int numOutEdges = 0; numOutEdges < nodeOutEdges[i].size(); numOutEdges++)
		{
			for(int searchEdges = 0; searchEdges < edges.size(); searchEdges++)
				if (edges[searchEdges].getIndex() == nodeOutEdges[i][numOutEdges])
				{
					nodes[i].addOutEdge(&edges[searchEdges]);
				}
		}
	}
	
	cout << "File was successfully loaded!\n";

}
void Graph::draw()
{
	for(int i = 0; i < edges.size(); i++)
	{
		edges[i].draw();
	}
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i].draw();
	}
}

#endif

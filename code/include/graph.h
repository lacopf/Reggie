#ifndef _GRAPH
#define _GRAPH

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
		vector<Node>* getNodes(){ return &nodes; }
		vector<Edge*> getEdges(){ return edges; }

		Graph();
		inline void addNode(Node node){ nodes.push_back(node); }
		void addNode(string info, vector<string> tags, int x, int y);
		void addEdge(int n1, int n2, string rel);
		void removeEdge(int index);
		void removeNode(int index);
		void printGraph();
		void saveSortedGraph();
		vector<int> topSort();
		bool visitNode(int node, vector<bool>& visited, vector<bool>& permanent, vector<int>& sortedVec);
		void save(string filename, bool isTemplate);
		void load(string filename, bool isTemplate);
		void draw();

	private:
		vector<Node> nodes;
		vector<Edge*> edges;
		bool f;
};

Graph::Graph(){
	//f = true;
}

//adds a node to the graph
void Graph::addNode(string info, vector<string> tags, int x, int y)
{
	/*if(nodes.size() == 1 && f)
	{
		nodes.clear();
		f = false;
	}*/
	Node n1(info, nodes.size(), tags, x, y);
	nodes.push_back(n1);
}

//adds an edge between two nodes to the graph
void Graph::addEdge(int n1, int n2, string rel)
{
	Edge* p = new Edge(edges.size(), rel, n1, n2);
	edges.push_back(p);
	nodes[n2].addInEdge(p);
	nodes[n1].addOutEdge(p);
	cout << n1 << " " << n2 << " " << p->getNodeB() << endl;
}


void Graph::removeEdge(int index)
{
	//removes edge from source node
	Node& n1 = nodes[(edges[index]) -> getNodeA()];
	n1.removeOutEdge(edges[index]);

	//removes edge from target node
	Node& n2 = nodes[(edges[index]) -> getNodeB()];
	n2.removeInEdge(edges[index]);

	//moves back of edges to index position and pops back
	edges[index] = edges.back();
	edges[index]->setIndex(index);
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

//Saves topologically sorted graph in a text file
void Graph::saveSortedGraph(){
	ofstream out("sorted.txt");
	vector<int> sorted = topSort();
	for(int i=0; i<sorted.size(); i++){
		out << nodes[i].getInformation() << endl;
	}	
}


//Returns a vector of indices of nodes in graph when sorted in topological order.
//returns an empty list if graph is not a DAG
vector<int> Graph::topSort(){
	vector<bool> visited(nodes.size(), false);
	vector<bool> permanent(nodes.size(), false);
	vector<int> sortedVec;

	//calls visitNode on all nodes in graph 
	//each call represents a new tree if the graph is a DAG
	for(int i=0; i<nodes.size(); i++){
		if(permanent[i]){continue;}
		else if (visitNode(i, visited, permanent, sortedVec)){vector<int> t; return t;}
	}
	vector<int> finalVec; 
	//reverses sorted list
	for(int i=sortedVec.size()-1; i >= 0; i--){
		finalVec.push_back(sortedVec[i]);
	}
	return finalVec;
}

//returns true if graph is a DAG
//visits all children in a DFS pattern
bool Graph::visitNode(int node, vector<bool>& visited, vector<bool>& permanent, vector<int>& sortedVec){
	if(visited[node] & not permanent[node]){return true;} //graph is a DAG
	else if(permanent[node]){return false;} //not a DAG, but this node has been seen before
	visited[node] = true;
	const vector<Edge*>& outEdges = nodes[node].getOutEdges(); 
	for(int i=0; i< outEdges.size(); i++){
		//calls visitNode on child, returns true if recursive call returned true (graph is a DAG) 
		if(visitNode(outEdges[i]->getNodeB(), visited, permanent, sortedVec)){return true;}
	}
	permanent[node] = true;
	sortedVec.push_back(node);
	return false;
}

//saves the graph to the file
void Graph::save(string filename, bool isTemplate)
{
	struct stat info;

	//make a templates folder if one doesn't exist
	if ( lstat("./templates", &info) == -1 )
		mkdir("./templates", S_IRWXU);

	//treat files differently based on whether it's ging to saved as a template or not
	if (!isTemplate)
	{
		int p = filename.find(".xml");
		if (p == string::npos || filename.length() < 4 || filename.substr(filename.size() - 4, 4).compare(".xml") != 0 )
			filename += ".xml";

	}
	else
	{
		int p = filename.find(".bgt");
		if (p == string::npos || filename.length() < 4 || filename.substr(filename.size() - 4, 4).compare(".bgt") != 0 )
			filename += ".bgt";
		chdir("./templates");
	}
	
	ofstream saveFile;
	saveFile.open(filename.c_str());
	cout << "The filename is " << filename << endl;


	if (isTemplate)
	{
		saveFile << "<template></template>\n";
	}

	saveFile << "<graph>\n";
	saveFile << "-<nodeList>\n";
	//save all the nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		saveFile << " -<node>\n";

		//save index and node information
		saveFile << "   <index>" << nodes[i].getIndex() << "</index>" << endl;
		saveFile << "   <info>" << nodes[i].getInformation() << "</info>" << endl;
		saveFile << "   <point>" << nodes[i].getPoint().getX() << "," << nodes[i].getPoint().getY() << "</point>" << endl;

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
		saveFile << " -<edge>" << endl;

		//save index and node information
		saveFile << "   <index>" << edges[i]->getIndex() << "</index>" << endl;
		saveFile << "   <relation>" << edges[i]->getRelation() << "</relation>" << endl;
		saveFile << "   <nodeA>" << edges[i]->getNodeA() << "</nodeA>" << endl;
		saveFile << "   <nodeB>" << edges[i]->getNodeB() << "</nodeB>" << endl;		

		saveFile << "  </edge>" << endl;
	}

	saveFile << " </edgeList>\n";
	saveFile << "</graph>\n";
	saveFile.close();

	if (isTemplate)
		chdir("..");
}
void Graph::load(string filename, bool isTemplate = false)
{
	//assume the filename has the proper extension
	ifstream source;
	source.open( filename.c_str() );
	if ( !source.is_open() )
	{
		string filenametemp = filename + ".xml";
		source.open( filename.c_str() );
	}
	if ( !source.is_open() )
	{
		filename += ".bgt";
		source.open( filename.c_str() );
		if ( !source.is_open() )
		{
			cout << "Invalid file name\n";
			return;
		}
	}

	//all my temporary variables
	string line = "";
	//bool isTemplate = false;
	Node dummyNode;
	Edge dummyEdge;
	vector<Node> loadedNodes;
	vector<Edge> loadedEdges;
	vector<vector<int> > nodeInEdges;
	vector<vector<int> > nodeOutEdges;


	getline( source, line, '\n');
	if ( line.find("template") != string::npos )
	{
		getline( source, line, '\n');
		isTemplate = true;
	}
	else if ( line.find("graph") == string::npos )
	{
		cout << "Not a graph file\n";
		return;
	}
	
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
		int endIndex;
		string info;
		int x, y;
		vector<string> tags;
		vector<int> nedges;
		vector<int> oedges;

		//get the line with the index information
		getline(source, line, '\n');
		int parse_index = line.find("<index>");
		endIndex = line.find("</index>");

		//not a valid file
		if (parse_index == string::npos)
		{
			cout << "Invalid load file\n";
			return;
		}

		//get to the index location in the line
		parse_index += 7;

		if (line[parse_index + 7] == '-')
			node_index = -1;
		else
		{
			const char* buf = (line.substr(parse_index + 7, endIndex - parse_index - 7)).c_str();
			node_index = atoi( buf );
		}

		//get the line with the node information
		getline(source, line, '\n');
		parse_index = line.find("<info>");
		endIndex = line.find("</info>");

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


		//get the line with the point information
		getline(source, line, '\n');
		parse_index = line.find("<point>");
		endIndex = line.find("</point>");
		
		//not a valid file
		if (parse_index == string::npos || endIndex == string::npos)
		{
			cout << "Invalid load file\n";
			return;
		}
		else
		{
			int findComma = line.find(",");
			const char* buf = (line.substr(parse_index + 7, findComma - parse_index - 7)).c_str();
			x = atoi( buf );
			buf = (line.substr(findComma + 1, endIndex - findComma - 1)).c_str();
			y = atoi( buf );
			
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

		Node tempNode(info, node_index, tags, x, y);
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
		if (line.find("<index>") == string::npos)
			getline(source, line, '\n');			
		
		int parse_index = line.find("<index>");
		int endIndex = line.find("</index>");
		if (parse_index == string::npos)
		{
			break;
		}

		const char* p = ( line.substr(parse_index + 7, endIndex - parse_index - 7) ).c_str();
		edgeIndex = atoi( p );

		getline(source, line, '\n');
		parse_index = line.find("<relation>");
		endIndex = line.find("</relation>");
		if (parse_index == string::npos || endIndex == string::npos)
		{
			cout << "RELInvalid file to load from\n";
			return;
		}

		relation = line.substr(parse_index + 10, endIndex - parse_index - 10);

		//get the Node A
		getline(source, line, '\n');
		parse_index = line.find("<nodeA>");
		endIndex = line.find("</nodeA>");
		if (parse_index == string::npos || endIndex == string::npos)
		{
			cout << "NAInvalid file to load from\n";
			return;
		}

		const char* r = ( line.substr(parse_index + 7, endIndex - parse_index - 7) ).c_str();
		nA = atoi( r );


		//get Node B
		getline(source, line, '\n');
		parse_index = line.find("<nodeB>");
		endIndex = line.find("</nodeA>");
		if (parse_index == string::npos)
		{
			cout << "NBInvalid file to load from\n";
			return;
		}


		const char* q = ( line.substr(parse_index + 7, endIndex - parse_index - 7) ).c_str();
		nB = atoi( q );

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
	for (int i = 0; i < loadedEdges.size(); i++){
		Edge& e = loadedEdges[i];		
		Edge* p = new Edge(e.getIndex(), e.getRelation(), e.getNodeA(), e.getNodeB());
		//p* = loadedEdges[i]; //!!!!!!!!!!PROBLEM?	
		edges.push_back(p);
	}

	//reassign edges to nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int numInEdges = 0; numInEdges < nodeInEdges[i].size(); numInEdges++)
		{
			for(int searchEdges = 0; searchEdges < edges.size(); searchEdges++)
				if (edges[searchEdges]->getIndex() == nodeInEdges[i][numInEdges])
				{
					nodes[i].addInEdge(edges[searchEdges]);
				}
		}
		for (int numOutEdges = 0; numOutEdges < nodeOutEdges[i].size(); numOutEdges++)
		{
			for(int searchEdges = 0; searchEdges < edges.size(); searchEdges++)
				if (edges[searchEdges]->getIndex() == nodeOutEdges[i][numOutEdges])
				{
					nodes[i].addOutEdge(edges[searchEdges]);
				}
		}
	}
	
	cout << "File was successfully loaded!\n";

}
void Graph::draw()
{
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );

	//edges
	for(int i = 0; i < edges.size(); i++)
	{
		
		glLineWidth(3*3.14159265359); 
		glColor3f(16.0 / 255.0, 73.0 / 255.0, 169.0 / 255.0);
		
		float startX = nodes[edges[i]->getNodeA()].getPoint().getX();
		float startY = nodes[edges[i]->getNodeA()].getPoint().getY();
		
		float endX = nodes[edges[i]->getNodeB()].getPoint().getX();
		float endY = nodes[edges[i]->getNodeB()].getPoint().getY();
		
		float diffX = endX - startX;
		float diffY = endY - startY;
		float length = sqrt(diffX*diffX + diffY*diffY);
		
		float pointX = endX - diffX/length*RADIUS;
		float pointY = endY - diffY/length*RADIUS;
		
		float centX = pointX - diffX/length*RADIUS/3;
		float centY = pointY - diffY/length*RADIUS/3;
		
		float leftX = centX - diffY/length*RADIUS/3;
		float leftY = centY + diffX/length*RADIUS/3;
		
		float rightX = centX + diffY/length*RADIUS/3;
		float rightY = centY - diffX/length*RADIUS/3;
		
		glBegin(GL_LINES);
			glVertex2f(startX, startY);
			glVertex2f(centX, centY);
		glEnd();
		
		glBegin(GL_TRIANGLES);
			glVertex2f(leftX,leftY);
			glVertex2f(pointX, pointY);
			glVertex2f(rightX,rightY);
		glEnd();
	}
	//nodes
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i].draw();
	}
	
}

#endif

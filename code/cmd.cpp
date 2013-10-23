//standard includes
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//babel graph includes
#include "include/graph.h"

//function prototypes
vector<string> parse(string tagString);

// main function
int main(int argc, char *argv[])
{
	string input;
	string info;
	Graph graph;
	
	cout << "Welcome to OpenTextReggieTextBabelGraphTextReggieOpenGraph!May I take your order?\n1. Create Root Node\n: ";
	cin >> input;
	while(input != "1")
	{
		cout << "I'm sorry.\nThat is not a valid menu option.\nPlease, select again.\n1. Create Root Node\n: ";
		cin >> input;
	}
	cout << "Thank you for selecting \"Create Root Node\".\nPlease input a single piece of information to identify your root node.\n: ";
	cin >> info;
	
	cout << "Thank you for adding information.\nPlease input all tags to be associated with the root node, separated by commas without spaces.\n: ";
	cin >> input;
		
	graph.addNode(info, parse(input), -1);
	
	int index1, index2;
	
	while(true)
	{
		cout << "\n\nPlease, select your next task from the menu.\n1. Display Graph\n2. Add Node\n3. Remove Node\n4. Add Edge\n5. Remove Edge\n: ";
		cin >> input;

		//print graph
		if(input == "1")
		{
			graph.printGraph();
		}
		//add node
		else if(input == "2")
		{
			cout << "Input info: ";
			cin >> info;
			cout << "Input tags: ";
			cin >> input;
			graph.printNodes();
			cout << "Choose a parent node: ";
			cin >> index1;
			graph.addNode(info, parse(input), index1);
		}
		//remove node
		else if(input == "3")
		{
			graph.printNodes();
			cout << "Choose a node to remove: ";
			cin >> index1;
			if (index1 >= graph.getNodes().size())
				cout << "Node does not exist\n";
			else if (index1 == 0)
				cout << "Can't remove the root node\n";
			else
				graph.removeNode(index1);
		}
		//add edge
		else if(input == "4")
		{
			graph.printNodes();
			cout << "Choose a the first node: ";
			cin >> index1;
			cout << "Choose a the second node: ";
			cin >> index2;
			cout << "Input the relation: ";
			cin >> input;
			graph.addEdge(index1, index2, input);
		}
		//remove edge
		else if(input == "5")
		{
			graph.printNodes();
			cout << "Choose a the first node: ";
			cin >> index1;
			cout << "Choose a the second node: ";
			cin >> index2;

			vector<Edge> edgs = graph.getEdges();
			int i;
			for (i = 0; i < edgs.size(); i++)
			{
				if (edgs[i].getNodeA() == index1 && edgs[i].getNodeB() == index2)
				{
					graph.removeEdge(i);
					break;
				}

			}
			if (i == edgs.size() )
				cout << "Edge wasn't removed/doesn't exist\n";
		}
		else
		{
			cout << "BAD BAD BAD BAD BAD\n\n";
		}
	}

	return 0;
}

vector<string> parse(string tagString)
{
	vector<string> tags;
	string temp;
	
	for(int i = 0; i < tagString.length(); i++)
	{
		if(tagString[i] == ',')
		{
			tags.push_back(temp);
			temp.clear();
		}
		else
		{
			temp = temp + tagString[i];
		}
	}
	tags.push_back(temp);
	
	return tags;
}


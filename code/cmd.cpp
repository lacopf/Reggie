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
	
	cout << "Welcome to Reggie's Ready Body! Would you like me to Fravel your Arviden?\n1. Create Root Node\n: ";
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
		cout << "\n\nPlease, select your next task from the menu.\n1. Display Graph\n2. Add Node\n3. Remove Node\n4. Add Edge\n5. Remove Edge\n6. Save Graph\n";
		cout << "7. Load Graph\n8. Quit\n:";
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
			
			//checks if the parent exists
			if (index1 >= graph.getNodes().size()  || index1 < 0 || cin.fail())
			{
				cout << "Not a valid parent node\n";
			}
			else
			{	
				graph.addNode(info, parse(input), index1);
			}
		}
		//remove node
		else if(input == "3")
		{
			graph.printNodes();
			cout << "Choose a node to remove: ";
			cin >> index1;

			//node out of bounds, function prevents root node deletion
			if ( index1 >= graph.getNodes().size()  || index1 < 0)
			{
				cout << "Node does not exist\n";
			}
			else
			{
				graph.removeNode(index1);
			}
		}
		//add edge
		else if(input == "4")
		{
			graph.printNodes();
			cout << "Choose the first node: ";
			cin >> index1;
			cout << "Choose the second node: ";
			cin >> index2;
			cout << "Input the relation: ";
			cin >> input;
			int bound = graph.getNodes().size();
			
			//makes sure both nodes exist
			if ( index1 >= bound || index1 < 0 || index2 >= bound || index2 < 0)
			{
				cout << "Not a valid node assignment\n";
			}
			else
			{
				graph.addEdge(index1, index2, input);
			}
		}
		//remove edge
		else if(input == "5")
		{
			graph.printNodes();
			cout << "Choose the first node: ";
			cin >> index1;
			cout << "Choose the second node: ";
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
			{
				cout << "Edge wasn't removed/doesn't exist\n";
			}
		}
		else if(input == "6")
		{
			string filen;
			cout << "Enter a filename: ";
			cin >> filen;
			graph.save(filen);			
		}
		else if(input == "7")
		{
			string filen;
			cout << "Enter a filename: ";
			cin >> filen;
			graph.load(filen);			
		}
		else if(input == "8")
		{
			cout << "Reggie thanks you for your time!\n";
			char c;
			cin >> c;	
			exit (0);
		}
		else
		{
			cout << "BAD BAD BAD BAD BAD\n\n";
		}
		
		//flush input buffer to prevent infinite looping on bad input
		cin.clear(); cin.ignore(999999,'\n'); 
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


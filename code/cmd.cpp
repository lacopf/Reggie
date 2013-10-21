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
		if(input == "1")
		{
			graph.printGraph();
		}
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
		else if(input == "3")
		{
			graph.printNodes();
			cout << "Choose a node to remove: ";
			cin >> index1;
			graph.removeNode(index1);
		}
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
		else if(input == "5")
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


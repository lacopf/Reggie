
#ifndef _node_h_
#define _node_h_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "edge.h"

class Node{
	private:
	  string information;
	  vector<string> tags;
	  int index;
	  Node* parent;
	  vector<Edge*> edges;
	  
	public:
	  int inline get_index() {return index;}
	  string inline get_information() {return information;}
	  Node* inline get_parent() {return parent;}
	  
	  Node();
	  Node(string info, int ind, Node* par);

	  void inline add_edge(Edge* edg) {edges.push_back(edg);}
	  void inline add_tag(string tag) {tags.push_back(tag);}

	  bool has_tag(string tag);
  
};

Node::Node()
{
	vector<string> tempt;
	vector<Edge*> tempe;

	tags = tempt;
	edges = tempe;
	information = "";
	index = -1;
	parent = NULL;
}
Node::Node(string info, int ind, Node* par)
{
	vector<string> tempt;
	vector<Edge*> tempe;

	tags = tempt;
	edges = tempe;
	information = info;
	index = ind;
	parent = par;
}
Node::has_tag(string tag)
{
	for (int i = 0; i < tags.size(); i++)
		if (tags[i].compare(tag) == 0)
			return true;

	return false;
}

#endif



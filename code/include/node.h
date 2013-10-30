#ifndef _NODE
#define _NODE

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <math.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#include "edge.h"

class Node
{
	private:
		string information;
		vector<string> tags;
		int index;
		vector<Edge*> in_edges;
		vector<Edge*> out_edges;
		Point point;
		

	public:
		Node();
		Node(string info, int ind, vector<string> new_tags, int x, int y);
		
		inline int getIndex() {return index;}
		inline string getInformation() {return information;}
		inline vector<Edge*> getInEdges(){return in_edges;}
		inline vector<Edge*> getOutEdges(){return out_edges;}
		inline vector<string> getTags() {return tags;}

		void inline addInEdge(Edge* edg) {in_edges.push_back(edg);}
		void inline addOutEdge(Edge* edg) {out_edges.push_back(edg);}
		void removeInEdge(Edge* edg);
		void removeOutEdge(Edge* edg);
		inline void addTag(string tag) {tags.push_back(tag);}
		inline void setIndex(int ind){index = ind;}

		bool hasTag(string tag);
		
		void draw();
		Point getPoint()
		{
			return point;
		}
};
//default constructor
Node::Node()
{
	vector<string> tempt;
	vector<Edge*> tempe;

	tags = tempt;
	in_edges = tempe;
	out_edges = tempe;
	information = "";
	index = -1;
	point = Point(-1,-1,false);
}
//constructor with information
Node::Node(string info, int ind, vector<string> new_tags, int x, int y)
{
	vector<Edge*> tempe;

	tags = new_tags;
	in_edges = tempe;
	out_edges = tempe;
	information = info;
	index = ind;
	point = Point(x,y,true);
}
//returns whether a node has a given tag
bool Node::hasTag(string tag)
{
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i].compare(tag) == 0)
		{
			return true;
		}
	}

	return false;
}
//removes an edge coming into a node
void Node::removeInEdge(Edge* edg)
{
	if(edg->getIndex() >= in_edges.size())
	{
		cout << "node does not contain this edge" << endl;
	}
	else
	{
		in_edges[edg->getIndex()] = in_edges.back();
		in_edges.pop_back();
	}
}
//removes an edge going into a node
void Node::removeOutEdge(Edge* edg)
{
	if(edg->getIndex() >= out_edges.size())
	{
		cout << "node does not contain this edge" << endl;
	}
	else
	{
		out_edges[edg->getIndex()] = out_edges.back();
		out_edges.pop_back();
	}
}
void Node::draw()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
		for (int i=0; i < 360; i++)
		{
			float degInRad = i*M_PI/180;
			glVertex2f(cos(degInRad)*2.0+point.getX()/5.0,sin(degInRad)*2.0+point.getY()/5.0);
		}
	glEnd();
	
}

#endif

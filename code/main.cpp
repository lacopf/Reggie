//includes
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "include/graph.h"

using namespace std;

//global variables
Graph graph;
string MODE;
string FILENAME;
string input = "DefaultInput";
vector<Point> points;
int HEIGHT = 500;
int WIDTH = 500;
int mouse_x = 0;
int mouse_y = 0;
int firstNode = -1;
int inputFunc = 0;
string info = "";
vector<string> tags;

//function prototypes
void drawScene();
void resize(int w, int h);
void keyInput(unsigned char key, int x, int y);
void mouseControl(int button, int state, int x, int y);
void mainMenu(int id);
void makeMenu(void);
int pickNode(int x, int y);
int pickEdge(int x, int y);
float dist(Point p1, int x, int y);
void mousePassiveMotion(int x, int y);
bool collisionFree(int x, int y);
void writeString(int x, int y, void *font, const char *str);

static inline std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

vector<string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void writeString(int x, int y, void *font, const char *str){
	const char *cs;
	glRasterPos2i(x, y);
	for(cs = str; *cs != '\0'; cs++)
	{
		glutBitmapCharacter(font, *cs);
	}
	glutPostRedisplay();
}

float dist(Point p1, int x, int y)
{
	return sqrt(pow(p1.getX() - x, 2) + pow(p1.getY() - y, 2));
}

bool collisionFree(int x, int y)
{
	vector<Node> nodes = graph.getNodes();
	for(int i = 0; i<nodes.size(); i++)
	{
		if(dist(nodes[i].getPoint(), x, y) <= 20)
		{
			return false;
		}
	}
	return true;
}

int pickNode(int x, int y)
{
	vector<Node> nodes = graph.getNodes();
	for(int i = 0; i<nodes.size(); i++)
	{
		if(dist(nodes[i].getPoint(), x, y) <= 10)
		{
			return i;
		}
	}
	return -1;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	gluOrtho2D(0, 500, 0, 500);
	glutCreateWindow("JungleReggie");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	MODE = "NORMAL";
	vector<string>test;
	cout << "Left click in empty space to create a node. Left click and drag from one node to another to create an edge between them." << endl;
	
	string s = "data";
	vector<string> ss;
	graph.addNode(s, ss, -50, -50);
	cout << graph.getNodes().size() << endl;
	glutMainLoop();

	return 0;
}

//display function
void drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	writeString(10, 10, GLUT_BITMAP_9_BY_15, input.c_str());
	graph.draw();

	glutSwapBuffers();
}

//window resize function
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//keyboard function
void keyInput(unsigned char key, int x, int y)
{
	if(MODE == "TYPING")
	{
		if(key == 32 && FILENAME != "")
		{
			graph.save(FILENAME);
			MODE = "NORMAL";
		}
		else
		{
			string lower = "abcdefghijklmnopqrstuvwxyz";
			string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			
			for(int i = 0; i < lower.length(); i++)
			{
				if(key == lower[i])
				{
					if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
					{
						FILENAME += upper[i];
					}
					else
					{
						FILENAME += lower[i];
					}
				}
			}
		}
	}
	else if(MODE == "INPUT")
	{
		if(key == 13)
		{
			if(inputFunc == 1)
			{
				info = input.substr(17, string::npos);	
				input = "Enter Node Tags Separated by Commas: ";
				inputFunc = 2;
			}
			else if(inputFunc == 2)
			{
				input = input.substr(37, string::npos);
				cout << points.back().getX() << ", " << points.back().getY() << endl;
				graph.addNode(info, split(input, ',', tags), points.back().getX(), points.back().getY());
				firstNode = graph.getNodes().back().getIndex();
				MODE = "NORMAL";
				input = "";
				tags.clear();
				inputFunc = 0;
			}
		}
		else
		{
			input += key;
		}
	}
	else
	{
		switch(key) 
		{
			case 27:
				exit(0);
				break;
			case 's':
				cout << "SAVING";
				if(glutGetModifiers() == GLUT_ACTIVE_CTRL)
				{
					if(FILENAME == "")
					{
						MODE = "TYPING";
					}
					else
					{
						graph.save(FILENAME);
					}
				}
				break;
			default:
				break;
		}
	}
}

//mouse function
void mouseControl(int button, int state, int x, int y)
{	

	vector<Node> nodes = graph.getNodes();

	// Store the currentPoint in the points vector when left button is released.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	
		MODE = "NORMAL";
		input = "";
		Point currentPoint = Point(x, HEIGHT - y, false);
		points.push_back(currentPoint);
		
		int pn = pickNode(currentPoint.getX(), currentPoint.getY());
		if(pn != -1)
		{
			cout << "Node " << pn << ", Data: " << nodes[pn].getInformation() << ", First 2 tags: "
			       	<< nodes[pn].getTags()[0] << " " << nodes[pn].getTags()[1] << endl;
			firstNode = pn;
		}
		else if(collisionFree(x, HEIGHT - y))
		{
			MODE = "INPUT";
			input = "Enter Node Data: ";
			inputFunc = 1;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Point currentPoint = Point(x, HEIGHT - y, true);
		points.push_back(currentPoint);
		
		int pn = pickNode(currentPoint.getX(), currentPoint.getY());
		if(pn != -1 && firstNode != -1 && pn != firstNode && !nodes[firstNode].edgeExists(pn))
		{
			string s = "edgeRelation";
			cout << firstNode << endl;
			cout << "Adding Edge from " << firstNode << " to " << pn << endl;
			graph.addEdge(firstNode, pn, s);
			firstNode = -1;
		}
	}
}

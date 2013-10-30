//includes
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

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
vector<Point> points;
int HEIGHT = 500;
int WIDTH = 500;
int mouse_x = 0;
int mouse_y = 0;

//function prototypes
void drawScene();
void resize(int w, int h);
void keyInput(unsigned char key, int x, int y);
void mouseControl(int button, int state, int x, int y);
void mainMenu(int id);
void makeMenu(void);
int pickNode(int x, int y);
int pickEdge(int x, int y);
float dist(Point p1, Point p2);
void mousePassiveMotion(int x, int y);

float dist(Point p1, int x, int y)
{
	return sqrt(pow(p1.getX() - x, 2) + pow(p1.getY() - y, 2));
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

// main function
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("JungleReggie");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	MODE = "SETUP";
	vector<string>test;
	glutMainLoop();

	return 0;
}

//display function
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

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
	switch(key) 
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

//mouse function
void mouseControl(int button, int state, int x, int y)
{	
	// Store the currentPoint in the points vector when left button is released.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Point currentPoint = Point(x, HEIGHT - y, true);
		points.push_back(currentPoint);
		
		int pn = pickNode(currentPoint.getX(), currentPoint.getY());
		cout << pn << endl;
		if(pn != -1)
		{
			
		}
		else
		{
			string s = "data";
			vector<string> ss;
			cout << points.back().getX() << ", " << points.back().getY() << endl;
			graph.addNode(s, ss, 1, points.back().getX(), points.back().getY());
			graph.printNodes();
		}
	}
	
	glutPostRedisplay();
}

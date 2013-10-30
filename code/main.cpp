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

using namespace std;

#include "include/graph.h"
#include "include/point.h"

using namespace std;

//global variables
Graph graph;
string MODE;
vector<Point> points;
int HEIGHT = 500;
int WIDTH = 500;


//function prototypes
void drawScene();
void resize(int w, int h);
void keyInput(unsigned char key, int x, int y);
void mouseControl(int button, int state, int x, int y);


// main function
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("BabelReggieGraphBodyReadySuperRobotMonkeyTeamHyperForceGo");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	
	MODE = "SETUP";

	glutMainLoop();

	return 0;
}

//display function
void drawScene()
{
	glColor3f(1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//graph.draw();
	
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
	// Store the clicked point in the currentPoint variable when left button is pressed.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Point currentPoint = Point(x, HEIGHT - y, true);
		points.push_back(currentPoint); 
		cout << currentPoint.getX() << ", " << currentPoint.getY() << endl;
	}

	// Store the currentPoint in the points vector when left button is released.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Point currentPoint = Point(x, HEIGHT - y, false);
		points.push_back(currentPoint);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		exit(0);
	}

	glutPostRedisplay();
}

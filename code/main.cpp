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

//global variables


//function prototypes
void drawScene();


// main function
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Engine");
	glutDisplayFunc(drawScene);
	//glutReshapeFunc(resize);
	//glutKeyboardFunc(keyInput);
	//glutMouseFunc(mouseControl);

	glutMainLoop();

	return 0;
}

//display function
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
		
	
	glutSwapBuffers();
}

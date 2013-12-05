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

using namespace std;

//Node radius
int RADIUS = 50;
//Tracks current project state
string MODE;
//Holds text messages
string MESSAGE;
//Stores filenames for saving/loading
string FILENAME;
//integer indices pointing to most
//recently picked node and edge
int pn = -1;
int pe = -1;

#include "include/graph.h"
#include "include/utils.cpp"

int main(int argc, char *argv[])
{
	opengl_init(argc, argv);

	return 0;
}

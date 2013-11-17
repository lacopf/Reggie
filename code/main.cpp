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

int RADIUS = 20;

#include "include/graph.h"
#include "include/utils.cpp"

int main(int argc, char *argv[])
{
	opengl_init(argc, argv);

	return 0;
}


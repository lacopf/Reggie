#include <iostream>

using namespace std;

#include "button.h"

///global variables
Graph graph;
string MODE;
string FILENAME;
int cursorBlinkFrame = 0;
bool ACTIVE_CTRL = false;
string input = "";
vector<Point> points;
int HEIGHT = 500;
int WIDTH = 500;
int mouse_x = 0;
int mouse_y = 0;
int firstNode = -1;
int pn = -1;
int inputFunc = 0;
string info = "";
vector<string> tags;
vector<Button> demButtons;



//string split helper
vector<string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

//writes bitmap string to screen
void writeString(int x, int y, void *font, const char *str){
	const char *cs;
	glRasterPos2i(x, y);
	for(cs = str; *cs != '\0'; cs++)
	{
		glutBitmapCharacter(font, *cs);
	}
	glutPostRedisplay();
}

//euclidean distance
float dist(Point p1, int x, int y)
{
	return sqrt(pow(p1.getX() - x, 2) + pow(p1.getY() - y, 2));
}

//check if candidate node would overlap any other nodes
bool collisionFree(int x, int y)
{
	vector<Node>* nodes = graph.getNodes();
	for(int i = 0; i<nodes->size(); i++)
	{
		//check the distance from each node to the mousclick position. If it is too close, don't allow node creation
		if(dist((*nodes)[i].getPoint(), x, y) <= RADIUS*2)
		{
			return false;
		}
	}
	return true;
}

//check if user clicked on a node
int pickNode(int x, int y)
{
	vector<Node>* nodes = graph.getNodes();
	for(int i = 0; i<nodes->size(); i++)
	{
		if(dist((*nodes)[i].getPoint(), x, y) <= RADIUS)
		{
			return i;
		}
	}
	return -1;
}

//button drawing function
void drawButton(string name, int row, int column)
{
	int left, right, top, bottom;
	
	left = WIDTH - 185 + 90*(column - 1);
	right = left + 80;
	top = HEIGHT - 15 - 40*(row - 1);
	bottom = top - 30;	
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(left, top);
		glVertex2f(left, bottom);
		glVertex2f(right, bottom);
		glVertex2f(right, top);
	glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	writeString(left + 5, bottom + 10, GLUT_BITMAP_9_BY_15, name.c_str());
}

//menu drawing function
void drawMenu()
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(WIDTH - 200, 0);
		glVertex2f(WIDTH, 0);
		glVertex2f(WIDTH, HEIGHT);
		glVertex2f(WIDTH - 200, HEIGHT);
	glEnd();
	
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(WIDTH - 190, 10);
		glVertex2f(WIDTH - 10, 10);
		glVertex2f(WIDTH - 10, HEIGHT - 10);
		glVertex2f(WIDTH - 190, HEIGHT - 10);
	glEnd();
	
	for(int i = 0; i < demButtons.size(); i++)
	{
		drawButton(demButtons[i].getName(), demButtons[i].getRow(), demButtons[i].getCol());
	}
	
}

//display function
void drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	writeString(10, 10, GLUT_BITMAP_9_BY_15, input.c_str());
	graph.draw();
	
	if(MODE == "SAVING" || MODE == "LOADING")
	{
		cursorBlinkFrame++;
		if(cursorBlinkFrame % 20 < 10)
		{
			input = "Enter filename: " + FILENAME + "|";
		}
		else
		{
			input = "Enter filename: " + FILENAME + "";
		}
	}
	
	drawMenu();
	
	glutSwapBuffers();
}

//window resize function
void resize(int w, int h)
{
	WIDTH = w;
	HEIGHT = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//keyboard function
void keyInput(unsigned char key, int x, int y)
{
	if(MODE == "SAVING" || MODE == "LOADING" || MODE == "TEMPLATE")
	{
		if(key == 13 && FILENAME != "")
		{
			if(MODE == "SAVING")
			{
				input = "";
				graph.save(FILENAME,false);			
			}
			else if(MODE == "LOADING")
			{
				input = "";
				graph.load(FILENAME);
			}
			else if(MODE == "TEMPLATE")
			{
				input = "";
				graph.save(FILENAME,true);
			}
			FILENAME = "";
			MODE = "NORMAL";
		}
		else if(key == 8)
		{
			if(FILENAME.size() != 0)
			{
				FILENAME.resize(FILENAME.size() - 1);
			}
		}
		else if(key == 27)
		{
			FILENAME = "";
			MODE = "NORMAL";
			input = "";
		}
		else if(key != 13)
		{
			FILENAME += key;
		}
	}
	else if(MODE == "INPUT")
	{
		//Enter Key: Check what function is currently in progress and compute appropriately
		if(key == 13)
		{
			vector<Node>* nodes = graph.getNodes();
			//add node data
			if(inputFunc == 1)
			{
				info = input.substr(17, string::npos);	
				input = "Enter Node Tags Separated by Commas: ";
				inputFunc = 2;
			}
			//add node tags
			else if(inputFunc == 2)
			{
				input = input.substr(37, string::npos);
				cout << points.back().getX() << ", " << points.back().getY() << endl;
				graph.addNode(info, split(input, ',', tags), points.back().getX(), points.back().getY());
				firstNode = graph.getNodes()->back().getIndex();
				MODE = "NORMAL";
				input = "";
				tags.clear();
				inputFunc = 0;
			}
			//add edge
			else if(inputFunc == 3)
			{
				input = input.substr(21, string::npos);
				cout << firstNode << endl;
				cout << "Adding Edge from " << firstNode << " to " << pn << endl;
				cout << "Relation: " << input << endl;
				graph.addEdge(firstNode, pn, input);
				firstNode = -1;
				pn = -1;

				MODE = "NORMAL";
				input = "";
				inputFunc = 0;
			}
			//edit node data
			else if(inputFunc == 4)
			{
				input = input.substr(16, string::npos);
				if(input != "")
				{
					(*nodes)[pn].setInformation(input);
					graph.printGraph();
				
				}

				inputFunc = 5;
				input = "Add Node Tags: " + (*nodes)[pn].printTags();
			}
			//edit node tags
			else if (inputFunc == 5)
			{
				input = input.substr(15, string::npos);
				tags = split(input, ',', tags);
				(*nodes)[pn].setTags(tags);

				MODE = "NORMAL";
				input = "";
				pn = -1;
				inputFunc = 0;
				firstNode = -1;
				tags.clear();
			}
		}
		//backspace removes characters from input buffer
		else if(key == 8)
		{
			if(input.substr(input.size()-2, string::npos) != ": ")
			{
				input.resize(input.size() - 1); 
			}
		}
		//escape exits INPUT mode
		else if(key == 27)
		{
			MODE = "NORMAL";
			input = "";
			inputFunc = 0;
			tags.clear();
			firstNode = -1;
			pn = -1;
		}
		//add other keys to input buffer
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
				FILENAME = "";
				MODE = "SAVING";
				input = "Enter filename: ";
				break;
			case 'l':
				FILENAME = "";
				MODE = "LOADING";
				input = "Enter filename: ";
				break;
			case 't':
				FILENAME = "";
				MODE = "TEMPLATE";
				input = "Enter template name: ";
				break;
			default:
				break;
		}
	}
}

//mouse function
void mouseControl(int button, int state, int x, int y)
{
	bool buttFlag = false;
	vector<Node>* nodes = graph.getNodes();
	
	//check if in button area
	if(x >= WIDTH - 200)
	{
		buttFlag = true;
	}
	
	if(buttFlag)
	{
		//check for button clicks
		int left, right, top, bottom;
		if(state == GLUT_DOWN)
		{
			for(int i = 0; i < demButtons.size(); i++)
			{
				left = WIDTH - 185 + 90*(demButtons[i].getCol() - 1);
				right = left + 80;
				top = HEIGHT - 15 - 40*(demButtons[i].getRow() - 1);
				bottom = top - 30;
		
				if(x < right && x > left && HEIGHT - y < top && HEIGHT - y > bottom)
				{
					if(demButtons[i].getName() == "Tiger")
					{
						graph.saveSortedGraph();
					}
				}
			}
		}
	}
	else
	{
		// Store the currentPoint in the points vector when left button is released.
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{	
			MODE = "NORMAL";
			input = "";
			Point currentPoint = Point(x, HEIGHT - y, false);
			points.push_back(currentPoint);
		
			//check if we picked a node
			pn = pickNode(currentPoint.getX(), currentPoint.getY());
			if(pn != -1)
			{
				    input = string("Data: ") + string((*nodes)[pn].getInformation()) + string(", Tags: ") + (*nodes)[pn].printTags();
				firstNode = pn;
			}
			else if(collisionFree(x, HEIGHT - y))
			{
				MODE = "INPUT";
				input = "Enter Node Data: ";
				inputFunc = 1;
			}
		}
		else if (state == GLUT_UP)
		{
			Point currentPoint = Point(x, HEIGHT - y, true);
			points.push_back(currentPoint);	
			pn = pickNode(currentPoint.getX(), currentPoint.getY());
		
			if(button == GLUT_LEFT_BUTTON)
			{
				if(pn != -1 && firstNode != -1 && pn != firstNode && !(*nodes)[firstNode].edgeExists(pn))
				{
					MODE = "INPUT";
					input = "Enter Edge Relation: ";
					inputFunc = 3;
				}
			}
			else if(button == GLUT_RIGHT_BUTTON)
			{
				if(pn != -1)
				{
					MODE = "INPUT";
					input = "Edit Node Data: ";
					inputFunc = 4;
				}	
			}
		}
	}
}

void opengl_init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(0, 0);
	gluOrtho2D(0, 500, 0, 500);
	glutCreateWindow("Babel Graph");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	MODE = "NORMAL";
	tags.clear();
	vector<string>test;
	glEnable(GL_BLEND);
	cout << "Left click in empty space to create a node. Left click and drag from one node to another to create an edge between them." << endl;
	
	//hacky solution to opengl text rendering problem
	string s = "data";
	vector<string> ss;
	graph.addNode(s, ss, -50, -50);
	
	//buttons delcaration
	demButtons.push_back(Button(1,1,"Tiger"));
	demButtons.push_back(Button(1,2,"Eye"));
	demButtons.push_back(Button(2,1,"Plow"));

	glutMainLoop();
}

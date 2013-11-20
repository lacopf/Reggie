#include <iostream>

using namespace std;

#include "button.h"

///global variables
Graph graph;
int cursorBlinkFrame = 0;
bool ACTIVE_CTRL = false;
string input = "";
vector<Point> points;
int HEIGHT = 800;
int WIDTH = 1200;
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
	while (std::getline(ss, item, delim)) 
	{
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
		if(dist((*nodes)[i].getPoint(), x, y) <= RADIUS*2 && i != firstNode)
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
	
	left = WIDTH - 385 + 190*(column - 1);
	right = left + 180;
	top = HEIGHT - 15 - 40*(row - 1);
	bottom = top - 30;	
	
	glColor3f(37.0/255.0, 213.0/255.0, 0.0/255.0);
	glBegin(GL_QUADS);
		glVertex2f(left, top);
		glVertex2f(left, bottom);
		glVertex2f(right, bottom);
		glVertex2f(right, top);
	glEnd();
	
	glColor3f(255.0/255.0, 255.0/255.0, 255.0/255.0);
	writeString(left + 5 + (180 - 10*name.length())/2, bottom + 8, GLUT_BITMAP_HELVETICA_18, name.c_str());
}

//menu drawing function
void drawMenu()
{
	glColor3f(0.0/255.0, 160.0/255.0, 138.0/255.0);
	glBegin(GL_QUADS);
		glVertex2f(WIDTH - 400, 0);
		glVertex2f(WIDTH, 0);
		glVertex2f(WIDTH, HEIGHT);
		glVertex2f(WIDTH - 400, HEIGHT);
	glEnd();
	
	glColor3f(16.0/255.0, 73.0/255.0, 169.0/255.0);
	glBegin(GL_QUADS);
		glVertex2f(WIDTH - 390, 10);
		glVertex2f(WIDTH - 10, 10);
		glVertex2f(WIDTH - 10, HEIGHT - 10);
		glVertex2f(WIDTH - 390, HEIGHT - 10);
	glEnd();
	
	for(int i = 0; i < demButtons.size(); i++)
	{
		drawButton(demButtons[i].getName(), demButtons[i].getRow(), demButtons[i].getCol());
	}
	
	//draw typing area
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(WIDTH - 385, 15);
		glVertex2f(WIDTH - 15, 15);
		glVertex2f(WIDTH - 15, 105);
		glVertex2f(WIDTH - 385, 105);
	glEnd();
	
	//actual text in area
	if(MODE == "SAVING FILE" || MODE == "LOADING FILE" || MODE == "SAVING TEMPLATE" || MODE == "LOADING TEMPLATE" || MODE == "INPUT")
	{	
		glColor3f(37.0/255.0, 213.0/255.0, 0.0/255.0);
		writeString(WIDTH - 380, 85, GLUT_BITMAP_9_BY_15, MODE.c_str());
		
		string super = MESSAGE;
		while(super.length() < 120)
		{
			super = super + " ";
		}
		string sub[3] = {"", "", ""};
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 40; j++)
			{
				sub[i] = sub[i] + super[40*i+j];
			}
		}
		writeString(WIDTH - 380, 65, GLUT_BITMAP_9_BY_15, sub[0].c_str());
		writeString(WIDTH - 380, 45, GLUT_BITMAP_9_BY_15, sub[1].c_str());
		writeString(WIDTH - 380, 25, GLUT_BITMAP_9_BY_15, sub[2].c_str());
	}
	else if(MODE == "NORMAL" || MODE == "MESSAGE")
	{		
		glColor3f(37.0/255.0, 213.0/255.0, 0.0/255.0);
		
		string super = MESSAGE;
		while(super.length() < 160)
		{
			super = super + " ";
		}
		string sub[4] = {"", "", "", ""};
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 40; j++)
			{
				sub[i] = sub[i] + super[40*i+j];
			}
		}
		writeString(WIDTH - 380, 85, GLUT_BITMAP_9_BY_15, sub[0].c_str());
		writeString(WIDTH - 380, 65, GLUT_BITMAP_9_BY_15, sub[1].c_str());
		writeString(WIDTH - 380, 45, GLUT_BITMAP_9_BY_15, sub[2].c_str());
		writeString(WIDTH - 380, 25, GLUT_BITMAP_9_BY_15, sub[3].c_str());
	}
	
}

//display function
void drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	//writeString(10, 10, GLUT_BITMAP_9_BY_15, input.c_str());
	graph.draw();
	
	if(MODE == "SAVING FILE" || MODE == "LOADING FILE" || MODE == "SAVING TEMPLATE" || MODE == "LOADING TEMPLATE")
	{
		cursorBlinkFrame++;
		if(cursorBlinkFrame % 30 < 15)
		{
			MESSAGE = "Enter filename: " + FILENAME + "|";
		}
		else
		{
			MESSAGE = "Enter filename: " + FILENAME + "";
		}
	}
	else if(MODE == "INPUT")
	{
		cursorBlinkFrame++;
		if(cursorBlinkFrame % 30 < 15)
		{
			MESSAGE = input + "|";
		}
		else
		{
			MESSAGE = input + "";
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
	if(MODE == "SAVING FILE" || MODE == "LOADING FILE" || MODE == "SAVING TEMPLATE" || MODE == "LOADING TEMPLATE")
	{
		if(key == 13 && FILENAME != "")
		{
			if(MODE == "SAVING FILE")
			{
				MESSAGE = "";
				graph.save(FILENAME,false);			
			}
			else if(MODE == "LOADING FILE")
			{
				MESSAGE = "";
				graph.load(FILENAME,false);
			}
			else if(MODE == "SAVING_TEMPLATE")
			{
				MESSAGE = "";
				graph.save(FILENAME,true);
			}
			else if(MODE == "LOADING_TEMPLATE")
			{
				MESSAGE = "";
				graph.load(FILENAME,true);
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
			MESSAGE = "";
		}
		else if(key != 13)
		{
			FILENAME += key;
		}
	}
	
	else if(MODE == "INPUT")
	{
		//Enter Key: Check what function is currently in progress and compute appropriately
		if(key == 13)//enter key
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
				//cout << points.back().getX() << ", " << points.back().getY() << endl;
				graph.addNode(info, split(input, ',', tags), points.back().getX(), points.back().getY());
				firstNode = -1;//graph.getNodes()->back().getIndex();
				MODE = "NORMAL";
				input = "";
				MESSAGE = "";
				tags.clear();
				inputFunc = 0;
			}
			//add edge
			else if(inputFunc == 3)
			{
				input = input.substr(21, string::npos);
				//cout << firstNode << endl;
				//cout << "Adding Edge from " << firstNode << " to " << pn << endl;
				//cout << "Relation: " << input << endl;
				graph.addEdge(firstNode, pn, input);
				firstNode = -1;
				pn = -1;

				MODE = "NORMAL";
				input = "";
				MESSAGE = "";
				inputFunc = 0;
			}
			//edit node data
			else if(inputFunc == 4)
			{
				input = input.substr(16, string::npos);
				if(input != "")
				{
					(*nodes)[pn].setInformation(input);
					//graph.printGraph();
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
	if(x >= WIDTH - 400 || x < 0 || y < 0 || y > HEIGHT)
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
				left = WIDTH - 385 + 190*(demButtons[i].getCol() - 1);
				right = left + 180;
				top = HEIGHT - 15 - 40*(demButtons[i].getRow() - 1);
				bottom = top - 30;	
		
				if(x < right && x > left && HEIGHT - y < top && HEIGHT - y > bottom)
				{
					//cout << demButtons[i].getName() << endl;
					if(demButtons[i].getName() == "Load File")
					{
						MODE = "LOADING FILE";
						FILENAME = "";
						//graph.load("temp", false);
					}
					else if(demButtons[i].getName() == "Save File")
					{
						MODE = "SAVING FILE";
						FILENAME = "";
						//graph.save("temp",false);
					}
					else if(demButtons[i].getName() == "Load Template")
					{
						MODE = "LOADING TEMPLATE";
						FILENAME = "";
						//graph.load("temp", true);
					}
					else if(demButtons[i].getName() == "Save Template")
					{
						MODE = "SAVING TEMPLATE";
						FILENAME = "";
						//graph.save("temp",true);
					}
					else if(demButtons[i].getName() == "Topological Sort")
					{
						graph.saveSortedGraph();
					}
					else if(demButtons[i].getName() == "Export Calendar")
					{
						//export calendar file
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
				MESSAGE = string("Data: ") + string((*nodes)[pn].getInformation()) + string(", Tags: ") + (*nodes)[pn].printTags();
				firstNode = pn;
			}
			else if(collisionFree(x, HEIGHT - y))
			{
				MODE = "INPUT";
				input = "Enter Node Data: ";
				inputFunc = 1;
				firstNode = -1;
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
				else if(firstNode != -1 && collisionFree(x, HEIGHT - y))
				{
					(*graph.getNodes())[firstNode].move(x, HEIGHT - y);
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
	glutInitWindowSize(WIDTH, HEIGHT);
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
	//cout << "Left click in empty space to create a node. Left click and drag from one node to another to create an edge between them." << endl;
	MESSAGE = "Left click in empty space to create a   node. Left click and drag from one node to another to create an edge between    them.";
	MODE = "MESSAGE";
	
	//buttons declaration
	demButtons.push_back(Button(1,1,"Load File"));
	demButtons.push_back(Button(1,2,"Save File"));
	demButtons.push_back(Button(2,1,"Load Template"));
	demButtons.push_back(Button(2,2,"Save Template"));
	demButtons.push_back(Button(3,1,"Topological Sort"));
	demButtons.push_back(Button(3,2,"Export Calendar"));

	glutMainLoop();
}

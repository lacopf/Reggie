#ifndef _POINT
#define _POINT

#include "point.h"

class Point
{
	private:
		double x;//x coordinate of the click
		double y;//y coordinate of the click
		bool down;//if it was down click
	  
	public:
		Point(double i, double j, bool press)//constructor
		{
			x = i;
			y = j;
			down = press;
		}
		double getX()//get x coordinate
		{
			return x;
		}
		double getY()//get y coordinate
		{
			return y;
		}
		bool getDown()//get down and boogie
		{
			return down;
		}
};

#endif

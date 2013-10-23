#ifndef _point_h_
#define _point_h_

#include "point.h"

class Point
{
	private:
		int x;
		int y;
		bool down;
	  
	public:
		Point(int i, int j, bool press)
		{
			x = i;
			y = j;
			down = press;
		}
		int getX()
		{
			return x;
		}
		int getY()
		{
			return y;
		}
		bool getDown()
		{
			return down;
		}
};

#endif

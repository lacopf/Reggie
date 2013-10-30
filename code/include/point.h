#ifndef _POINT
#define _POINT

class Point
{
	private:
		double x;//x coordinate of the click
		double y;//y coordinate of the click
		bool down;//if it was down click
	  
	public:
		Point()//default constructor
		{
			x = -1;
			y = -1;
			down = false;
		}
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

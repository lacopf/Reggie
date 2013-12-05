#ifndef _POINT
#define _POINT

class Point
{
	private:
		int x;//x coordinate of the click
		int y;//y coordinate of the click
		bool down;//if it was down click

	public:
		inline Point()//default constructor
		{
			x = -1;
			y = -1;
			down = false;
		}
		inline Point(double i, double j, bool press)//constructor
		{
			x = i;
			y = j;
			down = press;
		}
		inline int getX()//get x coordinate
		{
			return x;
		}
		inline int getY()//get y coordinate
		{
			return y;
		}
		inline bool getDown()//get down and boogie
		{
			return down;
		}

		inline void move(int newX, int newY)//lets you move a node after you've already placed it
		{
			x = newX;
			y = newY;
		}
};

#endif

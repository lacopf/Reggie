#ifndef _POINT
#define _POINT

class Point
{
	private:
		int x;//x coordinate of the click
		int y;//y coordinate of the click
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
		
		//get x coordinate
		inline int getX(){return x;}
		
		//get y coordinate
		inline int getY(){return y;}
		
		//get down and boogie
		inline bool getDown(){return down;}

		inline void move(int newX, int newY)//lets you move a node after you've already placed it
		{
			x = newX;
			y = newY;
		}
};

#endif

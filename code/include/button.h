#ifndef _BUTTON
#define _BUTTON

//helps with managing buttons on the window
//stores a button's location and name
class Button
{
	private:
		int row;
		int column;
		string name;
	  
	public:
		Button(int i, int j, string id)//constructor
		{
			row = i;
			column = j;
			name = id;
		}
		int getRow()//get row coordinate
		{
			return row;
		}
		int getCol()//get name coordinate
		{
			return column;
		}
		string getName()//get name
		{
			return name;
		}
};

#endif

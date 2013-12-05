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
		
		//get row coordinate
		inline int getRow(){return row;}
		
		//get name coordinate
		inline int getCol(){return column;}
		
		//get name
		inline string getName(){return name;}
};

#endif

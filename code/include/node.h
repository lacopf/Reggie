#include <iostream>
#include <string>
using namespace std;

public Node{
private:
  string information;
  int index;
  Node* parent;
  
public:
  int inline get_index() {return index;}
  string inline get_information() {return information;}
  Node* inline get_parent() {return parent;}
  
  Node();
  Node(string info, int ind, Node* parent);
  
  

};

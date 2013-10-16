#include "node.h"

public Edge{
  private:
  Node* node1;
  Node* node2;
  string realtion;
  
  public:
  Edge();
  Edge(Node* n1, Node* n2, string relation);
  
  string get_relation() {return relation;}
  
  
};

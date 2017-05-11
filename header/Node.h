/*
  Group Name: NxWorries
  Group Members: Maxwell Mahlaba
					  Mongezi Nene
					  Simangaliso Mlangeni
  315 Mini Project
  Node header file
*/

#ifndef NODE_
#define NODE_H
#include <vector>

using namespace std;

class Node{

	vector<Node*>* neighbours; 
	vector<int>* directions;
	
	public:
		static int encode(const int& );
        Node(const int& ,const int&,const int&);
		int getIndex();
        int getX();
        int getY();
		void choose(Node*& ,int& );
        void choosePredator(Node*& ,int&);//Declaration of the method to choose path for predator
		~Node();
		void assignNeighbours(vector<Node*>*const& ,vector<int>*const& );
   
   private:
      const int NT;//Node type
      const int INDEX;
      const int X_pos;
      const int Y_pos;

};
#endif // NODE_H

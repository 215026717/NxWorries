/*
  Group Name: NxWorries
  Group Members: Maxwell Mahlaba
					  Mongezi Nene
					  Simangaliso Mlangeni
  315 Pacman Project
  Node file
*/

#include "Node.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int Node::encode(const int& index){    
   if(index%2==1)
      return 1;//edge
   else if(index==4)
      return 2;//centre
   else
      return 0;//corner
}

Node::Node(const int& index,const int &x,const int &y):NT(encode(index)),INDEX(index),X_pos(x),Y_pos(y){}

int Node::getIndex(){
	return INDEX;
} 
int Node::getX(){
    return X_pos;
}
int Node::getY(){
    return Y_pos;
}
void Node::assignNeighbours(vector<Node*>*const& nbvp,vector<int>*const& nbdvp){
   neighbours=nbvp;
   directions=nbdvp;
}

void Node::choose(Node*& nb,int& d){
   int r=rand()%neighbours->size();
   nb = neighbours->at(r);
   d = directions->at(r);
}

//chooses the next neighbour and direction for the predator
void Node::choosePredator(Node*& nb,int& d){

    int r=rand()%neighbours->size();
    nb = neighbours->at(r);

    d = directions->at(r);

 }

Node::~Node(){
	delete neighbours;
	delete directions;
}

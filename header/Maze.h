
/*
  Group Name: NxWorries
  Group Members: Maxwell Mahlaba
                      Mongezi Nene
                      Simangaliso Mlangeni
  315 Pacman Project
  Maze header file
*/

#ifndef MAZE_H
#define MAZE_H
#include "Node.h"
#include <QGraphicsEllipseItem>


using namespace std;

class Maze{
    int nextPos;
    int nextDirection;
    static const int m = 27,n = 15;
    int sz[m*n];
    int x,y;
    vector<int> exclude;



    public:
    vector<Node*>* nodeVector;
    bool inExclude(int);
    int neigh[m*n][4];
    int direc[m*n][4];
    void sec();
    int chooser;
    Node* predator;
    Node* prey;
    Node* predatorRed;
    Node* predatorBlue;
    Node* predatorGreen;

      void findNextPos(Node*&);
        void spaceE(int);
        void space(int,int,int e[]);
        void corners();
        void edges(int,int,int e[]);
        void centres(int e[]);
        Maze();
        void navigatePredator();

        void navigateRed();
        void navigateBlue();
        void navigateGreen();

        void navigatePrey();
        bool collide();
        ~Maze();

};
#endif //Maze.h

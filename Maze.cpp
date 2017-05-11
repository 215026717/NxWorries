/*
  Group Name: NxWorries
  Group Members: Maxwell Mahlaba
                      Mongezi Nene
                      Simangaliso Mlangeni
  315 Pacman Project
  Maze file
*/

#include "Maze.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

//Algorith for predator to find prey
void Maze::findNextPos(Node*& predator){
    nextPos = 0;
    for(int i=0;i<4;i++){
        if(prey->getIndex()>predator->getIndex()){
            if(neigh[predator->getIndex()][i] == -1){
                continue;
            }
            else if(neigh[predator->getIndex()][i] != -1 && ( prey->getIndex()<neigh[predator->getIndex()][i])&&(neigh[predator->getIndex()][i] <predator->getIndex() ) && neigh[predator->getIndex()][i]>nextPos){
                nextPos = i;
            }
            else if(neigh[predator->getIndex()][i] != -1 && ( predator->getIndex()<neigh[predator->getIndex()][i] ) && (neigh[predator->getIndex()][i]<prey->getIndex() ) && neigh[predator->getIndex()][i]>nextPos){
                nextPos = i;
            }
            }
            else{
                if(neigh[predator->getIndex()][i] == -1){
                    continue;
            }
            else if(neigh[predator->getIndex()][i] != -1 && ( prey->getIndex()<neigh[predator->getIndex()][i] ) && (neigh[predator->getIndex()][i]<predator->getIndex() ) && neigh[predator->getIndex()][i]<nextPos){
                nextPos = i;
            }
            else if(neigh[predator->getIndex()][i] != -1 && ( predator->getIndex()<neigh[predator->getIndex()][i] ) && (neigh[predator->getIndex()][i]<prey->getIndex() ) && neigh[predator->getIndex()][i]<nextPos){
                nextPos = i;
            }
        }
    }
}

//for last neighbour and direction of Edges
void Maze::spaceE(int a){
    neigh[a][3] = -1;
    direc[a][3] = -1;
}

//for last two neighbour's and direction's of centres
void Maze::space(int a, int b,int cIn[]){
        neigh[cIn[a]][b] = -1;
        direc[cIn[a]][b++] = -1;
        neigh[cIn[a]][b] = -1;
        direc[cIn[a]][b++] = -1;
    }

//finds the neighbours and directions for corners
void Maze::corners(){
         int cIndex[4] = {0,(m-1),m*(n-1),(m*n)-1};

         for(int i=0;i<4;i++){
            int j = 0;

            sz[cIndex[i]] = 2;

            if(i==0){
               direc[cIndex[i]][j] = 0;
               neigh[cIndex[i]][j++] =cIndex[i]+1;
               direc[cIndex[i]][j] = 3;
               neigh[cIndex[i]][j++] =(m+m)-1;
               space(i,j,cIndex);
            }

            else if(i==1){

               neigh[cIndex[i]][j] = cIndex[i]-1;
               direc[cIndex[i]][j++] = 2;

               neigh[cIndex[i]][j] = cIndex[i]+1;
               direc[cIndex[i]][j++] = 3;
               space(i,j,cIndex);

            }
            else if(i==2){
               direc[cIndex[i]][j] = 0;
               neigh[cIndex[i]][j++] = cIndex[i]+1;

               direc[cIndex[i]][j] = 1;
               neigh[cIndex[i]][j++] = cIndex[i]-1;

               space(i,j,cIndex);
            }
            else if(i==3){
               direc[cIndex[i]][j] = 1;
               neigh[cIndex[i]][j++] = cIndex[i]-((2*m)-1);

               direc[cIndex[i]][j] = 0;
               neigh[cIndex[i]][j++] = cIndex[i]-1;

               space(i,j,cIndex);
           }
      }

    }

//finds the neighbours and directions for corners
void Maze::edges(int counter2,int q,int theList[]){
         //For Edges
         for(int i=0;i<(m-2);i++){
            theList[i] = counter2;
            counter2 += 2;
         }

      //upper edges

         for(int i=1;i<=(m-2);i++){

                sz[i]=3;//sz

            neigh[i][0] = i + 1;
            direc[i][0] = 0;

            neigh[i][1] = i-1;
            direc[i][1] = 2;

            neigh[i][2] = i+theList[q--];
            direc[i][2] = 3;
            spaceE(i);
         }

      //lower edges
         int counter = 0;
         for(int i=(m*(n-1))+1 ;i<((m*n)-1);i++){
                if(m%2==0){//even m

                        sz[i] = 3;

                       neigh[i][0] = i-1;
                    direc[i][0] = 0;

                    neigh[i][1] = i-theList[counter];
                    direc[i][1] = 1;

                    neigh[i][2] = i+1;
                    direc[i][2] = 2;

                    spaceE(i);

                        counter++;
                }
                else{//odd m

                        sz[i] = 3;//sz

                        neigh[i][0] = i+1;
                    direc[i][0] = 0;

                    neigh[i][1] = i-theList[counter];
                    direc[i][1] = 1;

                        neigh[i][2] = i-1;
                    direc[i][2] = 2;

                    spaceE(i);
                        counter++;


                }
         }


      //side edges
         int sign1 = 1;
         int sign2 = 3;
         char sign3 = '-';//up
        char sign4 = '+';//down

         int edge[2] = {-1,0};
         for(int i=0;i<n-1;i++){
            edge[0] += m;
            edge[1] += m;

            for(int j=0;j<2;j++){

               int index = edge[j];
               if(index == m-1 || index == (m*(n-1)) || index==((m*n)-1)){
                  continue;
               }

               else if(index == 189 || index == 215){

                   sz[index] = 4;//sz

                   if(index==189){


                       neigh[index][0] = 215;
                       direc[index][0] = 0;

                       neigh[index][1] = -1;
                       direc[index][1] = -1;

                       neigh[index][2] = 190;
                       direc[index][2] = 2;

                       spaceE(index);

                   }
                   else{
                       neigh[index][0] = 214;
                       direc[index][0] = 0;

                       neigh[index][1] = -1;
                       direc[index][1] = -1;

                       neigh[index][2] = 189;
                       direc[index][2] = 2;

                       spaceE(index);

                   }

               }

               else{

                        sz[index] = 4;//sz

                        if(sign1==1){

                            if(sign2 == 3 && sign4 == '+'){//this


                                neigh[index][2] = (inExclude(index + (m+m)-1))? -1: index + (m+m)-1;
                        direc[index][2] = (inExclude(index + (m+m)-1))? -1: 3;

                        neigh[index][0] = (inExclude(index - 1))? -1: index - 1;
                            direc[index][0] = (inExclude(index - 1))? -1: 1;

                                sign1 = 0;


                                neigh[index][1] = (inExclude(index+1))? -1: index+1;
                         direc[index][1] = (inExclude(index+1))? -1: 2;
                        spaceE(index);

                         sign4 = '-';
                         sign2 = 2;
                                continue;
                    }

                      else if(sign2==3 && sign4=='-'){//this

                                neigh[index][2] = (inExclude(index + (m+m)-1))? -1: index + (m+m)-1;
                        direc[index][2] = (inExclude(index + (m+m)-1))? -1: 3;

                        neigh[index][0] = (inExclude(index + 1))? -1: index + 1;
                        direc[index][0] = (inExclude(index + 1))? -1: 0;

                                sign1 = 0;


                                neigh[index][1] = (inExclude(index-1))? -1:index-1;
                         direc[index][1] = (inExclude(index-1))? -1: 1;

                         spaceE(index);

                         sign4 = '+';
                         sign2 = 2;
                                continue;
                      }

                  }
                  else if(sign1==0){

                      if(sign2 == 2 && sign3 == '+'){//this

                            neigh[index][0] = index - ((m+m)-1);
                         direc[index][0] = 1;

                         neigh[index][1] = index - 1;
                         direc[index][1] = 2;

                        sign1 = 1;

                                neigh[index][2] = index+1;
                         direc[index][2] = 3;
                         spaceE(index);

                         sign3 = '-';
                         sign2 = 3;
                                continue;
                      }

                      else if(sign2 == 2 && sign3 == '-'){//this

                                neigh[index][1] = index - ((m+m)-1);
                        direc[index][1] = 1;

                        neigh[index][2] = index + 1;
                        direc[index][2] = 3;

                        sign1 = 1;

                                neigh[index][0] = index-1;
                         direc[index][0] = 0;

                         spaceE(index);
                         sign3 = '+';
                         sign2 = 3;
                                continue;
                      }
                  }
               }
            }
         }
    }

//finds the neighbours and directions for centres
void Maze::centres(int theList[]){
      //For Centers
         int start = 1;
         int end = 0;

         for(int i=1;i<n-1;i++){
            int counter1 = 0;
            int counter4 = m-3;
            start += m;
            end = start +(m-2);
            for(int j=start;j<end;j++){
                int size = 4;

                if(i%2==0){

                  size = 4;

                  neigh[j][0] = (inExclude(j+1))? -1 : j+1 ;
                  direc[j][0] = (inExclude(j+1))? -1 : 0;
                  //size += (inExclude(j+1))? 0 : 1;

                  neigh[j][1] = (inExclude(j-theList[counter1]))? -1 : j-theList[counter1];
                  direc[j][1] = (inExclude(j-theList[counter1++]))? -1 : 1;
                  //size += (inExclude(j-theList[counter1++]))? 0 : 1;

                  neigh[j][2] = (inExclude(j-1))? -1 : j-1;
                  direc[j][2] = (inExclude(j-1))? -1 : 2;
                  //size += (inExclude(j-1))? 0 : 1;


                  neigh[j][3] = (inExclude(j+theList[counter4]))? -1 :j+theList[counter4];
                  direc[j][3] = (inExclude(j+theList[counter4--]))? -1 :3;
                  //size += (inExclude(j+theList[counter4--]))? 0 : 1;

                  sz[j]= size;

               }
               else{
                  size = 4;
                  neigh[j][0] = (inExclude(j-1))? -1 : j-1;
                  direc[j][0] = (inExclude(j-1))? -1 : 0;
                  neigh[j][1] = (inExclude(j-theList[counter1]))? -1 : j-theList[counter1];
                  direc[j][1] = (inExclude(j-theList[counter1++]))? -1 : 1;
                  neigh[j][2] = (inExclude(j+1))? -1 : j+1;
                  direc[j][2] = (inExclude(j+1))? -1 : 2;
                  neigh[j][3] = (inExclude(j+theList[counter4]))? -1 : j+theList[counter4];
                  direc[j][3] = (inExclude(j+theList[counter4--]))? -1 : 3;
                  sz[j] = size;
               }

            }

         }
         neigh[204][0] = -1;
         direc[204][0] = -1;
         neigh[204][1] = -1;
         direc[204][1] = -1;
         neigh[204][2] = -1;
         direc[204][2] = -1;
         neigh[204][3] = 227;
         direc[204][3] = 3;
         neigh[206][1] = -1;
         direc[206][1] = -1;
         neigh[206][2] = -1;
         direc[206][2] = -1;
         neigh[206][3] = 225;
         direc[206][3] = 3;
         neigh[225][1] = 206;
         direc[225][1] = 1;
         neigh[225][2] = -1;
         direc[225][2] = -1;
         neigh[225][3] = -1;
         direc[225][3] = -1;
         neigh[226][1] = 205;
         direc[226][1] = 1;
         neigh[226][3] = -1;
         direc[226][3] = -1;
         neigh[227][1] = 204;
         direc[227][1] = 1;
         neigh[227][0] = -1;
         direc[227][0] = -1;
         neigh[227][3] = -1;
         direc[227][3] = -1;
         neigh[238][3] = 247;
         direc[238][3] = 3;
         neigh[291][0] = 292;
         direc[291][0] = 0;
         neigh[292][1] = 247;
         direc[292][1] = 1;
         neigh[211][1] = 166;
         direc[211][1] = 1;
         neigh[157][3] = 166;
         direc[157][3] = 3;
         neigh[258][0] = 257;
         direc[258][0] = 0;
         neigh[282][1] = 257;
         direc[282][1] = 1;
         neigh[228][3] = 257;
         direc[228][3] = 3;
         neigh[230][3] = 255;
         direc[230][3] = 3;
         neigh[284][1] = 255;
         direc[284][1] = 1;
         neigh[232][3] = 253;
         direc[232][3] = 3;
         neigh[286][1] = 253;
         direc[286][1] = 1;
         neigh[234][3] = 251;
         direc[234][3] = 3;
         neigh[288][1] = 251;
         direc[288][1] = 1;
         //neigh[205][3] = -1;
         //direc[205][3] = -1;
      for(int i=0;i<(m*n);i++){
         vector<Node*>* nbvp = new vector<Node*>;
         vector<int>* nbdvp = new vector<int>;
         for(int j=0;j<sz[i];j++){

           if(neigh[i][j]==-1){
                continue;
           }

           else{
            nbvp->push_back(nodeVector->at(neigh[i][j]));
            //cout<<i<<endl;

           // pellets[i] = new QGraphicsEllipseItem(QRectF(1120,170,10,10));
            nbdvp->push_back(direc[i][j]);
           }
         }
         nodeVector->at(i)->assignNeighbours(nbvp,nbdvp);
      }
}


void Maze::sec(){
    for (int i=0 ;i<84;i++){
        exclude.push_back(i);
    }
    int start = 105;
    for(int w=0;w<3;w++){
        for (int i=0;i<6;i++){
            exclude.push_back(start++);
            }
        start += (m-5);
    }
    exclude.push_back(186);
    exclude.push_back(187);
    exclude.push_back(188);

    exclude.push_back(216);
    exclude.push_back(217);
    exclude.push_back(218);

    int start2 = 240;

    for(int w=0;w<3;w++){
        for (int i=0;i<6;i++){
            exclude.push_back(start2++);
            }
        start += (m-5);
    }
    for (int i=321;i<405;i++){
        exclude.push_back(i);
    }

    //row one
    exclude.push_back(84);
    exclude.push_back(86);
    exclude.push_back(88);
    exclude.push_back(89);
    exclude.push_back(90);
    exclude.push_back(91);
    exclude.push_back(92);
    exclude.push_back(94);
    exclude.push_back(100);
    exclude.push_back(101);
    exclude.push_back(102);
    exclude.push_back(104);

    //row two
    exclude.push_back(117);
    exclude.push_back(118);
    exclude.push_back(127);

    //row three
    exclude.push_back(132);
    exclude.push_back(136);
    exclude.push_back(140);
    exclude.push_back(142);
    exclude.push_back(144);
    exclude.push_back(145);
    exclude.push_back(146);
    exclude.push_back(147);
    exclude.push_back(148);
    exclude.push_back(150);
    exclude.push_back(151);
    exclude.push_back(152);
    exclude.push_back(154);
    exclude.push_back(155);
    exclude.push_back(156);
    exclude.push_back(158);

    //row four
    exclude.push_back(165);
    exclude.push_back(167);
    exclude.push_back(175);
    exclude.push_back(177);
    exclude.push_back(179);
    exclude.push_back(183);
    exclude.push_back(185);

    //row five

    exclude.push_back(194);
    exclude.push_back(195);
    exclude.push_back(196);
    exclude.push_back(198);
    exclude.push_back(200);
    exclude.push_back(202);
    exclude.push_back(204);
    exclude.push_back(205);
    exclude.push_back(206);
    exclude.push_back(208);
    exclude.push_back(209);
    exclude.push_back(210);

    //row six
    exclude.push_back(219);
    exclude.push_back(221);
    exclude.push_back(222);
    exclude.push_back(223);
    exclude.push_back(225);
    exclude.push_back(226);
    exclude.push_back(227);
    exclude.push_back(229);
    exclude.push_back(233);
    exclude.push_back(235);
    exclude.push_back(236);
    exclude.push_back(237);
    exclude.push_back(239);

    //row seven
    exclude.push_back(246);
    exclude.push_back(248);
    exclude.push_back(249);
    exclude.push_back(250);
    exclude.push_back(252);
    exclude.push_back(254);
    exclude.push_back(256);
    exclude.push_back(262);
    exclude.push_back(263);
    exclude.push_back(264);
    exclude.push_back(266);

    //row eight
    exclude.push_back(272);
    exclude.push_back(279);
    exclude.push_back(281);
    exclude.push_back(285);


    //row nine
    exclude.push_back(300);
    exclude.push_back(302);
    exclude.push_back(303);
    exclude.push_back(304);
    exclude.push_back(306);
    exclude.push_back(307);
    exclude.push_back(308);
    exclude.push_back(310);
    exclude.push_back(312);
    exclude.push_back(313);
    exclude.push_back(314);
    exclude.push_back(316);
    exclude.push_back(317);
    exclude.push_back(318);
    exclude.push_back(320);
    exclude.push_back(294);

    exclude.push_back(160);
    exclude.push_back(159);
    exclude.push_back(294);
    exclude.push_back(295);
    exclude.push_back(296);
    exclude.push_back(297);
    exclude.push_back(298);
    exclude.push_back(299);
    exclude.push_back(267);
    exclude.push_back(268);
    exclude.push_back(269);
    exclude.push_back(270);
    exclude.push_back(271);


 }

bool Maze::inExclude(int x){
    //cout<<"this"<<endl;

    if(find(exclude.begin(), exclude.end(), x) != exclude.end()) {
        /* exclude contains x*/
        return true;
    }
    return false;

}

//Maze constructor
Maze::Maze(){
    chooser = 3;
    sec();
    int mazeSquared = m*n;
            x = 0;

            y = 0;
            int pos[m*n][2];
            int posCounter = 0;
            pos[posCounter][0] = x;
            pos[posCounter++][1] = y;

            for(int i=0;i<n;i++){
                if(i%2==0){
                    for(int j=0;j<(m-1);j++){
                        x += 50;
                        pos[posCounter][0] = x;
                        pos[posCounter++][1] = y;
                    }
                    y+=50;
                    if(posCounter<((m*n)-1)){
                        pos[posCounter][0] = x;
                        pos[posCounter++][1] = y;
                    }

                }
                else if(i%2==1){
                    for(int j=0;j<(m-1);j++){
                        x -= 50;
                        pos[posCounter][0] = x;
                        pos[posCounter++][1] = y;
                    }
                    y+=50;
                    if(posCounter<((m*n)-1)){
                        pos[posCounter][0] = x;
                        pos[posCounter++][1] = y;
                    }

                }

            }
    nodeVector = new vector<Node*>;
      for(int i=0;i<mazeSquared;i++){
         nodeVector->push_back(new Node(i,pos[i][0],pos[i][1]));
      }
      //int r = rand()%mazeSquared;
        int e;

        if (m % 2 == 1)
            e = (m*n) - 1;
        else
            e = m * (n - 1);

        cout<<"PREDATOR starting at "<<0<<endl;
        cout<<"PREY starting at "<<e<<endl;
        predator = nodeVector->at(274);
        prey = nodeVector->at(311);
        predatorRed = nodeVector->at(206);
        predatorBlue = nodeVector->at(205);
        predatorGreen = nodeVector->at(227);

        int theList[m-2];
      int counter2 = 3;
      int q = m-3;

      corners();
      edges(counter2,q,theList);

      centres(theList);

}


//navigates the predator
void Maze::navigatePredator(){
   int d;
    findNextPos(predator);
   predator->choosePredator(predator,d);
   switch(d){
      case 0: cout<<"predator going east to: "<<predator->getIndex()<<endl;
         break;
      case 1: cout<<"predator going north to: "<<predator->getIndex()<<endl;
         break;
      case 2: cout<<"predator going west to: "<<predator->getIndex()<<endl;
         break;
      case 3: cout<<"predator going south to: "<<predator->getIndex()<<endl;
         break;
   }
}

void Maze::navigateBlue(){
   int d;
    findNextPos(predatorBlue);
   predatorBlue->choosePredator(predatorBlue,d);
   switch(d){
      case 0: cout<<"predatorBlue going east to: "<<predatorBlue->getIndex()<<endl;
         break;
      case 1: cout<<"predatorBlue going north to: "<<predatorBlue->getIndex()<<endl;
         break;
      case 2: cout<<"predatorBlue going west to: "<<predatorBlue->getIndex()<<endl;
         break;
      case 3: cout<<"predator going south to: "<<predatorBlue->getIndex()<<endl;
         break;
   }
}

void Maze::navigateRed(){
   int d;
    findNextPos(predatorRed);
   predatorRed->choosePredator(predatorRed,d);
   switch(d){
      case 0: cout<<"predatorRed going east to: "<<predatorRed->getIndex()<<endl;
         break;
      case 1: cout<<"predatorRed going north to: "<<predatorRed->getIndex()<<endl;
         break;
      case 2: cout<<"predatorRed going west to: "<<predatorRed->getIndex()<<endl;
         break;
      case 3: cout<<"predatorRed going south to: "<<predatorRed->getIndex()<<endl;
         break;
   }
}

void Maze::navigateGreen(){
   int d;
    findNextPos(predatorGreen);
    //cout<<nextPos<<endl;
   predatorGreen->choosePredator(predatorGreen,d);
   switch(d){
      case 0: cout<<"predatorGreen going east to: "<<predatorGreen->getIndex()<<endl;
         break;
      case 1: cout<<"predatorGreen going north to: "<<predatorGreen->getIndex()<<endl;
         break;
      case 2: cout<<"predatorGreen going west to: "<<predatorGreen->getIndex()<<endl;
         break;
      case 3: cout<<"predatorGreen going south to: "<<predatorGreen->getIndex()<<endl;
         break;
   }
}

//navigates the prey
void Maze::navigatePrey(){
    int in = prey->getIndex();
    //cout<<"CHOOSER"<<chooser<<endl;
    if (direc[in][chooser] == chooser){
        prey = nodeVector->at(neigh[in][chooser]);
    }
}

//Checks when predator pos is equal to prey pos
bool Maze::collide(){
    if((predatorRed->getIndex()==prey->getIndex()) || (predatorBlue->getIndex()==prey->getIndex()) || (predatorGreen->getIndex()==prey->getIndex())){
        return 1;
    }
    return 0;
}

//destructor
Maze::~Maze(){
      for(int i=0;i<m*n;i++){
         delete nodeVector->at(i);
      }
      delete nodeVector;
}

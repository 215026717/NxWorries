/*
  Group Name: NxWorries
  Group Members: Maxwell Mahlaba
                      Mongezi Nene
                      Simangaliso Mlangeni
  315 Pacman Project
  Maze file
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Maze.h"
#include <iostream>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>

using namespace std;

Maze mz;
int spec1[8] = {103,93,85,176,178,301,309,319};
set<int> spec(spec1, spec1 + 8);
QFile file("scores");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new MyScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->installEventFilter(this);
    const QPixmap pm(":/images/pmaze.png");
    ui->graphicsView->setFixedSize(pm.width()+10-3,pm.height()+10-3);


    for(int i=0;i<27*15;i++){
        //if (i == 311)
         //   continue;

      if(i==166||i==257||i==255||i==253||i==251||i==247){
        pellets[i] = new QGraphicsEllipseItem(QRectF(mz.nodeVector->at(i)->getX()+20,mz.nodeVector->at(i)->getY()+20,10,10));
        pellets[i]->setBrush(QBrush(Qt::white));
        scene->addItem(pellets[i]);
      }
      else if(mz.inExclude(i)){
        continue;
      }
      else{
          pellets[i] = new QGraphicsEllipseItem(QRectF(mz.nodeVector->at(i)->getX()+20,mz.nodeVector->at(i)->getY()+20,10,10));
          pellets[i]->setBrush(QBrush(Qt::white));
          scene->addItem(pellets[i]);
      }
    }
    for (int i = 0; i < 8; i++){
        pellets[spec1[i]]->setRect(QRectF(mz.nodeVector->at(spec1[i])->getX()+15,mz.nodeVector->at(spec1[i])->getY()+15,20,20));

    }


    agent = new QGraphicsPixmapItem(QPixmap(":images/pacCU"));
    agent->setPos(600,550);
    scene->addItem(agent);

    agent1 = new QGraphicsPixmapItem(QPixmap(":images/pacOR"));
    agent1->setPos(1200,700);
    scene->addItem(agent1);

    agent2 = new QGraphicsPixmapItem(QPixmap(":images/pacOR"));
    agent2->setPos(1250,700);
    scene->addItem(agent2);

    agent3 = new QGraphicsPixmapItem(QPixmap(":images/pacOR"));
    agent3->setPos(1300,700);
    scene->addItem(agent3);

    green = new QGraphicsPixmapItem(QPixmap(":images/green"));
    green->setPos(550,350);
    scene->addItem(green);

    orange = new QGraphicsPixmapItem(QPixmap(":images/orange"));
    orange->setPos(500,350);
    scene->addItem(orange);

    darkred = new QGraphicsPixmapItem(QPixmap(":images/darkred"));
    darkred->setPos(450,350);
    scene->addItem(darkred);


    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

    off = true;
    hr = 0, mn = 0, sc = 0, d_1 = 0, d_2 = 0,d_3 = 0,d_4=0, GJ = 0,OJ = 0,DJ = 0;



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    int d = mz.prey->getIndex();
    if (event->key() == Qt::Key_Q){
        this->close();

    }
    if (event->key() == Qt::Key_P){
        if (mn == 1){
            consume();
            mn = 0;
        }
        if (d_2 == 3){
            QString ps;
            ps+=QString("Rules: Press P to start the game. Press P whenever you want to pause or restart the game. Press Q to quit the game and close window.");
            ui->label_2->setText(ps);
            ui->label_2->setTextFormat(Qt::RichText);
            d_2 += 1;
            d_4 = 0;
            //ppellets[282]->show();
            for (int i = 85;i<320;i++){

                if (eatP.count(i)!=0){
                    pellets[i]->show();
                    eatP.erase(i);
                }
            }
        }
        else
            pause();
        if (d_2 == 4){
            spec.insert(spec1, spec1 + 8);
            d_2 = 0;
            agent1->show();
            agent2->show();
            agent3->show();
        }
        bs = ui->lineEdit->text();
        ui->lineEdit->hide();
        //cout<< bs.toStdString()<<endl;
    }
    if (event->key() == Qt::Key_Up && mz.direc[d][1] == 1){
        mz.chooser = 1;
        //event->accept();
    }
    else if (event->key() == Qt::Key_Left && mz.direc[d][2] == 2){
        mz.chooser = 2;
    }
    else if (event->key() == Qt::Key_Down && mz.direc[d][3] == 3){
       mz.chooser = 3;
    }
    else if (event->key() == Qt::Key_Right && mz.direc[d][0] == 0){
        mz.chooser = 0;
    }

}

void MainWindow::tick(){
    if(timer->isActive()){
        if (mz.chooser == 0){
            agent->setPixmap(QPixmap(":images/pacOR"));
            //agent->show;
        }
        if (mz.chooser == 1){
            agent->setPixmap(QPixmap(":images/pacOU"));
            //agent->show;
        }
        if (mz.chooser == 2){
            agent->setPixmap(QPixmap(":images/pacOL"));
            //agent->show;
        }
        if (mz.chooser == 3){
            agent->setPixmap(QPixmap(":images/pacOD"));
            //agent->show;
        }
        sc++;
        QString qs;

        if (sc % 24 == 0){
            d_1+=50;
            d_3 = 0;
            green->setPixmap(QPixmap(":images/green"));
            darkred->setPixmap(QPixmap(":images/darkred"));
            orange->setPixmap(QPixmap(":images/orange"));
            OJ=0;
            DJ=0;
            GJ=0;
        }
        mz.navigatePrey();
        agent->setPos(mz.prey->getX(),mz.prey->getY());
        pellets[mz.prey->getIndex()]->hide();
        eatP.insert(mz.prey->getIndex());
        qs+= QString("Scoreboard: ") + QString::number(eatP.size()*50 + d_4);
        ui->label->setText(qs);

        if (spec.count(mz.prey->getIndex())!=0) {
            if (d_3 == 0){
                sc = 0;
                green->setPixmap(QPixmap(":images/joker"));
                darkred->setPixmap(QPixmap(":images/joker"));
                orange->setPixmap(QPixmap(":images/joker"));
                d_3 = 1;
                spec.erase(mz.prey->getIndex());
            }

        }

        if (mz.collide()){
            if (d_3 == 0){
                pause();
                mn = 1;
            }
            else if (mz.predatorGreen->getIndex()==mz.prey->getIndex() && GJ == 0){
                green->setPixmap(QPixmap(":images/jokerC"));
                GJ = 1;
                d_4+= 200;
            }
            else if (mz.predatorRed->getIndex()==mz.prey->getIndex() && DJ == 0){
                darkred->setPixmap(QPixmap(":images/jokerC"));
                DJ = 1;
                d_4+= 200;
            }
            else if (mz.predatorBlue->getIndex()==mz.prey->getIndex() && OJ == 0){
                orange->setPixmap(QPixmap(":images/jokerC"));
                OJ = 1;
                d_4+= 200;
            }
        }
        if (d_3 == 1){
            if (sc % 2 == 0){
                mz.navigateRed();
                mz.navigateGreen();
                mz.navigateBlue();
            }
            if (sc > 10){
                if (sc % 2 == 0){
                    if (OJ == 1)
                        orange->setPixmap(QPixmap(":images/jokerCI"));
                    else
                        orange->setPixmap(QPixmap(":images/jokerI"));
                    if (DJ == 1)
                        darkred->setPixmap(QPixmap(":images/jokerCI"));
                    else
                        darkred->setPixmap(QPixmap(":images/jokerI"));
                    if (GJ == 1)
                        green->setPixmap(QPixmap(":images/jokerCI"));
                    else
                        green->setPixmap(QPixmap(":images/jokerI"));
                }
                if (sc % 2 == 1){
                    if (OJ == 1)
                        orange->setPixmap(QPixmap(":images/jokerC"));
                    else
                        orange->setPixmap(QPixmap(":images/joker"));
                    if (DJ == 1)
                        darkred->setPixmap(QPixmap(":images/jokerC"));
                    else
                        darkred->setPixmap(QPixmap(":images/joker"));
                    if (GJ == 1)
                        green->setPixmap(QPixmap(":images/jokerC"));
                    else
                        green->setPixmap(QPixmap(":images/joker"));
                }
            }
        }
        else{
            mz.navigateRed();
            mz.navigateGreen();
            mz.navigateBlue();
        }
        if (d_1 == 50){
            mz.predatorRed = mz.nodeVector->at(205);
            d_1 = 100;
        }
        if (d_1 == 150){
            mz.predatorGreen = mz.nodeVector->at(205);
            d_1 = 200;
        }
        green->setPos(mz.predatorGreen->getX(),mz.predatorGreen->getY());
        orange->setPos(mz.predatorBlue->getX(),mz.predatorBlue->getY());
        darkred->setPos(mz.predatorRed->getX(),mz.predatorRed->getY());
        if (mz.collide()){
            if (d_3 == 0){
                pause();
                mn = 1;
            }
            else if (mz.predatorGreen->getIndex()==mz.prey->getIndex() && GJ == 0){
                green->setPixmap(QPixmap(":images/jokerC"));
                GJ = 1;
                d_4+= 200;
            }
            else if (mz.predatorRed->getIndex()==mz.prey->getIndex() && DJ == 0){
                darkred->setPixmap(QPixmap(":images/jokerC"));
                DJ = 1;
                d_4+= 200;
            }
            else if (mz.predatorBlue->getIndex()==mz.prey->getIndex() && OJ == 0){
                orange->setPixmap(QPixmap(":images/jokerC"));
                OJ = 1;
                d_4+= 200;
            }
        }
        if (eatP.size() == 104){
            pause();
            qs = QString("You've completed the maze. Your score was: ") + QString::number(eatP.size()*50 + d_4) + QString("Press P to restart");
            ui->label_2->setText(qs);
            d_2 = 3;
        }
    }
}

bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
    QKeyEvent *keyEvent = NULL;//event data, if this is a keystroke event
    bool result = false;//return true to consume the keystroke

    if (event->type() == QEvent::KeyPress)
    {
         keyEvent = dynamic_cast<QKeyEvent*>(event);
         this->keyPressEvent(keyEvent);
         result = true;
    }//if type()

    else if (event->type() == QEvent::KeyRelease)
    {
        keyEvent = dynamic_cast<QKeyEvent*>(event);
        this->keyReleaseEvent(keyEvent);
        result = true;
    }//else if type()

    //### Standard event processing ###
    else
        result = QObject::eventFilter(obj, event);

    return result;
}//eventFilter

void MainWindow::consume(){
    mz.prey = mz.nodeVector->at(311);
    mz.predatorRed = mz.nodeVector->at(206);
    mz.predatorBlue = mz.nodeVector->at(205);
    mz.predatorGreen = mz.nodeVector->at(227);
    d_1 = 0;
    d_2 += 1;
    agent->setPos(600,550);
    green->setPos(550,350);
    orange->setPos(500,350);
    darkred->setPos(450,350);
    if (d_2 == 1)
        agent1->hide();
    if (d_2 == 2)
        agent2->hide();
    if (d_2 == 3)
        agent3->hide();
        file.open(QFile::ReadWrite);
        QTextStream in(&file);
        in << bs << QString(" : ") << QString::number(eatP.size()*50 + d_4) << QString("\n");
        file.flush();
        file.close();
}

void MainWindow::pause(){
    if(off){
        timer->start(300);
        off=!off;
    }
    else{
        if(timer->isActive()){
            timer->stop();
        }
        else{
            timer->start(300);
        }
    }
}

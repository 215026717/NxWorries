/*
  Group Name: NxWorries
  Group Members: Maxwell Mahlaba
                      Mongezi Nene
                      Simangaliso Mlangeni
  315 Pacman Project
  Maze file
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

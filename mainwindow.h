#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include "myscene.h"
#include <set>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString bs;
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *);

private:
    set<int> eatP;
    set<int>::iterator it;
    pair<set<int>::iterator,bool> ret;

    Ui::MainWindow *ui;
    QTimer *timer;
    MyScene* scene;
    QGraphicsPixmapItem* agent;
    QGraphicsPixmapItem* agent1;
    QGraphicsPixmapItem* agent2;
    QGraphicsPixmapItem* agent3;
    QGraphicsEllipseItem* agent4;
    QGraphicsEllipseItem* pellets[320];
    QGraphicsPixmapItem* item;
    QGraphicsPixmapItem* darkred;
    QGraphicsPixmapItem* orange;
    QGraphicsPixmapItem* green;
    bool eventFilter(QObject*,QEvent*);
    void consume();
    bool off;
    int hr,mn,sc,d_1,d_2,d_3,d_4,DJ,OJ,GJ;
private slots:
void tick();
void pause();
};

#endif // MAINWINDOW_H

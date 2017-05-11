#include "myscene.h"

MyScene::MyScene(QObject *parent):QGraphicsScene(parent)
{

}

void MyScene::drawBackground(QPainter* painter,const QRectF &rect){
    const QPixmap pm(":/images/pmaze.png");
    painter->drawPixmap(0,0,pm.width()-3,pm.height()-3,pm);
    this->setSceneRect(0,0,pm.width(),pm.height());
}

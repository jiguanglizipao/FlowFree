#include "gamescene.h"
#include <QDebug>

GameScene::GameScene(QWidget *parent, int _size, int _n)
    :QGraphicsScene(parent), size(_size), n(_n)
{
    Psize = double(size)/double(n);
    FlagR = Psize*.4;
    CircleR = Psize*.6;
    flags.push_back(Flags(QPoint(0, 0), QPoint(4, 1), QPen(Qt::blue), QBrush(Qt::blue)));
    flags.push_back(Flags(QPoint(0, 3), QPoint(3, 1), QPen(Qt::red), QBrush(Qt::red)));
    flags.push_back(Flags(QPoint(0, 4), QPoint(3, 2), QPen(Qt::gray), QBrush(Qt::gray)));
    flags.push_back(Flags(QPoint(1, 3), QPoint(2, 2), QPen(Qt::yellow), QBrush(Qt::yellow)));
    flags.push_back(Flags(QPoint(4, 2), QPoint(3, 4), QPen(Qt::green), QBrush(Qt::green)));
    Update(false);
}

void GameScene::makeMap()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            this->addRect(i*Psize, j*Psize, Psize, Psize);
        }
    for(size_t i=0;i<flags.size();i++)addFlag(flags[i]);
}

void GameScene::addFlag(Flags flag)
{
    const double r = FlagR;
    this->addEllipse(flag.a[0].y()*Psize+Psize/2-r/2, flag.a[0].x()*Psize+Psize/2-r/2, r, r, flag.pen, flag.brush);
    this->addEllipse(flag.a[1].y()*Psize+Psize/2-r/2, flag.a[1].x()*Psize+Psize/2-r/2, r, r, flag.pen, flag.brush);
}

void GameScene::drawCircle(int x, int y, QPen pen, QBrush brush)
{
    const double r = CircleR;
    this->addEllipse(x-r/2, y-r/2, r, r, pen, brush);
}


void GameScene::Update(bool flag, int x, int y)
{
    this->clear();
    makeMap();
    if(flag)drawCircle(x, y);
}

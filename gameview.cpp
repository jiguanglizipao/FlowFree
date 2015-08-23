#include "gameview.h"
#include <QDebug>
#include <QMouseEvent>

GameView::GameView(GameScene *scene, QWidget *parent)
    :QGraphicsView(scene, parent), Scene(scene)
{
    this->setFixedSize(705, 705);
    Scene->setSceneRect(0, 0, 700, 700);
}

void GameView::mousePressEvent(QMouseEvent  *event)
{
    qDebug()<<"Press "<<event->button()<<" "<<event->pos().x()<<" "<<event->pos().y();
    Scene->Update(true, event->pos().x(), event->pos().y());
}

void GameView::mouseMoveEvent(QMouseEvent  *event)
{
    qDebug()<<"Move "<<event->pos().x()<<" "<<event->pos().y();
    Scene->Update(true, event->pos().x(), event->pos().y());
}

void GameView::mouseReleaseEvent(QMouseEvent  *event)
{
    qDebug()<<"Release "<<event->button()<<" "<<event->pos().x()<<" "<<event->pos().y();
    Scene->Update(false, event->pos().x(), event->pos().y());
}

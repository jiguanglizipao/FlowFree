#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QtMath>
#include <QVector>

struct Flags
{
    QPoint a[2];
    QBrush brush;
    QPen pen;
    Flags(QPoint a1=QPoint(), QPoint a2=QPoint(), QPen _pen = QPen(), QBrush _brush = QBrush())
    {
        a[0]=a1, a[1]=a2, brush=_brush, pen=_pen;
    }
};

struct Data
{
    QVector<Flags> flags;
    int n;
};

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QWidget *parent = 0, int _size = 700);
    void Init(Data &a);
public slots:
    void Press(int x, int y);
    void Move(int x, int y);
    void Release(int x, int y);
signals:
    void Success();
private:
    int size, n;
    double Psize, FlagR, CircleR, PathR;
    int moveFlag;
    void makeMap();
    void drawCircle(int i, int j, QPen pen = QPen(), QBrush brush = QBrush());
    QVector<Flags> flags;
    void addFlag(Flags flag);
    QVector<QVector<int> > filled;
    QVector<QVector<QPoint> > path;
    bool checkFlag(int x, int y);
    void Update(int x=0, int y=0);
    /*double distance(QPoint x)
    {
        return qSqrt(qPow(x.x(), 2) + qPow(x.y(), 2));
    }*/
};

#endif // GAMESCENE_H

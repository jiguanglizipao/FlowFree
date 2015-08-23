#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QPoint>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QWidget *parent = 0, int _size = 700, int _n = 5);
public slots:
    void Update(bool flag, int x=0, int y=0);
private:
    int n;
    const int size;
    double Psize, FlagR, CircleR;
    void makeMap();
    //void drawFlagCircle(int i, int j, QPen pen = QPen(), QBrush brush = QBrush());
    void drawCircle(int i, int j, QPen pen = QPen(), QBrush brush = QBrush());
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
    QVector<Flags> flags;
    void addFlag(Flags flag);
};

#endif // GAMESCENE_H

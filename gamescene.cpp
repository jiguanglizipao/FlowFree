#include "gamescene.h"
#include <QDebug>

GameScene::GameScene(QWidget *parent, int _size, int _n)
    :QGraphicsScene(parent), size(_size), n(_n), moveFlag(-1)
{
    Psize = double(size)/double(n);
    filled.resize(n);
    for(int i=0;i<n;i++)filled[i].resize(n);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)filled[i][j]=-1;
    FlagR = Psize*.4;
    CircleR = Psize*.6;
    PathR = Psize*.2;
    flags.push_back(Flags(QPoint(0, 0), QPoint(1, 4), QPen(Qt::blue), QBrush(Qt::blue)));
    flags.push_back(Flags(QPoint(3, 0), QPoint(1, 3), QPen(Qt::red), QBrush(Qt::red)));
    flags.push_back(Flags(QPoint(4, 0), QPoint(2, 3), QPen(Qt::gray), QBrush(Qt::gray)));
    flags.push_back(Flags(QPoint(3, 1), QPoint(2, 2), QPen(Qt::yellow), QBrush(Qt::yellow)));
    flags.push_back(Flags(QPoint(2, 4), QPoint(4, 3), QPen(Qt::green), QBrush(Qt::green)));
    path.resize(flags.size());
    for(size_t i=0;i<path.size();i++)path[i].clear();
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
    this->addEllipse(flag.a[0].x()*Psize+Psize/2-r/2, flag.a[0].y()*Psize+Psize/2-r/2, r, r, flag.pen, flag.brush);
    this->addEllipse(flag.a[1].x()*Psize+Psize/2-r/2, flag.a[1].y()*Psize+Psize/2-r/2, r, r, flag.pen, flag.brush);
}

void GameScene::drawCircle(int x, int y, QPen pen, QBrush brush)
{
    const double r = CircleR;
    QColor tmp = brush.color();tmp.setAlpha(128);
    brush.setColor(tmp);
    this->addEllipse(x-r/2, y-r/2, r, r, pen, brush);
}

void GameScene::Press(int x, int y)
{
    const double r = FlagR/2;
    moveFlag=-1;
    int tmp;
    for(size_t i=0;i<flags.size();i++)
        for(int j=0;j<2;j++)
        {
            double fx=flags[i].a[j].x()*Psize+Psize/2, fy=flags[i].a[j].y()*Psize+Psize/2;
            if(distance(QPoint(x-fx, y-fy))<r)moveFlag=i, tmp=j;
        }
    if(moveFlag!=-1)
    {
        for(size_t i=0;i<path[moveFlag].size();i++)filled[path[moveFlag][i].x()][path[moveFlag][i].y()]=-1;
        path[moveFlag].clear();
        path[moveFlag].push_back(flags[moveFlag].a[tmp]);
        filled[flags[moveFlag].a[tmp].x()][flags[moveFlag].a[tmp].y()]=moveFlag;
    }
    Update(x, y);
}

bool GameScene::checkFlag(int x, int y)
{
    for(size_t i=0;i<flags.size();i++)for(int j=0;j<2;j++)
        if(flags[i].a[j].x() == x && flags[i].a[j].y() == y)return i==moveFlag;
    return true;
}

void GameScene::Move(int x, int y)
{
    x=std::max(0, x);x=std::min(size-1, x);
    y=std::max(0, y);y=std::min(size-1, y);

    const int dx[4]={-1, 0, 1, 0}, dy[4]={0, 1, 0, -1};

    if(moveFlag!=-1)
    {
        for(int i=0;i<4;i++)
        {
            int fx=path[moveFlag].back().x()+dx[i], fy=path[moveFlag].back().y()+dy[i];
            if(x>=fx*Psize && x<(fx+1)*Psize && y>=fy*Psize && y<(fy+1)*Psize){
                if(path[moveFlag].size()>1 && path[moveFlag][path[moveFlag].size()-2] == QPoint(fx, fy))
                    filled[path[moveFlag].back().x()][path[moveFlag].back().y()]=-1, path[moveFlag].removeLast();
                if(filled[fx][fy]!=moveFlag && checkFlag(fx, fy))
                {
                    if(filled[fx][fy] != -1)
                    {
                        int tmp = filled[fx][fy];
                        for(size_t j=0;j<path[tmp].size();j++)filled[path[tmp][j].x()][path[tmp][j].y()]=-1;
                        path[tmp].clear();
                    }
                    path[moveFlag].push_back(QPoint(fx, fy));
                    filled[fx][fy]=moveFlag;
                }
                break;
            }
        }
    }
    Update(x, y);
}

void GameScene::Release(int x, int y)
{
    if(moveFlag!=-1){
        if(path[moveFlag].size()>1 && (path[moveFlag].back()==flags[moveFlag].a[0]||path[moveFlag].back()==flags[moveFlag].a[1]))
            moveFlag=-1;
        else
        {
            for(size_t j=0;j<path[moveFlag].size();j++)filled[path[moveFlag][j].x()][path[moveFlag][j].y()]=-1;
            path[moveFlag].clear();
        }
    }
    moveFlag = -1;
    Update(x, y);
}

void GameScene::Update(int x, int y)
{
    this->clear();
    makeMap();
    /*
    for(size_t i=0;i<path.size();i++)
        for(int j=0;j<int(path[i].size())-1;j++)
        {
            int x = (path[i][j].x()==path[i][j+1].x())?(Psize*path[i][j].x()+Psize/2-PathR/2):(Psize*std::min(path[i][j].x(), path[i][j+1].x())+Psize/2);
            int y = (path[i][j].y()==path[i][j+1].y())?(Psize*path[i][j].y()+Psize/2-PathR/2):(Psize*std::min(path[i][j].y(), path[i][j+1].y())+Psize/2);
            int w = (path[i][j].x()==path[i][j+1].x())?PathR:Psize;
            int h = (path[i][j].y()==path[i][j+1].y())?PathR:Psize;
            this->addRect(x, y, w, h, flags[i].pen, flags[i].brush);
        }
    */
    for(size_t i=0;i<path.size();i++)
        for(int j=0;j<int(path[i].size())-1;j++)
        {
            QPen pen(flags[i].brush, PathR, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            this->addLine(Psize*path[i][j].x()+Psize/2, Psize*path[i][j].y()+Psize/2, Psize*path[i][j+1].x()+Psize/2, Psize*path[i][j+1].y()+Psize/2, pen);
        }
    if(moveFlag!=-1)drawCircle(x, y, flags[moveFlag].pen, flags[moveFlag].brush);
}

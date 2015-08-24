#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamescene.h"
#include "gameview.h"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void loadGame();
    void againGame();
    void nextGame();
    void beforeGame();
    void newGame();
private:
    GameScene *MainScene;
    GameView *MainView;
    QVector<Data> gameData;
    int gameNumber;
};

#endif // MAINWINDOW_H

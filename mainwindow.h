#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamescene.h"
#include "gameview.h"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QComboBox>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void loadGame(QString File = "");
    void againGame();
    void nextGame();
    void previousGame();
    void newGame();
    void solveGame();
    void selectGame();
private:
    GameScene *MainScene;
    GameView *MainView;
    QComboBox *SelectBox;
    QVector<Data> gameData;
    QVector<QVector<QVector<QPoint> > > gameSave;
    int gameNumber;
};

#endif // MAINWINDOW_H

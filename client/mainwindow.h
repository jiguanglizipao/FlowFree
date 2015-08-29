#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescene.h"
#include "gamesolver.h"
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void loadGame(QString File = "");
    void againGame();
    void nextGame();
    void previousGame();
    void newGame();
    void computeGame();
    void answerGame();
    void selectGame(int num=-1);
    void displayAbout();

private slots:
    void connectError(QAbstractSocket::SocketError error);
    void connected();
    void getData();
    void on_connectButton_clicked();
    void on_receiveButton_clicked();

private:
    GameScene *gameScene;
    QVector<Data> gameData;
    QVector<QVector<QVector<QPoint> > > gameSave;
    int gameNumber;
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString socketData;
};

#endif // MAINWINDOW_H

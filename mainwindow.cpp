#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameScene = new GameScene(this);
    ui->gameView->setScene(gameScene);

    connect(ui->selectButton, SIGNAL(pressed()), this, SLOT(selectGame()));
    connect(ui->loadButton, SIGNAL(pressed()), this, SLOT(loadGame()));
    connect(ui->againButton, SIGNAL(pressed()), this, SLOT(againGame()));
    connect(ui->previousButton, SIGNAL(pressed()), this, SLOT(previousGame()));
    connect(ui->nextButton, SIGNAL(pressed()), this, SLOT(nextGame()));
    connect(ui->computeButton, SIGNAL(pressed()), this, SLOT(computeGame()));
    connect(ui->answerButton, SIGNAL(pressed()), this, SLOT(answerGame()));

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(ui->actionEasy, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(ui->actionMedium, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(ui->actionHard, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->actionEasy, 0);
    signalMapper->setMapping(ui->actionMedium, 1);
    signalMapper->setMapping(ui->actionHard, 2);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(selectGame(int)));

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(displayAbout()));

    gameNumber=-1;
}

void MainWindow::loadGame(QString File)
{
    QString fileName;
    if(File != "")fileName = File;else fileName = QFileDialog::getOpenFileName(this, tr("Open Files"), "", tr("ff Files(*.ff);;All Files(*.*)"));
    if (fileName == "") return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(this, tr("ERROR!"), tr("Can not open this fils. %1").arg(fileName));
        return;
    }
    QTextStream in(&file);
    int n, m, num;
    gameData.clear();
    gameSave.clear();
    in>>n;
    for(int i=0;i<n;i++){
        gameData.push_back(Data());
        in>>gameData[i].n>>m;
        gameSave.push_back(QVector<QVector<QPoint> >());
        for(int j=0;j<m;j++)
        {
            int x1, y1, x2, y2, r, g, b;
            in>>x1>>y1>>x2>>y2>>r>>g>>b;
            gameData[i].flags.push_back(Flags(QPoint(x1, y1), QPoint(x2, y2), QPen(QColor(r, g, b, 255)), QBrush(QColor(r, g, b, 255))));
            gameSave[i].push_back(QVector<QPoint>());
            in>>num;
            for(int k=0;k<num;k++){
                int x, y;
                in>>x>>y;
                gameSave[i][j].push_back(QPoint(x, y));
            }
        }
    }
    gameNumber=0;
    gameScene->Init(gameData[0]);
}

void MainWindow::newGame()
{
    if(gameNumber!=-1)gameScene->Init(gameData[0]);
}

void MainWindow::againGame()
{
    if(gameNumber!=-1)gameScene->Init(gameData[gameNumber]);
}

void MainWindow::previousGame()
{
    if(gameNumber>0)gameScene->Init(gameData[--gameNumber]);
}

void MainWindow::nextGame()
{
    if(gameNumber<gameData.size()-1)gameScene->Init(gameData[++gameNumber]);
}

void MainWindow::computeGame()
{
    if(gameNumber!=-1)gameScene->Solve(gameSolver()(gameData[gameNumber]));
}

void MainWindow::answerGame()
{
    if(gameNumber!=-1)gameScene->Solve(gameSave[gameNumber]);
}

void MainWindow::selectGame(int num)
{
    if(num == -1)num = ui->selectBox->currentIndex();
    switch (num) {
    case 0:
        loadGame("://res/5x5.ff");
        break;
    case 1:
        loadGame("://res/6x6.ff");
        break;
    case 2:
        loadGame("://res/7x7.ff");
        break;
    default:
        break;
    }
}

void MainWindow::displayAbout()
{
    QMessageBox aboutBox(this);
    aboutBox.setToolTip("About this Application");
    aboutBox.setText("<h2>Flow Free</h2>"
                     "<h4>By: </h4><p>&nbsp;&nbsp;&nbsp;&nbsp;Jiguanglizipao</p>"
                     "<h4>Website: </h4><p><a href=https://github.com/jiguanglizipao/FlowFree>https://github.com/jiguanglizipao/FlowFree</a></p>");
    aboutBox.setIconPixmap(QPixmap("://res/zerg.png"));
    aboutBox.exec();
}


MainWindow::~MainWindow()
{
    delete ui;
}

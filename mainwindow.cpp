#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *Rightlayout = new QVBoxLayout, *Selectlayout = new QVBoxLayout;

    SelectBox = new QComboBox(this);
    SelectBox->addItem("Easy");
    SelectBox->addItem("Medium");
    SelectBox->addItem("Hard");

    QPushButton *SelectButton = new QPushButton("S&elect Level", this);
    Selectlayout->addWidget(SelectBox);
    Selectlayout->addWidget(SelectButton);

    //QPushButton *NewButton = new QPushButton("&New", this);
    QPushButton *AgainButton = new QPushButton("&Again", this);
    QPushButton *PreviousButton = new QPushButton("&Previous", this);
    QPushButton *NextButton = new QPushButton("&Next", this);
    QPushButton *LoadButton = new QPushButton("&Load", this);
    QPushButton *SolveButton = new QPushButton("&Solve", this);


    Rightlayout->addLayout(Selectlayout);
    Rightlayout->addWidget(AgainButton);
    Rightlayout->addWidget(PreviousButton);
    Rightlayout->addWidget(NextButton);
    Rightlayout->addWidget(LoadButton);
    Rightlayout->addWidget(SolveButton);

    connect(SelectButton, SIGNAL(pressed()), this, SLOT(selectGame()));
    connect(LoadButton, SIGNAL(pressed()), this, SLOT(loadGame()));
    //connect(NewButton, SIGNAL(pressed()), this, SLOT(newGame()));
    connect(AgainButton, SIGNAL(pressed()), this, SLOT(againGame()));
    connect(PreviousButton, SIGNAL(pressed()), this, SLOT(previousGame()));
    connect(NextButton, SIGNAL(pressed()), this, SLOT(nextGame()));
    connect(SolveButton, SIGNAL(pressed()), this, SLOT(solveGame()));

    QHBoxLayout *Mainlayout = new QHBoxLayout;
    MainScene = new GameScene(this, 700);
    MainView = new GameView(MainScene, this);
    connect(MainView, SIGNAL(Press(int,int)), MainScene, SLOT(Press(int,int)));
    connect(MainView, SIGNAL(Move(int,int)), MainScene, SLOT(Move(int,int)));
    connect(MainView, SIGNAL(Release(int,int)), MainScene, SLOT(Release(int,int)));
    Mainlayout->addWidget(MainView);
    Mainlayout->addLayout(Rightlayout);
    this->setLayout(Mainlayout);
    this->resize(QSize(1024, 768));

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
    MainScene->Init(gameData[0]);
}

void MainWindow::newGame()
{
    if(gameNumber!=-1)MainScene->Init(gameData[0]);
}

void MainWindow::againGame()
{
    if(gameNumber!=-1)MainScene->Init(gameData[gameNumber]);
}

void MainWindow::previousGame()
{
    if(gameNumber>0)MainScene->Init(gameData[--gameNumber]);
}

void MainWindow::nextGame()
{
    if(gameNumber<gameData.size()-1)MainScene->Init(gameData[++gameNumber]);
}

void MainWindow::solveGame()
{
    if(gameNumber!=-1)MainScene->Solve(gameSave[gameNumber]);
}

void MainWindow::selectGame()
{
    switch (SelectBox->currentIndex()) {
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


MainWindow::~MainWindow()
{

}

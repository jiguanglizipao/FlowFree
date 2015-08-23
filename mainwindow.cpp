#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *Rightlayout = new QVBoxLayout;
    QPushButton *NewButton = new QPushButton("New Game", this);
    QPushButton *AgainButton = new QPushButton("Again", this);
    QPushButton *BeforeButton = new QPushButton("Before", this);
    QPushButton *NextButton = new QPushButton("Next", this);
    Rightlayout->addWidget(NewButton);
    Rightlayout->addWidget(AgainButton);
    Rightlayout->addWidget(BeforeButton);
    Rightlayout->addWidget(NextButton);
    QHBoxLayout *Mainlayout = new QHBoxLayout;
    GameScene *MainScene = new GameScene(this, 700, 5);
    GameView *MainView = new GameView(MainScene, this);
    Mainlayout->addWidget(MainView);
    Mainlayout->addLayout(Rightlayout);
    this->setLayout(Mainlayout);
    this->resize(QSize(1024, 768));
}

MainWindow::~MainWindow()
{

}

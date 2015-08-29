#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    QTcpSocket *tmp = server->nextPendingConnection();
    if(!tmp)return;
    qDebug()<<tmp->peerAddress()<<" "<<tmp->peerPort()<<" "<<tmp->peerName();
    socket.push_back(tmp);
    connect(tmp, SIGNAL(disconnected()), this, SLOT(removeConnection()));
    QVariant port(tmp->peerPort());
    socketItem.push_back(new QListWidgetItem(tmp->peerAddress().toString()+":"+port.toString(), ui->ipList));
    ui->ipList->addItem(socketItem.back());
}

void MainWindow::removeConnection()
{
    qDebug()<<1231231;
    for(int i=0;i<socket.size();i++)
    {
        qDebug()<<socket[i]->state();
        if(socket[i]->state() == QTcpSocket::UnconnectedState){
            qDebug()<<i;
            ui->ipList->removeItemWidget(socketItem[i]);
            delete socketItem[i];
            //delete socket[i];
            socket.removeAt(i);
            socketItem.removeAt(i);
            break;
        }
    }
}

void MainWindow::on_listenButton_clicked()
{
    if(server->isListening())server->close();
    server->listen(QHostAddress::Any, ui->portBox->value());
    ui->sendButton->setEnabled(true);
    connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(on_sendButton_clicked()));
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}


void MainWindow::on_sendButton_clicked()
{
    QString tmp = ui->textEdit->document()->toPlainText();
    qDebug()<<tmp;

    for(int i=0;i<socket.size();i++)
    {
        socket[i]->write(tmp.toStdString().c_str());
    }

}

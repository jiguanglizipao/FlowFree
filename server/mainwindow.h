#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newConnection();
    void removeConnection();
    void on_listenButton_clicked();
    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QVector <QTcpSocket*> socket;
    QVector <QListWidgetItem*> socketItem;

};

#endif // MAINWINDOW_H

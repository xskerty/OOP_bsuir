#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QPushButton>
#include "gamewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Client* Client, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ReadSlot();

    void on_confirmNick_pushButton_clicked();

    void on_connect_pushButton_clicked();

    void on_createGame_pushButton_clicked();

private:
    GameWindow* game;
    QByteArray Data;
    QTcpSocket *socket;
    Client* client;
    uint8_t gameId;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

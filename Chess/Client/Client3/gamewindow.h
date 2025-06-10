#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "../../Chess-Core/src/Game.h"
#include <QTcpSocket>
#include "client.h"
#include <QTimer>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(Client* client, int total, int dop, QWidget *parent = nullptr);
    void setData(QByteArray d) {Data = d;};
    ~GameWindow();

private:
    int totalTime;
    int dopTime;
    Client* client;
    QTcpSocket* socket;
    std::vector<chess::Position> LegalMoves;
    QByteArray Data;
    chess::Game* game;
    std::pair<int, int> selectedField;
    std::pair<int, int> inFieldClicked(int x, int y);
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    Ui::GameWindow *ui;
    QTimer* timer1;
    QTimer* timer2;
    int remainingSeconds1;
    int remainingSeconds2;
    bool iAskDraw = 0;
    bool opAskDraw = 0;
private slots:
    void updateTimer1();
    void updateTimer2();
    void ReadSlot();
    void SendSlot();
    void on_capitulate_pushButton_clicked();
    void on_drawRemain_pushButton_clicked();
    void on_acceptDraw_pushButton_clicked();
    void on_declineDraw_pushButton_clicked();
};

#endif // GAMEWINDOW_H

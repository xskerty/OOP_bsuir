#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QVector>
#include "game.h"
#include "user.h"

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;

    enum SenderCodes : int
    {
        CONNECTION_USER   = 0x00,
        CREATE_GAME       = 0x01,
        CONNECT_GAME      = 0x02,
        MOVE_PIECE        = 0x03,
        LOGIN_CODE        = 0x04,
        CAPITULATE_CODE   = 0x05,
        DRAW_REQ          = 0x06,
        DRAW_ACCEPT       = 0x07,
        DRAW_DECLINE      = 0x08,
    };

    enum ServerCodes : int
    {
        NEW_GAME            = 0x00,
        START_GAME          = 0x01,
        OK                  = 0x02,
        MOVE_PIECE_OK       = 0x03,
        NICKNAME_ERROR      = 0x04,
        CAPITULATE_CODE_S   = 0x05,
        DRAW_REQ_S          = 0x06,
        DRAW_ACCEPT_S       = 0x07,
        DRAW_DECLINE_S      = 0x08,
    };
private:
    QVector<User> players;
    QVector<QTcpSocket*> Sockets;
    QByteArray Data;
    QVector<QString> nicknames;
    chess::Game* game;
    uint8_t t;
public slots:
    void incomingConnection(qintptr socketDiscriptor);
    void SendSlot(const QByteArray &arr);
    void ReadSlot();
signals:
    void sendSlotSignal(const QByteArray &arr);
};

#endif // SERVER_H

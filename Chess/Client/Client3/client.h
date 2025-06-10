#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QVector>
#include <stdint.h>
#include "../../Chess-Core/src/Game.h"

class Client: QTcpSocket
{
public:
    inline QTcpSocket* getSocket() const {return socket;};
    void setNickname(QString nick) {myNickname = nick;};
    void setID(uint8_t id) {myID = id;};
    void setColor(Color c) {color = c;};
    inline Color getColor() const {return color;};
    inline QString getNickname() { return myNickname;};
    inline uint8_t getID() {return myID;};
    Client();
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
    QTcpSocket *socket;
    QByteArray Data;
    QString myNickname;
    uint8_t myID;
    Color color;
public slots:

    void ReadSlot();
    void SendSlot();
};

#endif // CLIENT_H

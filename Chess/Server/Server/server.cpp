#include "server.h"
#include <QString>
#include <qDebug>
#include <QRandomGenerator>

Server::Server()
{
    if(this->listen(QHostAddress::Any, 7777))
    {
        qDebug()<<"start";
    }
    else
    {
        qDebug()<<"error";
    }
}

void Server::incomingConnection(qintptr socketDiscriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDiscriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::ReadSlot);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(this, &Server::sendSlotSignal, this, &Server::SendSlot);
    Sockets.push_back(socket);
    qDebug()<<"client connected" <<socketDiscriptor;
}

void Server::ReadSlot()
{
    socket = (QTcpSocket*)sender();
    Data = socket->readAll();
    qDebug()<<"Data: "<<Data;

    switch (Data.at(0))
    {
    case Server::SenderCodes::CONNECTION_USER:
    {
        QString userNickname = Data.mid(1, Data.size());
        qDebug()<<userNickname<< " tried to connect the game";

        Data.clear();
        players.push_back(User(socket ,userNickname, players.size()));
        nicknames.push_back(userNickname);
        break;
    }
    case Server::SenderCodes::CREATE_GAME:
    {
        QString userNickname = Data.mid(3, Data.size());
        uint8_t c = Data.at(1);
        t = Data.at(2);
        foreach (auto player, players) {
            if(player.getName() == userNickname)
            {
                switch (Data.at(1)) {
                case 1:
                    player.setColor(Color::WHITE);
                    break;
                case 2:
                    player.setColor(Color::BLACK);
                    break;
                case 3:
                    player.setColor(Color::NONE);
                    break;
                default:
                    break;
                }
                player.setTimeControl(t);
            }
            Data.clear();
            Data.push_back(Server::ServerCodes::NEW_GAME);
            Data.push_back(c);
            Data.push_back(t);
            Data.push_back(player.getName().toUtf8());
        }
        SendSlot(Data);
        break;
    }
    case Server::SenderCodes::CONNECT_GAME:
    {
        QString userNickname = Data.mid(1, Data.size());
        foreach (auto player, players) {
            if(player.getName() == userNickname)
            {
                Data.clear();
                Data.push_back(Server::ServerCodes::START_GAME);

                if(player.getColor()==Color::NONE)
                {
                    int randomNumber = QRandomGenerator::global()->bounded(0, 2);
                    if(randomNumber)
                    {
                        player.setColor(Color::WHITE);
                    }
                    else
                    {
                        player.setColor(Color::BLACK);
                    }
                    Data.push_back(randomNumber);
                }
                else
                {
                    Data.push_back(player.getColor() == Color::WHITE ? 0 : 1);
                }
                Data.push_back(t);
                qDebug()<<"t: "<<player.getTimeControl();
                Data.push_back(player.getName().toUtf8());
                SendSlot(Data);
                break;
            }
        }
        break;
    }
    case Server::SenderCodes::MOVE_PIECE:
    {
        SendSlot(Data);
        break;
    }
    case Server::SenderCodes::CAPITULATE_CODE:
    {
        SendSlot(Data);
        break;
    }
    case Server::SenderCodes::DRAW_REQ:
    {
        SendSlot(Data);
        break;
    }
    case Server::SenderCodes::DRAW_ACCEPT:
    {
        SendSlot(Data);
        break;
    }
    case Server::SenderCodes::DRAW_DECLINE:
    {
        SendSlot(Data);
        break;
    }
}
}

void Server::SendSlot(const QByteArray &arr)
{
    qDebug()<<"sending packages...";
    qDebug()<<Data;

    foreach (auto player, players) {
        player.getSocket()->write(arr);
    }
    qDebug()<<"packages sended";
}


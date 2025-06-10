#ifndef USER_H
#define USER_H
#include <QTcpSocket>
#include "../../Chess-Core/src/Game.h"

class User
{
public:
    User(QTcpSocket*, QString, uint8_t);
    inline QTcpSocket* getSocket() const {return socket;};
    inline uint8_t getID() const {return id;};
    inline QString getName() const {return name;};
    inline Color getColor() const {return color;};
    inline uint8_t getTimeControl() const {return timeControl;};
    void setColor(Color c) {color = c;};
    void setTimeControl(uint8_t a) {timeControl = a;};
private:
    Color color;
    uint8_t timeControl ;
    QTcpSocket* socket;
    QString name;
    uint8_t id;
};

#endif // USER_H

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

GameWindow::GameWindow(Client* cli, int total, int dop, QWidget *parent)
    : QMainWindow(parent)
    , client(cli)
    , selectedField(-1,-1)
    , ui(new Ui::GameWindow)
    , totalTime(total)
    , dopTime(dop)
    , remainingSeconds1(total+1)
    , remainingSeconds2(total+1)
{
    socket = client->getSocket();
    connect(socket, &QTcpSocket::readyRead, this, &GameWindow::ReadSlot);
    game = new chess::Game();
    game->startNewGame();
    ui->setupUi(this);
    ui->capitulate_pushButton->setVisible(1);
    ui->drawRemain_pushButton->setVisible(1);
    ui->label->setVisible(0);
    ui->acceptDraw_pushButton->setVisible(0);
    ui->declineDraw_pushButton->setVisible(0);

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &GameWindow::updateTimer1);
    timer1->start(1000);

    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, &GameWindow::updateTimer2);
    timer2->start(1000);

    if(game->getCurrentTurn() == client->getColor())
    {
        timer2->stop();
    }
    else
    {
        timer1->stop();
    }

    ui->lcdNumber_1->setDigitCount(5);

    ui->lcdNumber_1->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_1->setStyleSheet("background: black; color: white;");
    ui->lcdNumber_1->setMode(QLCDNumber::Dec);
    ui->lcdNumber_1->setSmallDecimalPoint(true);

    ui->lcdNumber_2->setDigitCount(5);

    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_2->setStyleSheet("background: black; color: white;");
    ui->lcdNumber_2->setMode(QLCDNumber::Dec);
    ui->lcdNumber_2->setSmallDecimalPoint(true);

    updateTimer1();
    updateTimer2();
}

void GameWindow::paintEvent(QPaintEvent *event)
{

    QPen pen;
    QPainter painter(this);
    painter.setFont(QFont("Times", 14, QFont::Bold));


    if(client->getColor() == Color::WHITE)
    {
        //for white display
        for(int i = 7; i >=0 ;--i)
        {
            for(int j = 7; j>=0; --j)
            {
                QRect field(30+(i)*100, 30+(7-j)*100, 100, 100);

                painter.setBrush(QBrush((i+j)%2 == 1 ? Qt::lightGray:Qt::darkGray));
                if(selectedField.first == i && selectedField.second == j) painter.setBrush(QBrush(QColor(255,219,139,255)));
                for(int k = 0; k<LegalMoves.size(); ++k)
                {
                    if(LegalMoves[k].x == i && LegalMoves[k].y == j && game->getBoard().isMoveLegal(chess::Position(selectedField.first, selectedField.second),chess::Position(i,j))) painter.setBrush(QBrush(QColor(255,226,183,255)));
                }
                painter.drawRect(field);
                QRect rect(40+(i)*100, 40+(7-j)*100, 80, 80);
                if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::PAWN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_pawn.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::ROOK&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_rook.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KNIGHT&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_knight.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::BISHOP&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_bishop.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::QUEEN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_queen.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KING&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_king.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::PAWN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_pawn.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::ROOK&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_rook.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KNIGHT&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_knight.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::BISHOP&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_bishop.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::QUEEN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_queen.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KING&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_king.png"));
                }
            }
        }

        for(int i = 0; i <8; ++i)
        {
            for(int j = 0; j<8; ++j)
            {
                if(i==0) painter.drawText(QPoint(110+j*100,825),QChar('a'+j));
            }
            painter.drawText(QPoint(35, 50+(7-i)*100),QChar('1' + i));
        }
    }
    else{
        for(int i = 0; i <8 ;++i)
        {
            for(int j = 0; j<8; ++j)
            {
                QRect field(30+(7-i)*100, 30+j*100, 100, 100);

                painter.setBrush(QBrush((i+j)%2 == 1 ? Qt::lightGray:Qt::darkGray));
                if(selectedField.first == i && selectedField.second == j) painter.setBrush(QBrush(QColor(255,219,139,255)));
                for(int k = 0; k<LegalMoves.size(); ++k)
                {
                    if(LegalMoves[k].x == i && LegalMoves[k].y == j) painter.setBrush(QBrush(QColor(255,226,183,255)));
                }
                painter.drawRect(field);

                QRect rect(40+(7-i)*100, 40+j*100, 80, 80);
                if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::PAWN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_pawn.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::ROOK&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_rook.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KNIGHT&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_knight.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::BISHOP&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_bishop.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::QUEEN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_queen.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KING&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::BLACK)
                {
                    painter.drawImage(rect, QImage("black_king.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::PAWN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_pawn.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::ROOK&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_rook.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KNIGHT&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_knight.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::BISHOP&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_bishop.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::QUEEN&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_queen.png"));
                }
                else if(game->getBoard().getGrid()[j][i].get() != nullptr&&game->getBoard().getGrid()[j][i].get()->getType()==PieceType::KING&&game->getBoard().getGrid()[j][i].get()->getColor()==Color::WHITE)
                {
                    painter.drawImage(rect, QImage("white_king.png"));
                }
            }
        }

        for(int i = 7; i >=0; --i)
        {
            for(int j = 7; j >= 0; --j)
            {
                if(i==0) painter.drawText(QPoint(110+j*100,825),QChar('h'-j));
            }
            painter.drawText(QPoint(35, 50+(7-i)*100),QChar('8' - i));
        }
    }
}

std::pair<int, int> GameWindow::inFieldClicked(int x, int y)
{
    if(client->getColor() == Color::WHITE)
    {
        for(int i = 7; i >=0 ;--i)
        {
            for(int j = 7; j>=0; --j)
            {
                if(30+i*100<x && x<130+i*100 && 30+(7-j)*100 <y && 130+(7-j)*100 > y) return std::pair<int, int>(i, j);
            }
        }
    }
    else{
        for(int i = 0; i <8 ;++i)
        {
            for(int j = 0; j<8; ++j)
            {
                if(30+(7-i)*100<x && x<130+(7-i)*100 && 30+j*100 <y && 130+j*100 > y) return std::pair<int, int>(i, j);
            }
        }
    }
    return std::pair<int, int>(-1, -1);
}

void GameWindow::mousePressEvent(QMouseEvent *event){

    if(event->button() &Qt::LeftButton){
        if(selectedField == std::pair<int, int>(-1,-1)&&game->getCurrentTurn()== client->getColor())
        {
            selectedField = inFieldClicked(QCursor::pos().x(), QCursor::pos().y());
            if(selectedField != std::pair<int, int>(-1,-1)
                &&game->getBoard().getGrid()[selectedField.second][selectedField.first].get() != nullptr
                &&game->getBoard().getGrid()[selectedField.second][selectedField.first].get()->getColor()==client->getColor())
            {
                LegalMoves = game->getBoard().getLegalMoves(chess::Position(selectedField.first, selectedField.second));
            }
            else
            {
                selectedField = std::pair<int, int>(-1,-1);
            }
        }
        else
        {
            std::pair<int, int> nField = inFieldClicked(QCursor::pos().x(), QCursor::pos().y());
            if(nField != std::pair<int, int>(-1,-1)&&game->getCurrentTurn()== client->getColor())
            {
                for(int i = 0; i < LegalMoves.size(); ++i)
                {
                    if(LegalMoves[i].x == nField.first && LegalMoves[i].y == nField.second)
                    {
                        Data.clear();
                        Data.push_back(Client::SenderCodes::MOVE_PIECE);
                        Data.push_back(selectedField.first);
                        Data.push_back(selectedField.second);
                        Data.push_back(nField.first);
                        Data.push_back(nField.second);
                        SendSlot();

                        selectedField = std::pair<int, int>(-1,-1);
                        nField = std::pair<int, int>(-1,-1);
                        LegalMoves.clear();
                        break;
                    }
                }
                if(nField != std::pair<int, int>(-1,-1)
                    &&game->getBoard().getGrid()[nField.second][nField.first].get() != nullptr
                    &&game->getBoard().getGrid()[nField.second][nField.first].get()->getColor()==client->getColor())
                {
                    selectedField = nField;
                    LegalMoves = game->getBoard().getLegalMoves(chess::Position(selectedField.first, selectedField.second));
                }
                else
                {
                    selectedField = std::pair<int, int>(-1,-1);
                    LegalMoves.clear();
                }
            }
            else
            {
                selectedField = std::pair<int, int>(-1,-1);
                LegalMoves.clear();
            }

        }
    }
    else if(event->button() &Qt::RightButton)
    {
        selectedField = std::pair<int, int>(-1,-1);
        LegalMoves.clear();
    }

    QMainWindow::repaint();
}

void GameWindow::ReadSlot()
{
    switch (Data.at(0)) {
    case Client::ServerCodes::MOVE_PIECE_OK:
    {
        game->makeMove(chess::Position(Data.at(1), Data.at(2)), chess::Position(Data.at(3), Data.at(4)));

        if(game->getCurrentTurn()== client->getColor())
        {
            remainingSeconds2 += dopTime+1;
            updateTimer2();
            timer2->stop();
            timer1->start(1000);
        }
        else
        {
            remainingSeconds1 += dopTime+1;
            updateTimer1();
            timer1->stop();
            timer2->start(1000);
        }

        if(game->isGameOver())
        {
            timer1->stop();
            timer2->stop();
            if(game->getStatus() == GameStatus::CHECK)
            {

            }
            else if(game->getWinner() == Color::NONE)
            {
                QMessageBox::information(this, "Игра завершена", "Ничья!");
            }
            else if(game->getWinner() == client->getColor())
            {
                QMessageBox::information(this, "Победа", "Объявлен мат!");
            }
            else
            {
                QMessageBox::information(this, "Поражение", "Объявлен мат!");
            }
        }

        QMainWindow::repaint();
        break;
    }
    case Client::ServerCodes::CAPITULATE_CODE_S:
    {
        if(Data.mid(1, Data.size()) == client->getNickname())
        {
            QMessageBox::information(this, "Поражение", "Вы сдались!");
        }
        else
        {
            QMessageBox::information(this, "Победа", "Соперник сдался!");
        }
        timer1->stop();
        timer2->stop();
        break;
    }
    case Client::ServerCodes::DRAW_ACCEPT_S:
    {
        QMessageBox::information(this, "Ничья", "Ничья по соглашению сторон!");
        timer1->stop();
        timer2->stop();
        break;
    }
    case Client::ServerCodes::DRAW_DECLINE_S:
    {
        iAskDraw = false;
        opAskDraw = false;
        ui->acceptDraw_pushButton->setVisible(0);
        ui->declineDraw_pushButton->setVisible(0);
        ui->label->setVisible(0);
        ui->drawRemain_pushButton->setEnabled(1);
        break;
    }
    case Client::ServerCodes::DRAW_REQ_S:
    {
        if(Data.mid(1, Data.size()) != client->getNickname())
        {
            ui->acceptDraw_pushButton->setVisible(1);
            ui->declineDraw_pushButton->setVisible(1);
            ui->label->setVisible(1);
            opAskDraw = true;
        }
        break;
    }
    }
}

void GameWindow::updateTimer1()
{
    remainingSeconds1--;

    int mins = remainingSeconds1 / 60;
    int secs = remainingSeconds1 % 60;

    ui->lcdNumber_1->display(
        QString("%1:%2")
            .arg(mins, 2, 10, QLatin1Char('0'))
            .arg(secs, 2, 10, QLatin1Char('0'))
        );

    if (remainingSeconds1 <= 0) {
        timer1->stop();
        QMessageBox::information(this, "Поражение", "Ваше время вышло!");
    }
}

void GameWindow::updateTimer2()
{
    remainingSeconds2--;

    int mins = remainingSeconds2 / 60;
    int secs = remainingSeconds2 % 60;

    ui->lcdNumber_2->display(
        QString("%1:%2")
            .arg(mins, 2, 10, QLatin1Char('0'))
            .arg(secs, 2, 10, QLatin1Char('0'))
        );

    if (remainingSeconds2 <= 0) {
        timer2->stop();
        QMessageBox::information(this, "Победа", "Время соперника вышло!");
    }
}

void GameWindow::SendSlot()
{
    socket->write(Data);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_capitulate_pushButton_clicked()
{
    Data.clear();
    Data.push_back(Client::SenderCodes::CAPITULATE_CODE);
    Data.push_back(client->getNickname().toUtf8());
    SendSlot();
}


void GameWindow::on_drawRemain_pushButton_clicked()
{
    Data.clear();
    if(opAskDraw)
    {
        Data.push_back(Client::SenderCodes::DRAW_ACCEPT);
    }
    else
    {
        Data.push_back(Client::SenderCodes::DRAW_REQ);
        Data.push_back(client->getNickname().toUtf8());
        iAskDraw = true;
        ui->drawRemain_pushButton->setDisabled(1);
    }
    SendSlot();
}


void GameWindow::on_acceptDraw_pushButton_clicked()
{
    Data.clear();
    Data.push_back(Client::SenderCodes::DRAW_ACCEPT);
    SendSlot();
}


void GameWindow::on_declineDraw_pushButton_clicked()
{
    Data.clear();
    Data.push_back(Client::SenderCodes::DRAW_DECLINE);
    SendSlot();
}


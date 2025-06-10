#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostInfo>
#include <QDebug>
MainWindow::MainWindow(Client* Client, QWidget *parent)
    : QMainWindow(parent)
    ,client(Client)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    socket = client->getSocket();
    ui->comboBox->setVisible(0);
    ui->comboBox_2->setVisible(0);
    ui->createGame_pushButton->setVisible(0);
    ui->connect_pushButton->setVisible(0);
    ui->tableWidget->setVisible(0);
    ui->label->setVisible(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    socket = client->getSocket();
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::ReadSlot);

}

void MainWindow::ReadSlot()
{
    socket = (QTcpSocket*)sender();
    Data = socket->readAll();
    switch (Data.at(0)) {
    case Client::ServerCodes::NEW_GAME:
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QTableWidgetItem *newItem = new QTableWidgetItem(Data.mid(3, Data.size()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, newItem);
        newItem = new QTableWidgetItem(ui->comboBox->itemText(Data.at(1)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, newItem);
        newItem = new QTableWidgetItem(ui->comboBox_2->itemText(Data.at(2)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, newItem);
        break;
    }
    case Client::ServerCodes::START_GAME:
    {
        if(Data.mid(3, Data.size()) == client->getNickname())
        {
            if(Data.at(1))
            {
                client->setColor(Color::WHITE);
            }
            else
            {
                client->setColor(Color::BLACK);
            }
        }
        else
        {
            if(Data.at(1))
            {
                client->setColor(Color::BLACK);
            }
            else
            {
                client->setColor(Color::WHITE);
            }
        }

        switch (Data.at(2))     {
        case 1:
            game = new GameWindow(client,60,1 ,this);
            break;
        case 2:
            game = new GameWindow(client,180,2 ,this);
            break;
        case 3:
            game = new GameWindow(client,300,0 ,this);
            break;
        case 4:
            game = new GameWindow(client,600,0 ,this);
            break;
        case 5:
            game = new GameWindow(client,900, 10 ,this);
            break;
        default:
            game = new GameWindow(client, 600, 0, this);
            break;
        }
        game->showFullScreen();
        this->hide();
    }
    default:
    {
        game->setData(Data);
        break;
    }
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_confirmNick_pushButton_clicked()
{
    if(ui->lineEdit->text()!="")
    {

        Data.clear();
        Data.push_back(Client::SenderCodes::CONNECTION_USER);
        QString str = ui->lineEdit->text();
        client->setNickname(str);
        Data.push_back(str.toUtf8());
        socket->write(Data);

        ui->comboBox->setVisible(1);
        ui->comboBox_2->setVisible(1);
        ui->createGame_pushButton->setVisible(1);
        ui->connect_pushButton->setVisible(1);
        ui->tableWidget->setVisible(1);
        ui->label->setVisible(1);
        ui->label_2->setVisible(0);
        ui->confirmNick_pushButton->setVisible(0);
        ui->lineEdit->setVisible(0);
    }
}


void MainWindow::on_connect_pushButton_clicked()
{
    Data.clear();
    Data.push_back(Client::SenderCodes::CONNECT_GAME);
    if(ui->tableWidget->currentRow() != -1){
        Data.push_back(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toUtf8());

        socket->write(Data);

    }

}


void MainWindow::on_createGame_pushButton_clicked()
{
    if(ui->comboBox->currentIndex() == 0 || ui->comboBox_2->currentIndex() == 0) return;
    Data.clear();
    Data.push_back(Client::SenderCodes::CREATE_GAME);
    Data.push_back(ui->comboBox->currentIndex());
    Data.push_back(ui->comboBox_2->currentIndex());
    Data.push_back(client->getNickname().toUtf8());
    socket->write(Data);
    ui->createGame_pushButton->setVisible(0);
    ui->connect_pushButton->setVisible(0);
}


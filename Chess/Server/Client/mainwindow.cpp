#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    QWidget::repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    game=new chess::Game();
    game->startNewGame();
    QPen pen;
    QPainter painter(this);
    //QPainter text(this);
    painter.setFont(QFont("Times", 14, QFont::Bold));
    //chess::Game game;
    //game.startNewGame();
    for(int i = 0; i <8;++i)
    {
        for(int j = 0; j<8;++j)
        {
            QRect rect(30+i*100,30+j*100,100,100);
            painter.setBrush(QBrush((i+j)%2 == 1 ? Qt::darkGray:Qt::lightGray));
            painter.drawRect(rect);
            if(j==7) painter.drawText(QPoint(110+i*100,825),QChar('a'+i));
            if(game->getBoard().getGrid()[i][j].get()->getType()==PieceType::PAWN&&game->getBoard().getGrid()[i][j].get()->getColor()==Color::BLACK)
            //if(j==1)
            {
                painter.drawImage(rect, QImage("black_pawn.png"));
            }
        }
        painter.drawText(QPoint(35, 50+i*100),QChar('1' + 7 - i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

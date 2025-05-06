#include <iostream>
#include <Windows.h>
#include "../Chess-Core/src/Game.h"
//using namespace chess;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    chess::Game game;
    game.startNewGame();

    chess::Position e2 = chess::Position::fromString("e2");
    chess::Position e4 = chess::Position::fromString("e4");

    while (true)
    {
        std::string a, b;
        std::cin >> a >> b;
        system("cls");
        e2 = chess::Position::fromString(a);
        e4 = chess::Position::fromString(b);
        auto moves = game.getBoard().getLegalMoves(e2);
        for (int i = 0; i < moves.size(); ++i)
        {
            std::cout << moves[i].toChessNotation() << std::endl;
        }

        if (game.makeMove(e2, e4)) {
            std::cout << "Ход выполнен: " << game.getLastMoveNotation() << std::endl;
        }


        char c = ' ';
        for (int i = 7; i >= 0; --i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (game.getBoard().getGrid()[i][j].get() == nullptr)
                {
                    std::cout << ' ';
                    continue;
                }
                switch (game.getBoard().getGrid()[i][j].get()->getType())
                {
                case PieceType::PAWN:
                {
                    c = 'P';
                    break;
                }
                case PieceType::ROOK:
                {
                    c = 'R';
                    break;
                }
                case PieceType::KING:
                {
                    c = 'K';
                    break;
                }
                case PieceType::KNIGHT:
                {
                    c = '7';
                    break;
                }
                case PieceType::BISHOP:
                {
                    c = 'B';
                    break;
                }
                case PieceType::QUEEN:
                {
                    c = 'Q';
                    break;
                }
                default:
                    c = '0';
                    break;
                }
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
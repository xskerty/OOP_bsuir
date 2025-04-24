#pragma once
#include "Board.h"
#include "Enums.h"
#include <vector>
#include <string>

namespace chess {

    class Game {
    public:
        Game();

        // ���������� �����
        void startNewGame();
        bool makeMove(const Position& from, const Position& to);
        void resign(Color player);
        bool offerDraw(Color player);

        // ��������� ����
        GameStatus getStatus() const;
        Color getCurrentTurn() const;
        const Board& getBoard() const;
        Color getWinner() const;
        bool isGameOver() const;

        // ������� ����
        const std::vector<std::string>& getMoveHistory() const;
        std::string getLastMoveNotation() const;

        // ��������� ��������
        void setTimeControl(int minutes);
        int getRemainingTime(Color player) const;

    private:
        Board board;
        GameStatus status;
        Color currentTurn;
        Color winner;
        bool drawOffered;

        // ������� ����
        std::vector<std::string> moveHistory;

        // ��������� ��������
        std::array<int, 2> remainingTime; // [white, black]

        // ��������������� ������
        void switchTurn();
        void updateGameStatus();
        void recordMove(const Position& from, const Position& to, PieceType promotion = PieceType::NONE);
        std::string moveToNotation(const Position& from, const Position& to, PieceType promotion) const;
        void handleGameEnd(GameStatus endStatus);
    };

} // namespace chess
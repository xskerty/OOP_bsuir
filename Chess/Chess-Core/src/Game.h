#pragma once
#include "Board.h"
#include "Enums.h"
#include <vector>
#include <string>

namespace chess {

    class Game {
    public:
        Game();

        // Управление игрой
        void startNewGame();
        bool makeMove(const Position& from, const Position& to);
        void resign(Color player);
        bool offerDraw(Color player);

        // Состояние игры
        GameStatus getStatus() const;
        Color getCurrentTurn() const;
        const Board& getBoard() const;
        Color getWinner() const;
        bool isGameOver() const;

        // История игры
        const std::vector<std::string>& getMoveHistory() const;
        std::string getLastMoveNotation() const;

        // Временной контроль
        void setTimeControl(int minutes);
        int getRemainingTime(Color player) const;

    private:
        Board board;
        GameStatus status;
        Color currentTurn;
        Color winner;
        bool drawOffered;

        // История игры
        std::vector<std::string> moveHistory;

        // Временной контроль
        std::array<int, 2> remainingTime; // [white, black]

        // Вспомогательные методы
        void switchTurn();
        void updateGameStatus();
        void recordMove(const Position& from, const Position& to, PieceType promotion = PieceType::NONE);
        std::string moveToNotation(const Position& from, const Position& to, PieceType promotion) const;
        void handleGameEnd(GameStatus endStatus);
    };

} // namespace chess
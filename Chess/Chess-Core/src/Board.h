#pragma once
#include "Position.h"
#include "Piece.h"
#include <array>
#include <memory>
#include <vector>
#include <unordered_map>

namespace chess {

    class Board {
    public:
        static const int BOARD_SIZE = 8;

        Board();
        Board(const Board& other); // Копирование
        void initializePieces();
        // Основные методы
        bool movePiece(const Position& from, const Position& to);
        bool isMoveLegal(const Position& from, const Position& to) const;

        // Доступ к данным
        Piece* getPiece(const Position& pos) const;
        const std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE>& getGrid() const { return grid; };

        // Состояние игры
        bool isCheck(Color color) const;
        bool isCheckmate(Color color) const;
        bool isStalemate(Color color) const;

        // Специальные ходы
        bool canCastle(Color color, bool kingside) const;
        bool isEnPassantPossible(const Position& pawnPos, const Position& targetPos) const;

        // Валидация
        std::vector<Position> getLegalMoves(const Position& from) const;
        bool wouldBeCheck(const Position& from, const Position& to) const;

    private:
        std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> grid;
        Position enPassantTarget; // Позиция для взятия на проходе

        // Вспомогательные методы
        
        Position findKing(Color color) const;
        bool isSquareAttacked(const Position& pos, Color attackerColor) const;
        bool hasAnyLegalMoves(Color color) const;

        // Специальные правила
        void handleEnPassant(const Position& from, const Position& to);
        void handleCastling(const Position& from, const Position& to);
        void handlePromotion(const Position& pos); //, PieceType type
    };

} 
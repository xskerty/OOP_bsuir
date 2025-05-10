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
        Board(const Board& other); // �����������
        void initializePieces();
        // �������� ������
        bool movePiece(const Position& from, const Position& to);
        bool isMoveLegal(const Position& from, const Position& to) const;

        // ������ � ������
        Piece* getPiece(const Position& pos) const;
        const std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE>& getGrid() const { return grid; };

        // ��������� ����
        bool isCheck(Color color) const;
        bool isCheckmate(Color color) const;
        bool isStalemate(Color color) const;

        // ����������� ����
        bool canCastle(Color color, bool kingside) const;
        bool isEnPassantPossible(const Position& pawnPos, const Position& targetPos) const;

        // ���������
        std::vector<Position> getLegalMoves(const Position& from) const;
        bool wouldBeCheck(const Position& from, const Position& to) const;

    private:
        std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> grid;
        Position enPassantTarget; // ������� ��� ������ �� �������

        // ��������������� ������
        
        Position findKing(Color color) const;
        bool isSquareAttacked(const Position& pos, Color attackerColor) const;
        bool hasAnyLegalMoves(Color color) const;

        // ����������� �������
        void handleEnPassant(const Position& from, const Position& to);
        void handleCastling(const Position& from, const Position& to);
        void handlePromotion(const Position& pos); //, PieceType type
    };

} 
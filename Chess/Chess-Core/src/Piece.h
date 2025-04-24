#pragma once
#include "Position.h"
#include "Enums.h"
#include <memory>
#include <vector>

namespace chess {

    class Piece {
    protected:
        Color color;
        PieceType type;
        bool hasMoved = false;

    public:
        Piece(Color c, PieceType t) : color(c), type(t) {}
        virtual ~Piece() = default;

        virtual bool isValidMove(const Position& from, const Position& to, bool isCapture) const = 0;
        virtual std::vector<Position> getPath(const Position& from, const Position& to) const = 0;
        virtual std::unique_ptr<Piece> clone() const = 0;

        Color getColor() const { return color; }
        PieceType getType() const { return type; }
        bool hasPieceMoved() const { return hasMoved; }

        void markAsMoved() { hasMoved = true; }
        void resetMoveStatus() { hasMoved = false; }

        static std::unique_ptr<Piece> create(PieceType type, Color color);

        virtual bool canCastle() const { return false; }
        virtual bool canEnPassant() const { return false; }
        virtual bool canPromote() const { return false; }
    };
}
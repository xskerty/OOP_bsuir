#pragma once
#include "../Piece.h"

namespace chess
{
    class Pawn : public Piece {
    public:
        Pawn(Color c);
        bool isValidMove(const Position& from, const Position& to, bool isCapture) const override;
        std::vector<Position> getPath(const Position& from, const Position& to) const override;
        std::unique_ptr<Piece> clone() const override;
        bool canEnPassant() const override { return true; }
        bool canPromote() const override { return true; }
    };
}
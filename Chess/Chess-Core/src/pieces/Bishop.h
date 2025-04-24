#pragma once
#include "../Piece.h"

namespace chess
{
    class Bishop : public Piece {
    public:
        Bishop(Color c);
        bool isValidMove(const Position& from, const Position& to, bool isCapture) const override;
        std::vector<Position> getPath(const Position& from, const Position& to) const override;
        std::unique_ptr<Piece> clone() const override;
    };
}
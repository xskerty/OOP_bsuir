#include "Knight.h"

namespace chess
{
    Knight::Knight(Color c) : Piece(c, PieceType::KNIGHT) {}

    bool Knight::isValidMove(const Position& from, const Position& to, bool isCapture) const {
        int dx = abs(to.x - from.x);
        int dy = abs(to.y - from.y);
        return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
    }

    std::vector<Position> Knight::getPath(const Position& from, const Position& to) const {
        return { to };
    }

    std::unique_ptr<Piece> Knight::clone() const {
        return std::make_unique<Knight>(*this);
    }
}
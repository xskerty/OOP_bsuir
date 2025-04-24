#include "King.h"

namespace chess
{
    King::King(Color c) : Piece(c, PieceType::KING) {}

    bool King::isValidMove(const Position& from, const Position& to, bool isCapture) const {
        int dx = abs(to.x - from.x);
        int dy = abs(to.y - from.y);

        if (dx <= 1 && dy <= 1) return true;

        if (!hasMoved && dy == 0 && dx == 2) return true;

        return false;
    }

    std::vector<Position> King::getPath(const Position& from, const Position& to) const {
        std::vector<Position> path;
        path.push_back(to);

        return path;
    }

    std::unique_ptr<Piece> King::clone() const {
        return std::make_unique<King>(*this);
    }
}
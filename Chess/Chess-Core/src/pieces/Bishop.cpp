#include "Bishop.h"

namespace chess 
{
    Bishop::Bishop(Color c) : Piece(c, PieceType::BISHOP) {}

    bool Bishop::isValidMove(const Position& from, const Position& to, bool isCapture) const {
        return abs(to.x - from.x) == abs(to.y - from.y);
    }

    std::vector<Position> Bishop::getPath(const Position& from, const Position& to) const {
        std::vector<Position> path;
        int dx = (to.x > from.x) ? 1 : -1;
        int dy = (to.y > from.y) ? 1 : -1;

        for (int x = from.x + dx, y = from.y + dy; x != to.x; x += dx, y += dy) {
            path.emplace_back(x, y);
        }
        path.push_back(to);
        return path;
    }

    std::unique_ptr<Piece> Bishop::clone() const {
        return std::make_unique<Bishop>(*this);
    }
}
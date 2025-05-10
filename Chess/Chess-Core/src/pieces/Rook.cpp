#include "Rook.h"

namespace chess
{
    Rook::Rook(Color c) : Piece(c, PieceType::ROOK) {}

    bool Rook::isValidMove(const Position& from, const Position& to, bool isCapture) const {
        return (from.x == to.x) || (from.y == to.y);
    }

    std::vector<Position> Rook::getPath(const Position& from, const Position& to) const {
        std::vector<Position> path;
        if (from.x == to.x) {
            int step = (to.y > from.y) ? 1 : -1;
            for (int y = from.y + step; y != to.y; y += step) {
                path.emplace_back(from.x, y);
            }
        }
        else {
            int step = (to.x > from.x) ? 1 : -1;
            for (int x = from.x + step; x != to.x; x += step) {
                path.emplace_back(x, from.y);
            }
        }
        path.push_back(to);
        return path;
    }

    std::unique_ptr<Piece> Rook::clone() const {
        return std::make_unique<Rook>(*this);
    }
}
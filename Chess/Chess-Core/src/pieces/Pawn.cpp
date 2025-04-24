#include "Pawn.h"

namespace chess
{
    Pawn::Pawn(Color c) : Piece(c, PieceType::PAWN) {}

    bool Pawn::isValidMove(const Position& from, const Position& to, bool isCapture) const {
        int direction = (color == Color::WHITE) ? 1 : -1;
        int startRow = (color == Color::WHITE) ? 1 : 6;

        if (!isCapture) {
            if (from.x == to.x) {
                if (to.y - from.y == direction) return true;
                if (from.y == startRow && to.y - from.y == 2 * direction) return true;
            }
            return false;
        }

        return abs(to.x - from.x) == 1 && to.y - from.y == direction;
    }

    std::vector<Position> Pawn::getPath(const Position& from, const Position& to) const {
        std::vector<Position> path;
        if (from.x == to.x) {
            int step = (to.y > from.y) ? 1 : -1;
            for (int y = from.y + step; y != to.y; y += step) {
                path.emplace_back(from.x, y);
            }
        }
        path.push_back(to);
        return path;
    }

    std::unique_ptr<Piece> Pawn::clone() const {
        return std::make_unique<Pawn>(*this);
    }
}
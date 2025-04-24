#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

namespace chess
{
    Queen::Queen(Color c) : Piece(c, PieceType::QUEEN) {}

    bool Queen::isValidMove(const Position& from, const Position& to, bool isCapture) const {
        return (from.x == to.x) || (from.y == to.y) ||
            (abs(to.x - from.x) == abs(to.y - from.y));
    }

    std::vector<Position> Queen::getPath(const Position& from, const Position& to) const {
        if (from.x == to.x || from.y == to.y) {

            Rook temp(color);
            return temp.getPath(from, to);
        }
        else {
            Bishop temp(color);
            return temp.getPath(from, to);
        }
    }

    std::unique_ptr<Piece> Queen::clone() const {
        return std::make_unique<Queen>(*this);
    }
}
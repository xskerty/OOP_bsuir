#include <stdexcept>
#include "Position.h"


namespace chess {

    Position::Position(int x, int y) : x(x), y(y) {}

    bool Position::isValid() const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    Position Position::fromChessNotation(char file, char rank) {
        if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
            throw std::invalid_argument("Invalid chess notation");
        }
        return Position(file - 'a', rank - '1');
    }

    Position Position::fromString(const std::string& str) {
        if (str.length() != 2) {
            throw std::invalid_argument("Position string must be 2 characters long");
        }
        return fromChessNotation(str[0], str[1]);
    }

    std::string Position::toChessNotation() const {
        if (!isValid()) return "??";
        return std::string(1, 'a' + x) + std::to_string(y + 1);
    }

    std::string Position::toString() const {
        return toChessNotation();
    }

    bool Position::isAdjacent(const Position& other) const {
        return distanceTo(other) == 1;
    }

    bool Position::isSameLine(const Position& other) const {
        return (x == other.x) || (y == other.y);
    }

    bool Position::isSameDiagonal(const Position& other) const {
        return std::abs(x - other.x) == std::abs(y - other.y);
    }

    int Position::distanceTo(const Position& other) const {
        return std::max(std::abs(x - other.x), std::abs(y - other.y));
    }

    bool Position::operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool Position::operator!=(const Position& other) const {
        return !(*this == other);
    }

    bool Position::operator<(const Position& other) const {
        return (y < other.y) || (y == other.y && x < other.x);
    }

    size_t Position::Hash::operator()(const Position& pos) const {
        return pos.x * 8 + pos.y;
    }

}
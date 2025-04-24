#pragma once
#include <string>
#include <utility> 
#include <cmath>   

namespace chess {

    class Position {
    public:
        int x; // 0-7 (a-h)
        int y; // 0-7 (1-8)

        // Конструкторы
        Position(int x = -1, int y = -1);

        // Фабричные методы
        static Position fromChessNotation(char file, char rank);
        static Position fromString(const std::string& str); // "e4" → (4, 3)

        // Проверки
        bool isValid() const;
        bool isAdjacent(const Position& other) const;

        // Преобразования
        std::string toChessNotation() const;
        std::string toString() const; // (4, 3) → "e4"

        // Геометрические проверки
        bool isSameLine(const Position& other) const;
        bool isSameDiagonal(const Position& other) const;
        int distanceTo(const Position& other) const;

        // Операторы
        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;
        bool operator<(const Position& other) const; // Для std::map

        // Хеширование
        struct Hash {
            size_t operator()(const Position& pos) const;
        };
    };

}
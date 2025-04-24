#pragma once

enum class Color {
    WHITE,
    BLACK,
    NONE
};

enum class PieceType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN,
    NONE
};

enum class GameStatus {
    NOT_STARTED,
    ONGOING,
    CHECK,
    CHECKMATE,
    STALEMATE,
    DRAW,
    RESIGNATION
};

inline char pieceTypeToSymbol(PieceType type) {
    switch (type) {
    case PieceType::KING:   return 'K';
    case PieceType::QUEEN:  return 'Q';
    case PieceType::ROOK:   return 'R';
    case PieceType::BISHOP: return 'B';
    case PieceType::KNIGHT: return 'N';
    case PieceType::PAWN:   return 'P';
    default: return '?';
    }
}
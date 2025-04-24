#include "Piece.h"
#include "pieces/Pawn.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Rook.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

namespace chess {

    std::unique_ptr<Piece> Piece::create(PieceType type, Color color) {
        switch (type) {
        case PieceType::PAWN:   return std::make_unique<Pawn>(color);
        case PieceType::ROOK:   return std::make_unique<Rook>(color);
        case PieceType::KNIGHT: return std::make_unique<Knight>(color);
        case PieceType::BISHOP: return std::make_unique<Bishop>(color);
        case PieceType::QUEEN:  return std::make_unique<Queen>(color);
        case PieceType::KING:   return std::make_unique<King>(color);
        default: return NULL;
        }
    }
}
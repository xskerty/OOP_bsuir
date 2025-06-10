#include <stdexcept>
#include "Board.h"
#include "Piece.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"


namespace chess {

    Board::Board() {
        initializePieces();
    }

    Board::Board(const Board& other) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                if (other.grid[y][x]) {
                    grid[y][x] = other.grid[y][x]->clone();
                }
            }
        }
        enPassantTarget = other.enPassantTarget;
    }

    void Board::initializePieces() {
        for (auto& row : grid) {
            for (auto& square : row) {
                square.reset();
            }
        }

        for (int x = 0; x < BOARD_SIZE; ++x) {
            grid[1][x] = std::make_unique<Pawn>(Color::WHITE);
            grid[6][x] = std::make_unique<Pawn>(Color::BLACK);
        }

        grid[0][0] = std::make_unique<Rook>(Color::WHITE);
        grid[0][7] = std::make_unique<Rook>(Color::WHITE);
        grid[7][0] = std::make_unique<Rook>(Color::BLACK);
        grid[7][7] = std::make_unique<Rook>(Color::BLACK);

        grid[0][1] = std::make_unique<Knight>(Color::WHITE);
        grid[0][6] = std::make_unique<Knight>(Color::WHITE);
        grid[7][1] = std::make_unique<Knight>(Color::BLACK);
        grid[7][6] = std::make_unique<Knight>(Color::BLACK);

        grid[0][2] = std::make_unique<Bishop>(Color::WHITE);
        grid[0][5] = std::make_unique<Bishop>(Color::WHITE);
        grid[7][2] = std::make_unique<Bishop>(Color::BLACK);
        grid[7][5] = std::make_unique<Bishop>(Color::BLACK);

        grid[0][3] = std::make_unique<Queen>(Color::WHITE);
        grid[7][3] = std::make_unique<Queen>(Color::BLACK);

        grid[0][4] = std::make_unique<King>(Color::WHITE);
        grid[7][4] = std::make_unique<King>(Color::BLACK);

        enPassantTarget = Position(-1, -1);
    }

    bool Board::movePiece(const Position& from, const Position& to) {
        if (!from.isValid() || !to.isValid()) return false;

        Piece* piece = getPiece(from);
        if (!piece || !isMoveLegal(from, to)) return false;

        if (piece->getType() == PieceType::KING && abs(from.x - to.x) == 2 && canCastle(piece->getColor(),(to.x > from.x))) {
            grid[to.y][to.x] = std::move(grid[from.y][from.x]);
            piece->markAsMoved();
            handleCastling(from, to); 
            return true;
        }
        else {
            handleEnPassant(from, to);
        }

        grid[to.y][to.x] = std::move(grid[from.y][from.x]);
        piece->markAsMoved();

        if (piece->getType() == PieceType::PAWN && (to.y == 0 || to.y == 7)) {
            handlePromotion(to);
        }

        return true;
    }

    bool Board::isMoveLegal(const Position& from, const Position& to) const {
        if (!from.isValid() || !to.isValid()||from == to) return false;
        if (getPiece(to) != nullptr && getPiece(from)->getColor() == getPiece(to)->getColor()) return false;

        const Piece* piece = getPiece(from);
        if (!piece) return false;


        if (piece->getType() == PieceType::PAWN && abs(from.x - to.x) == 1 && abs(from.y - to.y) == 1 && to == enPassantTarget) {
            return true;
        }

        const Piece* targetPiece = getPiece(to);
        bool isCapture = targetPiece && targetPiece->getColor() != piece->getColor();

        if (!piece->isValidMove(from, to, isCapture)) {
            return false;
        }

        if(piece->getType()==PieceType::KING&& isCheck(piece->getColor()) &&abs(from.x-to.x) == 2) return false;

        if (piece->getType() != PieceType::KNIGHT) {
            auto path = piece->getPath(from, to);
            for (const auto& pos : path) {
                if (getPiece(pos) != nullptr && pos != to) {
                    return false;
                }
            }
        }

        if (wouldBeCheck(from, to)) {
            return false;
        }

        return true;
    }

    Piece* Board::getPiece(const Position& pos) const {
        if (!pos.isValid()) return nullptr;
        return grid[pos.y][pos.x].get();
    }

    Position Board::findKing(Color color) const {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                const auto& piece = grid[y][x];
                if (piece && piece->getType() == PieceType::KING &&
                    piece->getColor() == color) {
                    return Position(x, y);
                }
            }
        }
        throw std::runtime_error("King not found!");
    }

    bool Board::isSquareAttacked(const Position& pos, Color attackerColor) const {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                const Piece* piece = grid[y][x].get();
                if (piece && piece->getColor() == attackerColor) {
                    Position attackerPos(x, y);
                    if (piece->isValidMove(attackerPos, pos, true)) {
                        if (piece->getType() != PieceType::PAWN &&
                            piece->getType() != PieceType::KNIGHT) {
                            auto path = piece->getPath(attackerPos, pos);
                            bool pathClear = true;
                            for (const auto& p : path) {
                                if (getPiece(p) && p != pos) {
                                    pathClear = false;
                                    break;
                                }
                            }
                            if (!pathClear) continue;
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool Board::isCheck(Color color) const {
        Position kingPos = findKing(color);
        return isSquareAttacked(kingPos, color == Color::WHITE ? Color::BLACK : Color::WHITE);
    }

    bool Board::wouldBeCheck(const Position& from, const Position& to) const {
        Board tempBoard(*this);
        tempBoard.grid[to.y][to.x] = std::move(tempBoard.grid[from.y][from.x]);
        return tempBoard.isCheck(getPiece(from)->getColor());
    }

    bool Board::isCheckmate(Color color) const {
        if (!isCheck(color)) return false;
        return !hasAnyLegalMoves(color);
    }

    bool Board::hasAnyLegalMoves(Color color) const {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                const Piece* piece = grid[y][x].get();
                if (piece && piece->getColor() == color) {
                    Position from(x, y);
                    auto moves = getLegalMoves(from);
                    if (!moves.empty()) return true;
                }
            }
        }
        return false;
    }

    std::vector<Position> Board::getLegalMoves(const Position& from) const {
        std::vector<Position> legalMoves;
        const Piece* piece = getPiece(from);
        if (!piece) return legalMoves;

        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                Position to(x, y);
                if (isMoveLegal(from, to)) {
                    legalMoves.push_back(to);
                }
            }
        }

        return legalMoves;
    }

    void Board::handleEnPassant(const Position& from, const Position& to) {
        Piece* piece = getPiece(from);
        if (piece->getType() == PieceType::PAWN &&
            std::abs(from.y - to.y) == 2) {
            enPassantTarget = Position(from.x, (from.y + to.y) / 2);
        }
        else if (to == enPassantTarget &&
            piece->getType() == PieceType::PAWN) {
            int capturedPawnY = piece->getColor() == Color::WHITE ? to.y - 1 : to.y + 1;
            grid[capturedPawnY][to.x].reset();
        }
        else {
            enPassantTarget = Position(-1, -1);
        }
    }

    void Board::handleCastling(const Position& from, const Position& to) {
        bool isKingside = (to.x > from.x);
        int rookStartX = isKingside ? 7 : 0;
        int rookNewX = isKingside ? 5 : 3;

        Position rookPos(rookStartX, from.y);
        Position newRookPos(rookNewX, from.y);

        grid[newRookPos.y][newRookPos.x] = std::move(grid[rookPos.y][rookPos.x]);
        grid[newRookPos.y][newRookPos.x]->markAsMoved();
    }

    bool Board::isStalemate(Color color) const {
        if (isCheck(color)) {
            return false; 
        }

        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                const Piece* piece = grid[y][x].get();
                if (piece && piece->getColor() == color) {
                    Position from(x, y);
                    auto moves = getLegalMoves(from);
                    if (!moves.empty()) {
                        return false; 
                    }
                }
            }
        }

        return true; 
    }

    bool Board::canCastle(Color color, bool kingside) const {
        int row = (color == Color::WHITE) ? 0 : 7;
        int kingX = 4;
        int rookX = kingside ? 7 : 0;
        int step = kingside ? 1 : -1;

        const Piece* king = grid[row][kingX].get();
        const Piece* rook = grid[row][rookX].get();
        if (!king || !rook ||
            king->getType() != PieceType::KING ||
            rook->getType() != PieceType::ROOK ||
            king->hasPieceMoved() ||
            rook->hasPieceMoved()) {
            return false;
        }

        for (int x = kingX + step; x != rookX; x += step) {
            if (grid[row][x].get()!=nullptr) {
                return false;
            }
        }

        for (int x = kingX; x != kingX + (step * 2); x += step) {
            if (isSquareAttacked(Position(x, row), color==Color::WHITE ? Color::BLACK : Color::WHITE)) {
                return false;
            }
        }

        return true;
    }

    bool Board::isEnPassantPossible(const Position& pawnPos, const Position& targetPos) const {
        if (!enPassantTarget.isValid()) {
            return false;
        }

        const Piece* pawn = getPiece(pawnPos);
        if (!pawn || pawn->getType() != PieceType::PAWN) {
            return false;
        }

        if (targetPos != enPassantTarget) {
            return false;
        }

        int dx = abs(pawnPos.x - targetPos.x);
        int dy = abs(pawnPos.y - targetPos.y);
        if (dx != 1 || dy != 1) {
            return false;
        }

        int capturedPawnY = (pawn->getColor() == Color::WHITE) ? targetPos.y - 1 : targetPos.y + 1;
        const Piece* capturedPawn = getPiece(Position(targetPos.x, capturedPawnY));
        if (!capturedPawn ||
            capturedPawn->getType() != PieceType::PAWN ||
            capturedPawn->getColor() == pawn->getColor()) {
            return false;
        }

        return true;
    }

    void Board::handlePromotion(const Position& pos) { //, PieceType type
        grid[pos.y][pos.x] = std::make_unique<Queen>(grid[pos.y][pos.x]->getColor());
        /*switch (type)
        {

        case PieceType::QUEEN:
        {
            
            break;
        }
        case PieceType::ROOK:
        {
            grid[pos.y][pos.x] = std::make_unique<Rook>(grid[pos.y][pos.x]->getColor());
            break;
        }
        case PieceType::KNIGHT:
        {
            grid[pos.y][pos.x] = std::make_unique<Knight>(grid[pos.y][pos.x]->getColor());
            break;
        }
        case PieceType::BISHOP:
        {
            grid[pos.y][pos.x] = std::make_unique<Bishop>(grid[pos.y][pos.x]->getColor());
            break;
        }*/
    }
    

    
}

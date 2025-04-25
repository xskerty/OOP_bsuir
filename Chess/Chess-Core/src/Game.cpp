#include "Game.h"
#include "Piece.h"

namespace chess {

    Game::Game() : status(GameStatus::NOT_STARTED),
        currentTurn(Color::WHITE),
        winner(Color::NONE),
        drawOffered(false) {
        remainingTime.fill(0);
    }

    void Game::startNewGame() {
        board.initializePieces();
        status = GameStatus::ONGOING;
        currentTurn = Color::WHITE;
        winner = Color::NONE;
        drawOffered = false;
        moveHistory.clear();
    }

    bool Game::makeMove(const Position& from, const Position& to) {
        if (status != GameStatus::ONGOING) return false;

        // Проверяем, что ход делает правильный игрок
        Piece* piece = board.getPiece(from);
        if (!piece || piece->getColor() != currentTurn) {
            return false;
        }

        // Пробуем сделать ход
        if (!board.movePiece(from, to)) {
            return false;
        }

        // Записываем ход в историю
        recordMove(from, to);

        // Обновляем состояние игры
        switchTurn();
        updateGameStatus();

        return true;
    }

    void Game::resign(Color player) {
        if (status == GameStatus::ONGOING) {
            winner = (player == Color::WHITE) ? Color::BLACK : Color::WHITE;
            handleGameEnd(GameStatus::RESIGNATION);
        }
    }

    bool Game::offerDraw(Color player) {
        if (status == GameStatus::ONGOING && player == currentTurn) {
            drawOffered = true;
            return true;
        }
        return false;
    }

    GameStatus Game::getStatus() const {
        return status;
    }

    Color Game::getCurrentTurn() const {
        return currentTurn;
    }

    const Board& Game::getBoard() const {
        return board;
    }

    Color Game::getWinner() const {
        return winner;
    }

    bool Game::isGameOver() const {
        return status != GameStatus::ONGOING && status != GameStatus::NOT_STARTED;
    }

    const std::vector<std::string>& Game::getMoveHistory() const {
        return moveHistory;
    }

    std::string Game::getLastMoveNotation() const {
        return moveHistory.empty() ? "" : moveHistory.back();
    }

    void Game::setTimeControl(int minutes) {
        remainingTime[static_cast<int>(Color::WHITE)] = minutes * 60;
        remainingTime[static_cast<int>(Color::BLACK)] = minutes * 60;
    }

    int Game::getRemainingTime(Color player) const {
        return remainingTime[static_cast<int>(player)];
    }

    // Приватные методы

    void Game::switchTurn() {
        currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        drawOffered = false;
    }

    void Game::updateGameStatus() {
        if (board.isCheckmate(currentTurn)) {
            winner = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
            handleGameEnd(GameStatus::CHECKMATE);
        }
        else if (board.isStalemate(currentTurn)) {
            handleGameEnd(GameStatus::STALEMATE);
        }
        else if (board.isCheck(currentTurn)) {
            status = GameStatus::CHECK;
        }
        else {
            status = GameStatus::ONGOING;
        }
    }

    void Game::recordMove(const Position& from, const Position& to, PieceType promotion) {
        moveHistory.push_back(moveToNotation(from, to, promotion));
    }

    std::string Game::moveToNotation(const Position& from, const Position& to, PieceType promotion) const {
        std::string oss = "";
        const Piece* piece = board.getPiece(to); // Уже перемещена

        // Рокировка
        if (piece->getType() == PieceType::KING && abs(from.x - to.x) == 2) {
            return (to.x > from.x) ? "O-O" : "O-O-O";
        }

        // Обозначение фигуры (кроме пешки)
        if (piece->getType() != PieceType::PAWN) {
            oss += pieceTypeToSymbol(piece->getType());
        }

        // Исходная позиция (если нужно для однозначности)
        // (здесь можно добавить логику для неоднозначных ходов)

        // Взятие
        if (board.getPiece(to)) {
            if (piece->getType() == PieceType::PAWN) {
                oss += from.toChessNotation()[0]; // Буква колонки
            }
            oss += 'x';
        }

        // Целевая позиция
        oss += to.toChessNotation();

        // Превращение пешки
        if (promotion != PieceType::NONE) {
            oss += '=' << pieceTypeToSymbol(promotion);
        }

        // Шах и мат
        Board tempBoard(board);
        tempBoard.movePiece(from, to);
        if (tempBoard.isCheck(currentTurn)) {
            oss += (tempBoard.isCheckmate(currentTurn) ? '#' : '+');
        }

        return oss;
    }

    void Game::handleGameEnd(GameStatus endStatus) {
        status = endStatus;
        // Здесь можно добавить логику сохранения игры, уведомлений и т.д.
    }

} // namespace chess
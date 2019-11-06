#include "board.hpp"

Board::Board() : turn_{0} {}

// Source: Fhourstones Benchmark by John Tromp
// https://github.com/qu1j0t3/fhourstones
bool Board::isWon() const {
    uint64_t board = masks_[turn_];

    // check \ diagonal
    uint64_t y = board & (board >> 6);
    if (y & (y >> 2 * 6)) {
        return true;
    }

    // check horizontal
    y = board & (board >> 7);
    if (y & (y >> 2 * 7)) {
        return true;
    }
    
    // check / diagonal
    y = board & (board >> 8);
    if (y & (y >> 2 * 8)) {
        return true;
    }

    // check vertical
    y = board & (board >> 1);
    if (y & (y >> 2)) {
        return true;
    }

    return false;
}

vector<size_t> Board::getSuccessors() const {
    vector<size_t> sucs;

    return sucs;
}

ostream& Board::print(ostream& os) const {
    return os;
}

void handleMove(size_t move) {

}

ostream& operator<<(const ostream& os, const Board& board) {
    return board.print(os);
}
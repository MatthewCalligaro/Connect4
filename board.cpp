#include "board.hpp"

Board::Board() : turn_{0} {}

size_t Board::getTurn() const {
    return turn_;
}

// Source: Fhourstones Benchmark by John Tromp
// https://github.com/qu1j0t3/fhourstones
bool Board::isWon() const {
    // If player who most recently played won
    uint64_t board = masks_[!turn_];

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
    uint64_t invBoard = ~(masks_[0] | masks_[1]);

    // We can play in any column in which the top bit is open
    if ((invBoard >> 26) & 1) {
        sucs.push_back(3);
    }
    if ((invBoard >> 19) & 1) {
        sucs.push_back(2);
    }
    if ((invBoard >> 33) & 1) {
        sucs.push_back(4);
    }
    if ((invBoard >> 12) & 1) {
        sucs.push_back(1);
    }
    if ((invBoard >> 40) & 1) {
        sucs.push_back(5);
    }
    if ((invBoard >> 5) & 1) {
        sucs.push_back(0);
    }
    if ((invBoard >> 47) & 1) {
        sucs.push_back(6);
    }

    return sucs;
}

ostream& Board::print(ostream& os) const {
    const char chars[3] = {'.', 'X', 'O'};

    // Iterate through the board row by row left to right top to bottom
    size_t bit = 5;
    while (bit != 6) {
        os << chars[((masks_[0] << bit) & 1) + 2 * ((masks_[1] << bit) & 1)];
        if (bit > 41) os << endl;
        bit = (bit + 7) % 43;
    }

    return os;
}

void Board::handleMove(size_t move) {
    // Find the lowest open bit in the column chosen by move
    uint64_t board = masks_[0] | masks_[1];
    size_t bit = move * 7;
    while ((board >> bit) & 1) {
        ++bit;
    }

    // Place a piece at bit in the correct mask and toggle turn_
    masks_[turn_] |= (1 << bit);
    turn_ = !turn_;
}

ostream& operator<<(ostream& os, const Board& board) {
    return board.print(os);
}

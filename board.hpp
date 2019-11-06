#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <vector>
#include <ostream>

using namespace std;

class Board {
public:
    Board();
    Board(const Board& other) = default;
    ~Board() = default;
    Board& operator=(const Board& other) = default;


    bool isWon() const;
    vector<size_t> getSuccessors() const;
    ostream& print(ostream& os) const;

    void handleMove(size_t move);

private:
    uint64_t masks_[2] = {0, 0};
    size_t turn_;
};

ostream& operator<<(const ostream& os, const Board& board);

#endif // BOARD_HPP

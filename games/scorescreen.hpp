#include "../library/MAX7219lib.hpp"
#include "hwlib.hpp"

#ifndef SCORESCREEN_HPP
#define SCORESCREEN_HPP


class scorescreen {
private:
    MAX7219lib& max;
    int score;
public:
    scorescreen(MAX7219lib& max, int score);
    void displayScore();
    void displayDigit(int digit, int x, int y);
};


#endif //SCORESCREEN_HPP

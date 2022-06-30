#include "scorescreen.hpp"

scorescreen::scorescreen(MAX7219lib& max, int score):
max(max), score(score)
{
    displayScore();
};

void scorescreen::displayScore() {
    max.clear();
    int spacing = 0;
    int x = 6, y = 8;
    if (score > 99) {
        x = 11;
        spacing = 5;
    }
    else if (score > 9) {
        x = 9;
        spacing = 6;
    }

    do {
        displayDigit(score % 10, x, y);
        x -= spacing;
    } while (score /= 10);

    // draws a sad face
    max.setRectangle(5, 6, 1, 2);
    max.setRectangle(9, 10, 1, 2);
    max.setRectangle(5, 10, 4, 6);
    max.setPixel(5, 4, 0);
    max.setPixel(10, 4, 0);

    max.flush();
}

void scorescreen::displayDigit(int digit, int x, int y) {
    // all digits are 4x7
    switch (digit) {
        case 1:
            max.setPixel(x, y + 2);
            max.setPixel(x + 1, y + 1);
            max.setRectangle(x + 2, x + 2, y, y + 6);
            max.setRectangle(x, x + 3, y + 6, y + 6);
            break;
        case 2:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x, x + 2, y + 1, y + 2, 0);
            max.setRectangle(x + 1, x + 3, y + 4, y + 5, 0);
            break;
        case 3:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x, x + 2, y + 1, y + 2, 0);
            max.setRectangle(x, x + 2, y + 4, y + 5, 0);
            break;
        case 4:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x + 1, x + 2, y, y + 2, 0);
            max.setRectangle(x, x + 2, y + 4, y + 6, 0);
            break;
        case 5:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x + 1, x + 3, y + 1, y + 2, 0);
            max.setRectangle(x, x + 2, y + 4, y + 5, 0);
            break;
        case 6:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x + 1, x + 3, y + 1, y + 2, 0);
            max.setRectangle(x + 1, x + 2, y + 4, y + 5, 0);
            break;
        case 7:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x, x + 2, y + 1, y + 6, 0);
            break;
        case 8:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x + 1, x + 2, y + 1, y + 2, 0);
            max.setRectangle(x + 1, x + 2, y + 4, y + 5, 0);
            break;
        case 9:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x + 1, x + 2, y + 1, y + 2, 0);
            max.setRectangle(x, x + 2, y + 4, y + 5, 0);
            break;
        default:
            max.setRectangle(x, x + 3, y, y + 6);
            max.setRectangle(x + 1, x + 2, y + 1, y + 5, 0);
            break;
    }
}


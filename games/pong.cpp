#include "pong.hpp"

pong::pong(MAX7219lib& max, hwlib::port_in_from_pins_t& Vcontrols, hwlib::port_in_from_pins_t& Hcontrols):
max(max),
b(max),
top(max, 6, 0, 0, Hcontrols),
right(max, 15, 7, 1, Vcontrols),
bottom(max, 6, 15, 0, Hcontrols),
left(max, 0, 7, 1, Vcontrols)
{
    objects = {&b, &top, &right, &bottom, &left};
    start();
    hwlib::wait_ms(2000);
    game();
    end();
    hwlib::wait_ms(3000);
}

void pong::game() {
    bool firstFrame = true;
    while (!b.end) {
        max.clean();
        for (auto &o: objects) {
            for (auto &other: objects) {
                o->collision(*other);
            }
            o->update();
            o->draw();
        }
        max.flush();
        if (firstFrame) {
            hwlib::wait_ms(1000); // wait a second before beginning the game
            firstFrame = false;
        }
    }
    max.clear();


}

void pong::start() {
    max.clear();

    // shows the word PONG
    // P
    max.setRectangle(1, 6, 1, 6);
    max.setRectangle(2, 5, 2, 3, 0);
    max.setRectangle(2, 6, 5, 6, 0);

    // O
    max.setRectangle(9, 14, 1, 6);
    max.setRectangle(10, 13, 2, 5, 0);

    // N
    max.setRectangle(1, 1, 9, 14);
    max.setRectangle(6, 6, 9, 14);
    max.setPixel(2,10);
    max.setPixel(3,11);
    max.setPixel(4,12);
    max.setPixel(5,13);

    // G
    max.setRectangle(9, 14, 9, 14);
    max.setRectangle(10, 13, 10, 13, 0);
    max.setRectangle(14, 14, 10, 11, 0);
    max.setRectangle(12, 13, 12, 12);

    max.flush();
}

void pong::end() {
    scorescreen(max, b.gameScore);
}



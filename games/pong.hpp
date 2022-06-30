#include "pongobjects.hpp"
#include "hwlib.hpp"
#include "scorescreen.hpp"

#ifndef PONG_HPP
#define PONG_HPP


class pong {
private:
    MAX7219lib& max;
    ball b;
    paddle top, right, bottom, left;
    std::array<pongobject*, 5> objects;
public:
    pong(MAX7219lib& max, hwlib::port_in_from_pins_t& Vcontrols, hwlib::port_in_from_pins_t& Hcontrols);
    void game();
    void start();
    void end();

};


#endif //PONG_HPP

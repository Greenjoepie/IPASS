#include "../library/MAX7219lib.hpp"
#include "hwlib.hpp"
#include "pong.hpp"

#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP


class launcher {
private:
    MAX7219lib& max;
public:
    launcher(MAX7219lib& max, hwlib::port_in_from_pins_t& Vcontrols, hwlib::port_in_from_pins_t& Hcontrols);
    void start();
    void menu(hwlib::port_in_from_pins_t& Vcontrols, hwlib::port_in_from_pins_t& Hcontrols);
};


#endif //LAUNCHER_HPP

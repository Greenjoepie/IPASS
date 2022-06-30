#include "hwlib.hpp"
#include "library/MAX7219lib.hpp"
#include "games/launcher.hpp"
#include "test.cpp"

namespace target = hwlib::target;




int main(){
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto up = target::pin_in(target::pins::d28);        // up button    (pin 28)
    auto down = target::pin_in(target::pins::d31);      // down button  (pin 31)

    auto Vcontrols = port_in_from(up, down);            // vertical controls (because hwlib::ports are hard to work with

    auto left = target::pin_in(target::pins::d32);      // left button  (pin 32)
    auto right = target::pin_in(target::pins::d35);     // right button (pin 35)

    auto Hcontrols = port_in_from(left, right);         // horizontal controls

    auto din = target::pin_out(target::pins::d5);       // data in      (pin 5)
    auto cs = target::pin_out(target::pins::d4);        // chip select  (pin 4)
    auto clk = target::pin_out(target::pins::d3);       // clock        (pin 3)
    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);

    auto max = MAX7219lib(spi_bus, cs, 2, 2);

    auto game = launcher(max, Vcontrols, Hcontrols);













}



#include "library/MAX7219lib.hpp"
#include "hwlib.hpp"

namespace target = hwlib::target;

namespace test {
    void firstTest(MAX7219lib& max) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                max.clean();
                max.setPixel(j, i);
                max.flush();
                hwlib::wait_ms(5);
            }
        }
        max.clear();
        max.setPixel(5,5);
        max.flush();
        hwlib::wait_ms(100);
        max.setPixel(3,1);
        max.flush();
        hwlib::wait_ms(900);
    }

    void secondTest(MAX7219lib& max) {
        max.clear();
        //Y
        max.setPixel(0,0);
        max.setPixel(1,1);
        max.setPixel(3,1);
        max.setPixel(4,0);
        max.setRectangle(2, 2, 2, 4);

        //O
        max.setRectangle(6,9,0,4);
        max.setRectangle(7,8,1,3, 0);

        //U
        max.setRectangle(11, 11, 0, 3);
        max.setRectangle(15, 15, 0, 3);
        max.setRectangle(12, 14, 4, 4);

        max.flush();
        hwlib::wait_ms(500);


        //=
        max.setRectangle(1,4,6,6);
        max.setRectangle(1,4,9,9);

        max.flush();
        hwlib::wait_ms(500);

        //D
        max.setRectangle(6,6,6,9);
        max.setRectangle(9,9,7,8);
        max.setRectangle(7,8,6,6);
        max.setRectangle(7,8,9,9);

        //smallA
        max.setRectangle(14,14,7,9);
        max.setRectangle(11,11,7,9);
        max.setRectangle(12,13,6,6);
        max.setRectangle(12,13,8,8);

        max.flush();
        hwlib::wait_ms(500);

        //B
        max.setRectangle(1,2,11,15);
        max.setPixel(2,14,0);
        max.setPixel(2,12,0);
        max.setPixel(3,12,1);
        max.setPixel(3,14,1);

        //E
        max.setRectangle(5,6,11,15);
        max.setPixel(6,14,0);
        max.setPixel(6,12,0);

        //S
        max.setRectangle(8,9,15,15);
        max.setRectangle(9,10,11,11);
        max.setPixel(8,12);
        max.setPixel(9,13);
        max.setPixel(10,14);

        //T
        max.setRectangle(12,14,11,11);
        max.setRectangle(13,13,12,15);

        max.flush();
        hwlib::wait_ms(2000);
        max.clear();

    }

    void main() {
        WDT->WDT_MR = WDT_MR_WDDIS;

        auto din = target::pin_out(target::pins::d5);       // data in      (pin 5)
        auto cs = target::pin_out(target::pins::d4);        // chip select  (pin 4)
        auto clk = target::pin_out(target::pins::d3);       // clock        (pin 3)
        auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din, hwlib::pin_in_dummy);


        hwlib::cout << "Test for MAX7219 library.\n\n";
        hwlib::cout << "Testing every pixel individually with all grid width/height possibilities";
        auto max11 = MAX7219lib(spi_bus, cs, 1, 1);
        test::firstTest(max11);
        max11.~MAX7219lib();
        auto max21 = MAX7219lib(spi_bus, cs, 2, 1);
        test::firstTest(max21);
        max21.~MAX7219lib();
        auto max12 = MAX7219lib(spi_bus, cs, 1, 2);
        test::firstTest(max12);
        max12.~MAX7219lib();
        auto max22 = MAX7219lib(spi_bus, cs, 2, 2);
        test::firstTest(max22);
        hwlib::cout << "Testing motivational message on 2x2 grid";
        test::secondTest(max22);
        hwlib::cout << "Test finished.";

    }
}



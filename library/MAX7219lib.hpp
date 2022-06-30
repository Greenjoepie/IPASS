
//          Copyright Mathijs Koek 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include <cstring>
#ifndef MAX7219LIB_HPP
#define MAX7219LIB_HPP

///@file

/// \brief
/// MAX7219lib class
/// \details
/// This class is used to operate an up to 2x2 grid of LED matrices powered by the MAX7219 chip.
/// It has the ability to set a single pixel or a rectangle of pixels on the display, or clear it entirely.
/// While compatible with smaller grids, it is intended to be used with a 2x2 grid.
class MAX7219lib {
private:
    hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus;
    hwlib::target::pin_out& cs;
    int width, height;
    int matrixamount = width * height;
    bool grid[16][16] = {};

    void drawRow(int y, int data, int targetmatrix = 1);
    void flushOne(int targetx, int targety, int targetmatrix);
public:
    MAX7219lib(hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus, hwlib::target::pin_out& cs, int width, int height);
    void write(int regaddr, int data, hwlib::spi_bus::spi_transaction& transaction);
    void writeSet(int regaddr, int data);
    void no_op(int repeat);
    void setBrightness(int data);
    void setPixel(int x, int y, bool value = 1);
    bool getPixel(int x, int y);
    void setRectangle(int x, int end_x, int y, int end_y, bool value = 1);
    void clean();
    void clear();
    void flush();
};


#endif //MAX7219LIB_HPP

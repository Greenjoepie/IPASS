
//          Copyright Mathijs Koek 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "MAX7219lib.hpp"

///@file

/// \brief
/// MAX7219lib constructor
/// \details
/// The constructor for the MAX7219lib class.
/// It requires an spi_bus and a chip select pin setup from the Arduino Due.
/// It also requires the values equivalent to the width and height of your LED matrix grid.
MAX7219lib::MAX7219lib(hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus, hwlib::target::pin_out& cs, int width, int height):
spi_bus(spi_bus),
cs(cs),
width(width),
height(height)
{
    writeSet(0x0B, 0x07); // set scan limit
    clear();
    writeSet(0x0C, 0x01); // turn on display
    setBrightness(0);
    no_op(matrixamount - 1);
    hwlib::wait_ms(500);
}

/// \brief
/// Write function without sending data
/// \details
/// This function writes data to the MAX7219 without its own spi_transaction.
/// This means the data will not get read by the MAX7219 until the external spi_transaction is destroyed.
/// This is useful for when you want to write multiple pieces of data to a single matrix,
/// otherwise each subsequent piece of data will instead get sent to the next matrix.
void MAX7219lib::write(int regaddr, int data, hwlib::spi_bus::spi_transaction& transaction) {
    transaction.write(regaddr);
    transaction.write(data);
}

/// \brief
/// Write function with sending data
/// \details
/// This function is identical to the write() function except that it uses its own spi_transaction.
/// This is useful for when you want to setup the MAX7219 using register addresses.
void MAX7219lib::writeSet(int regaddr, int data) {
    auto transaction = spi_bus.transaction(cs);
    write(regaddr, data, transaction);
}

/// \brief
/// Send no_op command
/// \details
/// This function sends a no_op code to the MAX7219 a repeated amount of times.
/// This is used for copying data (like setup data) over all matrices,
/// as just sending a no_op code will shift the data over to the next matrix while keeping it on the current one.
void MAX7219lib::no_op(int repeat) {
    for (int i = 0; i < repeat; i++) {
        writeSet(0, 0);
    }
}

/// \brief
/// Set brightness of the matrix
/// \details
/// This function sets the brightness of the MAX7219 from 0 to 16.
/// Make sure to use the no_op function after or else this might not apply to all matrices.
void MAX7219lib::setBrightness(int data) {
    writeSet(0x0A, data);
}

/// \brief
/// Set pixel in the grid
/// \details
/// This function sets a pixel at (x, y) to be on.
/// A pixel can also be turned off if 0 is specified in value.
void MAX7219lib::setPixel(int x, int y, bool value) {
    if (x >= 0 && x <= 15 && y >= 0 && y <= 15) {
        grid[x][y] = value;
    }
}

/// \brief
/// Get pixel from grid
/// \details
/// This function returns whether the pixel at (x, y) is turned on or off.
bool MAX7219lib::getPixel(int x, int y) {
    return grid[x][y];
}

/// \brief
/// Set rectangle in the grid
/// \details
/// This function sets a rectangle of pixels on the grid, starting from (x, y) and ending on (end_x, end_y).
void MAX7219lib::setRectangle(int x, int end_x, int y, int end_y, bool value) {
    for (int i = x; i <= end_x; i++) {
        for (int j = y; j <= end_y; j++) {
            setPixel(i, j, value);
        }
    }
}

/// \brief
/// Draw a row of pixels to a matrix
/// \details
/// This function is used to draw a single row of pixels to the specified matrix in targetmatrix.
/// This is done by writing a number that equates in binary to which pixels should be turned on.
/// No_op codes are used to draw the row to the right matrix.
void MAX7219lib::drawRow(int y, int data, int targetMatrix) {
    auto transaction = spi_bus.transaction(cs);
    for (int matrixNumber = matrixamount; matrixNumber > 0; matrixNumber--) {
        if (matrixNumber == targetMatrix) {
            write(9 - y, data, transaction);
        }
        else {
            write(0, 0, transaction); // no-op
        }
    }
}

/// \brief
/// Reset grid array to be empty
/// \details
/// This function uses memset to fill the grid array with 0s, resetting it.
/// This does not update the screen.
void MAX7219lib::clean() {
    memset(grid, 0, sizeof(grid)); // reset array to 0s
}

/// \brief
/// Reset grid and matrices to be empty
/// \details
/// This function functions the same as clean(), but it also turns off all pixels on the matrices.
void MAX7219lib::clear() {
    for (int i = 1; i <= 8; i++) // set all rows to 0
        writeSet(i, 0);
    no_op(matrixamount - 1);
    clean();
}


/// \brief
/// Updates a single matrix
/// \details
/// This function is used by flush() to update a single matrix.
/// This is done by going through the specified part of the grid that equates to the target matrix
/// and drawing the rows one by one from the grid to the target matrix using drawRow().
void MAX7219lib::flushOne(int targetx, int targety, int targetMatrix) {
    int start_x = targetx * 8 - 1;
    int end_x = (targetx - 1) * 8;
    int start_y = (targety - 1) * 8;
    int end_y = targety * 8;

    for (int y = start_y; y < end_y; y++) {
        int row = y % 8 + 1;
        int data = 0;
        for (int x = start_x; x >= end_x; x--) {
            data |= ( 1 & grid[x][y] );
            if (x != end_x) {
                data <<= 1;
            }
        }
        drawRow(row, data, targetMatrix);
    }
}

/// \brief
/// Updates all matrices
/// \details
/// This function updates all matrices to turn on pixels according to the grid array.
/// Nothing will appear on the matrices if this is not called.
void MAX7219lib::flush() {
    int targetCounter = 0;
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++){
            targetCounter++;
            flushOne(x, y, targetCounter);
        }
    }
}



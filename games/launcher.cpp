#include "launcher.hpp"

launcher::launcher(MAX7219lib& max, hwlib::port_in_from_pins_t& Vcontrols, hwlib::port_in_from_pins_t& Hcontrols):
max(max)
{
    start();
    hwlib::wait_ms(1000);
    menu(Vcontrols, Hcontrols);
}

// 'this way up' arrow
void launcher::start() {
    max.clear();
    max.setRectangle(7,8,1,1);
    max.setRectangle(6,9,2,14);
    max.setRectangle(5,10,3,3);
    max.setRectangle(4,11,4,4);
    max.setRectangle(3,12,5,5);
    max.setRectangle(2,13,6,6);
    max.setRectangle(1,14,7,7);
    max.flush();
}

void launcher::menu(hwlib::port_in_from_pins_t& Vcontrols, hwlib::port_in_from_pins_t& Hcontrols) {
    bool selection = 0;
    int selection_arrow_x = 0;

    while (true) {
        max.clean();
        // pong icon
        max.setRectangle(3, 4, 5, 5);
        max.setRectangle(3, 4, 10, 10);
        max.setRectangle(1, 1, 7, 8);
        max.setRectangle(6, 6, 7, 8);
        max.setPixel(4, 8);

        // snake icon (not playable)
        max.setRectangle(9, 14, 5, 10);
        max.setRectangle(10, 13, 6, 9, 0);
        max.setRectangle(9, 11, 8, 10, 0);
        max.setRectangle(10, 12, 7, 7);
        max.setPixel(10, 10);
        // X over snake icon
        if (selection) {
            max.setPixel(8, 4);
            max.setPixel(10, 6);
            max.setPixel(12, 8);
            max.setPixel(13, 9);
            max.setPixel(15, 11);
            max.setPixel(15, 4);
            max.setPixel(13, 6);
            max.setPixel(11, 8);
            max.setPixel(10, 9);
            max.setPixel(9, 10);
            max.setPixel(8, 11);
        }


        if (!selection) selection_arrow_x = 2;
        else selection_arrow_x = 10;

        max.setPixel(selection_arrow_x, 13);
        max.setPixel(selection_arrow_x + 3, 13);
        max.setRectangle(selection_arrow_x + 1, selection_arrow_x + 2, 12, 12);

        max.flush();

        if (Hcontrols.read() == 1) selection = 0;
        else if (Hcontrols.read() == 2) selection = 1;

        else if (Vcontrols.read() == 1) {
            if (!selection) {
                pong(max, Vcontrols, Hcontrols);
            }
        }
    }

}
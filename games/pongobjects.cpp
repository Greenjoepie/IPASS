#include "pongobjects.hpp"

// pongobject
pongobject::pongobject(MAX7219lib& max, double x, double y):
max(max), x(x), y(y)
{}


// ball
ball::ball(MAX7219lib& max):
pongobject(max, 8, 8)
{}

void ball::update() {

    if (++updateCount >= updateSpeed) {
        updateCount = 0;
        if (x < 0 || x > 15 || y < 0 || y > 15) {
            reset();
        }
        else {
            x += dirx;
            y += diry;
        }
    }
}

void ball::draw() {
    max.setPixel(round(x), round(y));
}

void ball::collision(pongobject& other) {
    if (this != & other) {
        double paddlex = other.getx(), paddley = other.gety();
        double paddle_endx = other.getendx(), paddle_endy = other.getendy();

        if (x < 1 || x > 14) {
            if (y >= paddley && y <= paddle_endy) {
                diry = (round(y) - ((paddley + paddle_endy) / 2)) / 2;
                dirx = 1 - abs(diry);
                if (x > 14) dirx = -dirx;
                x += dirx;
                y += diry;
                speedUp();
                gameScore++;
            }
        }
        if (y < 1 || y > 14) {
            if (x >= paddlex && x <= paddle_endx) {
                dirx = (round(x) - ((paddlex + paddle_endx) / 2)) / 2;
                diry = 1 - abs(dirx);
                if (y > 14) diry = -diry;
                x += dirx;
                y += diry;
                speedUp();
                gameScore++;
            }
        }

    }
}

void ball::speedUp() {
    if (updateSpeed > 2) {
        if (++speedUpCount == speedUpBounces) {
            updateSpeed--;
            speedUpCount = 0;
        }
    }

}

void ball::reset() {
    end = true;
}


// paddle
paddle::paddle(MAX7219lib& max, double x, double y, bool vertical, hwlib::port_in_from_pins_t& controls):
pongobject(max, x, y),
vertical(vertical),
controls(controls)
{
    update();
}

void paddle::update() {
    double* axis = &x;
    double* end_axis = &end_x;
    if (vertical) {
        axis = &y;
        end_axis = &end_y;
    }
    controls.refresh();
    if (controls.read() == 0x01) {
        (*axis)--;
    }
    else if (controls.read() == 0x02) {
        (*axis)++;
    }
    if (*axis < 0) *axis = 0;
    else if (*axis > 12) *axis = 12;
    *end_axis = *axis+3;
}

void paddle::draw() {
    max.setRectangle(int(x), int(end_x), int(y), int(end_y));
}
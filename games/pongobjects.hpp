#include "../library/MAX7219lib.hpp"
#include "hwlib.hpp"
#include <cmath>

#ifndef PONGOBJECTS_HPP
#define PONGOBJECTS_HPP


class pongobject {
protected:
    MAX7219lib& max;
    double x,y;
    double end_x = x, end_y = y;
public:
    pongobject(MAX7219lib& max, double x, double y);
    virtual void update() {};
    virtual void draw() = 0;
    virtual void collision(pongobject& other) {};
    double getx() {return x;}
    double gety() {return y;}
    double getendx() {return end_x;}
    double getendy() {return end_y;}
};


class ball : public pongobject {
private:
    double dirx = 1, diry = 0;
    int updateSpeed = 3;
    int updateCount = 0;
    int speedUpBounces = 50;
    int speedUpCount = 0;
public:
    bool end = false;
    int gameScore = 0;
    ball(MAX7219lib& max);
    void update() override;
    void draw() override;
    void collision(pongobject& other) override;
    void speedUp();
    void reset();
};


class paddle : public pongobject {
    bool vertical; // 0 for horizontal, 1 for vertical
    hwlib::port_in_from_pins_t& controls;
public:
    paddle(MAX7219lib& max, double x, double y, bool vertical, hwlib::port_in_from_pins_t& controls);
    void update() override;
    void draw() override;

};


#endif //PONGOBJECTS_HPP

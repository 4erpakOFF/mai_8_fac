#ifndef HEXAGON_H
#define HEXAGON_H

#include <iostream>
#include <cstdlib>
#include "figure.h"
#include "point.h"

#define NUM_OF_POINTS 6

class Hexagon : public Figure {
private:
    //const int NUM_OF_POINTS = 6;
    point set[NUM_OF_POINTS];

public:
    Hexagon();
    Hexagon(std::istream &);
    Hexagon(point*);
    Hexagon(const Hexagon &);

    double square() override;
    void print() override;

    virtual ~Hexagon() {};
};

#endif // HEXAGON_H

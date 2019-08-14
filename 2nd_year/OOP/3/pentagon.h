#ifndef PENTAGON_H
#define PENTAGON_H

#include <cstdlib>
#include <iostream>
#include "figure.h"
#include "point.h"

#define NUM_OF_POINTS 5

class Pentagon : public Figure {
private:
    point set[NUM_OF_POINTS];

public:
    Pentagon();
    Pentagon(std::istream &is);
    Pentagon(point* );
    Pentagon(const Pentagon &);

    double square() override;
    void print() override;

    virtual ~Pentagon() {};
};

#endif // PENTAGON_H

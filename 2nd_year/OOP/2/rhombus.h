#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <cstdlib>
#include <iostream>
//#include "figure.h"


class Rhombus {
private:
    size_t side;
    size_t h;

    bool DoesExist(size_t, size_t);

public:
    Rhombus();
    Rhombus(std::istream &);
    Rhombus(size_t side, size_t h);
    Rhombus(const Rhombus &);

    double Square();

    Rhombus& operator= (const Rhombus &);

    friend std::ostream & operator<< (std::ostream &, const Rhombus &);
    friend std::istream & operator>> (std::istream &, Rhombus &);
    friend bool operator== (const Rhombus &, const Rhombus &);

    ~Rhombus() {};
};

#endif // RHOMBUS_H

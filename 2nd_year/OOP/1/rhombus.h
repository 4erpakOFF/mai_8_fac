#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <cstdlib>
#include <iostream>
#include "figure.h"


class Rhombus : public Figure  {
private:
    size_t side;
    size_t h;

public:
    Rhombus();
    Rhombus(std::istream &);
    Rhombus(size_t, size_t);
    Rhombus(const Rhombus &);

    double Square() override;
    void Print() override;

    virtual ~Rhombus() {};
};

#endif // RHOMBUS_H

#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <cstdlib>
#include <iostream>
#include "figure.h"


class Rhombus : public Figure  {
private:
    size_t side;
    size_t h;
    bool DoesExist(size_t, size_t);

public:
    Rhombus();
    Rhombus(std::istream &);
    Rhombus(size_t, size_t);
    Rhombus(const Rhombus &);

    bool set(size_t, size_t);
    double square() override;
    void print() override;

    virtual ~Rhombus() {};
};

#endif // RHOMBUS_H

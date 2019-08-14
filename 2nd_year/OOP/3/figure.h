#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>

class Figure {
public:
    virtual double square() = 0;
    virtual void print() = 0;

    friend std::ostream & operator<< (std::ostream &os, Figure &fig) {
        fig.print();
        return os;
    }

    virtual ~Figure() {};
};

#endif // FIGURE_H

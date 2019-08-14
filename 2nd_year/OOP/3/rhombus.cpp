#include "rhombus.h"
#include <cmath>

/*
void DoesExist(size_t &side, size_t &h) {
    if (h >= side) {
        std::cout << "Такой ромб не может быть создан" << std::endl;
        side = 0;
        h = 0;
    }
}*/

bool Rhombus::DoesExist(size_t _side, size_t _h) {
    if (_h > _side) {
        std::cout << "Ромб с данными (" << _side << " " << _h << ") не может существовать" << std::endl;
        this->side = 0;
        this->h= 0;
        return false;
    }
    return true;
}

Rhombus::Rhombus() : Rhombus(0,0) {}

Rhombus::Rhombus(size_t a, size_t b) : side(a), h(b) {
    DoesExist(a, b);
}

Rhombus::Rhombus(std::istream &is) {
    std::cout << "Введите сторону и высоту ромба: ";
    is >> side >> h;
    DoesExist(side, h);
}

Rhombus::Rhombus(const Rhombus &orig) {
    h = orig.h;
    side = orig.side;
    DoesExist(side, h);
}

bool Rhombus::set(size_t newSide, size_t newH) {
    this->side = newSide;
    this->h = newH;
    return DoesExist(newSide, newH);
}

void Rhombus::print() {
    std::cout << "Сторона ромба == " << side <<
                 ",  Высота ромба == " << h << ";" << std::endl;
}

double Rhombus::square() {
    return side*h;
}

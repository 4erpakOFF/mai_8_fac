#include <cmath>
#include "rhombus.h"

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
    DoesExist(side, h);
}

Rhombus::Rhombus(std::istream &is) {
    std::cout << "Введите сторону и высоту ромба: ";
    is >> side >> h;
    DoesExist(side, h); // сам поправит значения
}

Rhombus::Rhombus(const Rhombus &orig) {
    h = orig.h;
    side = orig.side;
    DoesExist(side, h);
}

double Rhombus::Square() {
    return side*h;
}

// ------Перегружаем операторы------------

Rhombus &Rhombus::operator =(const Rhombus &rhmb) {
    if (this != &rhmb) {
        this->side = rhmb.side;
        this->h = rhmb.h;
    }
    return *this;
}

std::ostream & operator<< (std::ostream &os, const Rhombus &rhmb) {
    os << "РОМБ:  " << "Сторона == "
       << rhmb.side << ",  Высота == " << rhmb.h << ";" << std::endl;

    return os;
}

std::istream & operator>> (std::istream &is, Rhombus &rhmb) {
    //std::cout << "Введите сторону и высоту ромба:  " << std::endl;
    is >> rhmb.side >> rhmb.h;

    return is;
}

bool operator== (const Rhombus &rhmb1, const Rhombus &rhmb2) {
    return (rhmb1.side == rhmb2.side) && (rhmb1.h == rhmb2.h);
}

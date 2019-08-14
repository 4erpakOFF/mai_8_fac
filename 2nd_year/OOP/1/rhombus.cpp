#include "rhombus.h"
#include <cmath>


void DoesExist(size_t &side, size_t &h) {
    if (h >= side) {
        std::cout << "Такой ромб не может быть создан" << std::endl;
        side = 0;
        h = 0;
    }
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

void Rhombus::Print() {
    std::cout << "Сторона ромба == " << side <<
                 ",  Высота ромба == " << h << ";" << std::endl;
}

double Rhombus::Square() {
    return side*h;
}

#include "hexagon.h"

Hexagon::Hexagon() {
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        set[i].x = 0;
        set[i].y = 0;
    }
}

Hexagon::Hexagon(std::istream &is) {
    std::cout << "Введите координаты вершин " << NUM_OF_POINTS << "-угольника:" << std::endl;
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        is >> set[i].x >> set[i].y;
    }
}

Hexagon::Hexagon(point *data) {
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        set[i] = data[i];
    }
}

Hexagon::Hexagon(const Hexagon &orig) {
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        set[i] = orig.set[i];
    }
}

double Hexagon::Square() {
    double sum = 0;
    for (int i = 0; i < NUM_OF_POINTS - 1; ++i) {
        sum += set[i].x * set[i+1].y - set[i+1].x * set[i].y;
    }
    sum += set[NUM_OF_POINTS - 1].x * set[0].y - set[0].x * set[NUM_OF_POINTS - 1].y;
    sum /= 2;

    return sum >= 0 ? sum : -sum;
}

void Hexagon::Print() {
    std::cout << "Координаты вершин " << NUM_OF_POINTS << "-угольника:" << std::endl;
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        std::cout << "x" << i+1 << " == " << set[i].x << ", "
                  << "y" << i+1 << " == " << set[i].y << ";" << std::endl;
    }
}

#include "pentagon.h"

Pentagon::Pentagon() {
    for (int i = 0; i < NUM_OF_POINTS; ++i){
        set[i].x = 0.0;
        set[i].y = 0.0;
    }
}

Pentagon::Pentagon(std::istream &is) {
    std::cout << "Введите координаты вершин " << NUM_OF_POINTS << "-угольника:" << std::endl;
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        is >> set[i].x >> set[i].y;
    }
}

Pentagon::Pentagon(point *data) {
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        set[i] = data[i];
    }
}

Pentagon::Pentagon(const Pentagon &orig) {
    for (int i = 0; i < NUM_OF_POINTS; ++i) {
        set[i] = orig.set[i];
    }
}

void Pentagon::Print() {
    std::cout << "Координаты вершин " << NUM_OF_POINTS << "-угольника" << std::endl;
    for (int i = 0; i < NUM_OF_POINTS; ++i){
        std::cout << "x" << i+1 << " == " << set[i].x << ", "
                  << "y" << i+1 << " == " << set[i].y << ";" << std::endl;
    }
}

double Pentagon::Square() {
    double sum_S = 0;
    for (int i = 0; i < NUM_OF_POINTS - 1; ++i) {
        sum_S += set[i].x * set[i+1].y - set[i+1].x * set[i].y;
    }
    sum_S += set[NUM_OF_POINTS-1].x * set[0].y - set[0].x * set[NUM_OF_POINTS-1].y;
    sum_S /= 2;

    return sum_S >= 0 ? sum_S : -sum_S;
}

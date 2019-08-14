#include <iostream>
#include "hexagon.h"
#include "pentagon.h"
#include "rhombus.h"
#include "tvector.h"

int main() {
    TVector vec;
    const size_t rN = 4;

    // Rhombus:
    for (size_t i = 0, side = 2, h = 0; i<rN; ++i, side+=1, h+=1) {
        std::shared_ptr<Figure> fig(new Rhombus(side, h));
        vec.add( fig, i );
    }

    // Hexagon:
    const size_t hexN = 2;
    for (size_t i = 0; i < hexN; ++i) {
        point hexData[6];
        for (size_t j = 0; j < 6; ++j) {
            hexData[j].x = j;
            hexData[j].y = j+1;
        }
        std::shared_ptr<Figure> fig(new Hexagon(hexData));
        vec.add( fig, i );
    }

    // Pentagon:
    const size_t pentN = 2;
    for (size_t i = 0; i < pentN; ++i) {
        point hexData[5];
        for (size_t j = 0; j < 5; ++j) {
            hexData[j].x = j;
            hexData[j].y = j+1;
        }
        std::shared_ptr<Figure> fig(new Pentagon(hexData));
        vec.add( fig );
    }

    std::cout << vec << std::endl;

    vec.del(1);
    vec.del(6);
    std::cout << std::endl << std::endl << std::endl << vec << std::endl;

    return 0;
}

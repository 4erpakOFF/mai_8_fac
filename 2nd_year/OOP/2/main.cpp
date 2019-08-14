#include <iostream>
#include <cstdlib>
#include "rhombus.h"
#include "tvector.h"


int main() {
    Rhombus rhmb(666, 66);
    TVector vec(std::cin);

    vec.Add(&rhmb, 1);
    vec.Delete(0);
    vec.Add(&rhmb, 100);

    std::cout << std::endl << vec;
    std::cout << std::endl;

    TVector vec2(&rhmb);
    std::cout << vec2;
    std::cout << std::endl;
    return 0;
}

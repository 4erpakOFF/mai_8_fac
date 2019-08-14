/*
  Щербаков А.А
  Вариант - 5 : Ромб, 5- и 6-угольники.
*/

#include <iostream>
#include "hexagon.h"
#include "pentagon.h"
#include "rhombus.h"

int main() {
    Rhombus rhmb(std::cin);
    rhmb.Print();
    std::cout << "S == " << rhmb.Square() << std::endl << std::endl;

    Hexagon hex(std::cin);
    hex.Print();
    std::cout << "S == " << hex.Square() << std::endl << std::endl;

    Pentagon pent(std::cin);
    pent.Print();
    std::cout << "S == " << pent.Square() << std::endl << std::endl;

    return 0;
}

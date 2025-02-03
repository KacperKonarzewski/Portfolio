#include "Point.h"

int main( void ) {
	
	Point a(Fixed(0), Fixed(0));
    Point b(Fixed(5), Fixed(0));
    Point c(Fixed(2.5f), Fixed(5));
    Point inside(Fixed(2.5f), Fixed(2));
    Point outside(Fixed(5), Fixed(5));

    std::cout << "\nChecking if points are inside the triangle:\n";

    if (bsp(a, b, c, inside))
        std::cout << "Point inside is INSIDE the triangle.\n";
    else
        std::cout << "Point inside is OUTSIDE the triangle.\n";

    if (bsp(a, b, c, outside))
        std::cout << "Point outside is INSIDE the triangle.\n";
    else
        std::cout << "Point outside is OUTSIDE the triangle.\n";

    std::cout << "\nDestroying Points...\n";
	return 0;
}


#include <iostream>
#include "Geometry/Intersect.h"
#include "Geometry/Output.h"
#include "Geometry/Shape.h"
#include "Geometry/Shapes.h"

int main()
{
    using namespace OpenCadmus::Geometry;

    Shape p1 = Point(1, 1);
    Shape p2 = Point(1, 1);
    Shape p3 = Point(2, 2);
    Shape l1 = Line{{0, 0}, {2, 2}};
    Shape l2 = Line{{0, 2}, {2, 0}};
    Shape c1 = Circle{{1, 1}, 1};

    std::cout << "Intersect(p1, p2): ";
    for (const auto &s : Intersect(p1, p2))
        std::cout << s << " ";
    std::cout << "\n";

    std::cout << "Intersect(p1, p3): ";
    for (const auto &s : Intersect(p1, p3))
        std::cout << s << " ";
    std::cout << "\n";

    std::cout << "Intersect(l1, l2): ";
    for (const auto &s : Intersect(l1, l2))
        std::cout << s << " ";
    std::cout << "\n";

    std::cout << "Intersect(c1, l1): ";
    for (const auto &s : Intersect(c1, l1))
        std::cout << s << " ";
    std::cout << "\n";

    std::cout << std::boolalpha << "p1 Intersects p2: " << p1.Intersects(p2) << "\n";

    std::cout << p3 << "\n";

    p3 = p3.Translate(1, 1);

    std::cout << "After translating p3 by (1, 1): " << p3 << "\n";

    return 0;
}

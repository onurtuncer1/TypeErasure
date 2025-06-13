#include "Geometry/D2/Point.h"

namespace Geometry::D2{

    Point::Point(Real x, Real y) : x(x), y(y) {}

    bool Point::operator==(const Point &other) const
    {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }

    void Point::Translate(Real dx, Real dy)
    {
        x += dx;
        y += dy;
    }

    std::ostream& operator<<(std::ostream& os, const Point& pt) {
        return os << "(" << pt.x << ", " << pt.y << ")";
    }
}
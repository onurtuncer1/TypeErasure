
#include <cmath>

#include "Geometry/Output.h"
#include "Geometry/Intersect.h"

namespace OpenCadmus::Geometry {

Shapes Intersect(const D2::Point &a, const D2::Point &b)
{
    return (a == b) ? Shapes{Shape(a)} : Shapes{};
}

Shapes Intersect(const Line &l1, const Line &l2)
{
    Real x1 = l1.start.x, y1 = l1.start.y;
    Real x2 = l1.end.x, y2 = l1.end.y;
    Real x3 = l2.start.x, y3 = l2.start.y;
    Real x4 = l2.end.x, y4 = l2.end.y;

    Real denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (std::abs(denom) < 1e-9)
        return {}; // parallel

    double px = ((x1 * y2 - y1 * x2) * (x3 - x4) -
                 (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
    double py = ((x1 * y2 - y1 * x2) * (y3 - y4) -
                 (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;

    if (px >= std::min(x1, x2) && px <= std::max(x1, x2) &&
        py >= std::min(y1, y2) && py <= std::max(y1, y2) &&
        px >= std::min(x3, x4) && px <= std::max(x3, x4) &&
        py >= std::min(y3, y4) && py <= std::max(y3, y4))
    {
        return {D2::Point{px, py}};
    }
    return {};
}

Shapes Intersect(const Circle &c, const Line &l)
{
    Real dx = l.end.x - l.start.x;
    Real dy = l.end.y - l.start.y;
    Real a = dx * dx + dy * dy;
    Real b = 2 * (dx * (l.start.x - c.center.x) + dy * (l.start.y - c.center.y));
    Real cc = (l.start.x - c.center.x) * (l.start.x - c.center.x) +
                (l.start.y - c.center.y) * (l.start.y - c.center.y) -
                c.radius * c.radius;

    double det = b * b - 4 * a * cc;
    if (a <= 1e-9 || det < 0)
        return {};

    det = std::sqrt(det);
    Real t1 = (-b + det) / (2 * a);
    Real t2 = (-b - det) / (2 * a);

    Shapes result;
    if (t1 >= 0 && t1 <= 1)
        result.emplace_back(D2::Point{l.start.x + t1 * dx, l.start.y + t1 * dy});
    if (t2 >= 0 && t2 <= 1 && std::abs(t1 - t2) > 1e-9)
        result.emplace_back(D2::Point{l.start.x + t2 * dx, l.start.y + t2 * dy});
    return result;
}

Shapes Intersect(const Line &l, const Circle &c)
{
    return Intersect(c, l);
}

Shapes Intersect(const Shape &a, const Shape &b)
{
    if (auto pa = a.as<D2::Point>())
    {
        if (auto pb = b.as<D2::Point>())
            return Intersect(*pa, *pb);
    }
    else if (auto la = a.as<Line>())
    {
        if (auto lb = b.as<Line>())
            return Intersect(*la, *lb);
        if (auto cb = b.as<Circle>())
            return Intersect(*la, *cb);
    }
    else if (auto ca = a.as<Circle>())
    {
        if (auto lb = b.as<Line>())
            return Intersect(*ca, *lb);
    }
    return {};
}

} // namespace OpenCadmus

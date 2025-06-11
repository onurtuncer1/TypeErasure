

#include <vector>
#include <cmath>
#include <typeinfo>

#include "Output.h"
#include "Shape.h"
#include "Line.h"

namespace OPENCADMUS
{

    

  

    // === External Intersection Functions ===
    std::vector<Shape> Intersect(const Point &a, const Point &b)
    {
        return (a == b) ? std::vector{Shape(a)} : std::vector<Shape>{};
    }

    std::vector<Shape> Intersect(const Line &l1, const Line &l2)
    {
        double x1 = l1.start.x, y1 = l1.start.y;
        double x2 = l1.end.x, y2 = l1.end.y;
        double x3 = l2.start.x, y3 = l2.start.y;
        double x4 = l2.end.x, y4 = l2.end.y;

        double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (std::abs(denom) < 1e-9)
            return {}; // parallel

        double px = ((x1 * y2 - y1 * x2) * (x3 - x4) -
                     (x1 - x2) * (x3 * y4 - y3 * x4)) /
                    denom;
        double py = ((x1 * y2 - y1 * x2) * (y3 - y4) -
                     (y1 - y2) * (x3 * y4 - y3 * x4)) /
                    denom;

        if (px >= std::min(x1, x2) && px <= std::max(x1, x2) &&
            py >= std::min(y1, y2) && py <= std::max(y1, y2) &&
            px >= std::min(x3, x4) && px <= std::max(x3, x4) &&
            py >= std::min(y3, y4) && py <= std::max(y3, y4))
        {
            return {Point{px, py}};
        }
        return {};
    }

    std::vector<Shape> Intersect(const Circle &c, const Line &l)
    {
        double dx = l.end.x - l.start.x;
        double dy = l.end.y - l.start.y;
        double a = dx * dx + dy * dy;
        double b = 2 * (dx * (l.start.x - c.center.x) + dy * (l.start.y - c.center.y));
        double cc = (l.start.x - c.center.x) * (l.start.x - c.center.x) +
                    (l.start.y - c.center.y) * (l.start.y - c.center.y) -
                    c.radius * c.radius;

        double det = b * b - 4 * a * cc;
        if (a <= 1e-9 || det < 0)
            return {};

        det = std::sqrt(det);
        double t1 = (-b + det) / (2 * a);
        double t2 = (-b - det) / (2 * a);

        std::vector<Shape> result;
        if (t1 >= 0 && t1 <= 1)
            result.emplace_back(Point{l.start.x + t1 * dx, l.start.y + t1 * dy});
        if (t2 >= 0 && t2 <= 1 && std::abs(t1 - t2) > 1e-9)
            result.emplace_back(Point{l.start.x + t2 * dx, l.start.y + t2 * dy});
        return result;
    }

    std::vector<Shape> Intersect(const Line &l, const Circle &c)
    {
        return Intersect(c, l);
    }

    // === Public Intersect Dispatcher ===
    std::vector<Shape> Intersect(const Shape &a, const Shape &b)
    {
        if (auto pa = a.as<Point>())
        {
            if (auto pb = b.as<Point>())
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

} // namespace 


int main()
{
    using namespace OPENCADMUS;

    Shape p1 = Point{1, 1};
    Shape p2 = Point{1, 1};
    Shape p3 = Point{2, 2};
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

    return 0;
}

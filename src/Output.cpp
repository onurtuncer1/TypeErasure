
#include <iostream>

#include "Output.h"

namespace OPENCADMUS{

// === Output Operators ===
inline std::ostream &operator<<(std::ostream &os, const Point &p)
{
    return os << "Point(" << p.x << ", " << p.y << ")";
}

inline std::ostream &operator<<(std::ostream &os, const Line &l)
{
    return os << "Line(" << l.start << " → " << l.end << ")";
}

inline std::ostream &operator<<(std::ostream &os, const Circle &c)
{
    return os << "Circle(center=" << c.center << ", r=" << c.radius << ")";
}

}
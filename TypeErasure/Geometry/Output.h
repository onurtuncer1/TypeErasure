
#pragma once

#include <ostream>
#include "Geometry/D2/Point.h"
#include "Geometry/Line.h"
#include "Geometry/Circle.h"

namespace OpenCadmus::Geometry {

    // inline std::ostream& operator<<(std::ostream& os, const D2::Point& p) {
    //     return os << "(" << p.x << ", " << p.y << ")";
    // }

    inline std::ostream& operator<<(std::ostream& os, const Line& l) {
        return os << "Line[" << l.start << " -> " << l.end << "]";
    }

    inline std::ostream& operator<<(std::ostream& os, const Circle& c) {
        return os << "Circle[center: " << c.center << ", radius: " << c.radius << "]";
    }
}

#pragma once

#include <cmath>

#include "Core/Base.h"

namespace OpenCadmus::Geometry::D2 {

    // === Public Shape Types ===
    struct Point
    {
        Real x; 
        Real y;

        bool operator==(const Point &other) const
        {
            return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
        }

        void Translate(Real dx, Real dy)
        {
            x += dx;
            y += dy;
        }

        friend std::ostream& operator<<(std::ostream& os, const Point& pt) {
            return os << "(" << pt.x << ", " << pt.y << ")";
        }


    };

}
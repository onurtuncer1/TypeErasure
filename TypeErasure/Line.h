#pragma once

#include <cmath>

#include "Base.h"

namespace OPENCADMUS{

    // === Public Shape Types ===
    struct Point
    {
        Real x, y;

        bool operator==(const Point &other) const
        {
            return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
        }
    };

    struct Line
    {
        Point start, end;
    };

    struct Circle
    {
        Point center;
        Real radius;
    };
}
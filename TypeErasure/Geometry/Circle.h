#pragma once

#include <cmath>

#include "Core/Base.h"
#include "Geometry/D2/Point.h"

namespace OpenCadmus::Geometry{

    struct Circle
    {
        D2::Point center;
        Real radius;

        bool operator==(const Circle &other) const
        {
            return center == other.center && std::abs(radius - other.radius) < 1e-9;
        }

        void Translate(double dx, double dy)
        {
            center.Translate(dx, dy);
        }
    };
}
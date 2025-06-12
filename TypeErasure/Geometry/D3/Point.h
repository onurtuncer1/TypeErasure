#pragma once

#include <cmath>

#include "Core/Base.h"

namespace OpenCadmus::Geometry::D3 {

    // === Public Shape Types ===
    struct Point
    {
        Real x; 
        Real y;
        Real z;

        bool operator==(const Point &other) const
        {
            return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9 
                   && std::abs(z - other.z) < 1e-9;
        }

        void Translate(Real dx, Real dy, Real dz)
        {
            x += dx;
            y += dy;
            z += dz;
        }

    };

}
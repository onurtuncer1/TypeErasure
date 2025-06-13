#pragma once

#include <ostream>
#include <cmath>

#include "Core/Base.h"

namespace OpenCadmus::Geometry::D2 {

    struct Point
    {
        Real x; 
        Real y;

        bool operator==(const Point &other) const;
        void Translate(Real dx, Real dy);
        friend std::ostream& operator<<(std::ostream& os, const Point& pt);

    };

    static Point Origin()
    {
        return Point{0.0, 0.0};
    }

}
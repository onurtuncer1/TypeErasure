#pragma once

#include <cmath>

#include "Core/Base.h"
#include "Point.h"

namespace OpenCadmus::Geometry::D2 {

    struct Line
    {
        Point start;
        Point end;

        bool operator==(const Line &other) const
        {
            return (start == other.start && end == other.end) ||
                   (start == other.end && end == other.start);
        }

        void Translate(Real dx, Real dy)
        {
            start.Translate(dx, dy);
            end.Translate(dx, dy);
        }

        bool IsClosed() const
        {
            return false;
        }
    };

}
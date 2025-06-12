#pragma once

#include <vector>
#include "Shape.h"

namespace OpenCadmus::Geometry::D2 {
    class Shape { /* wraps only 2D types */ };
    std::vector<Shape> Intersect(const Shape&, const Shape&);
}

namespace OpenCadmus::Geometry::D3 {
    class Shape { /* wraps only 3D types */ };
    std::vector<Shape> Intersect(const Shape&, const Shape&);
}



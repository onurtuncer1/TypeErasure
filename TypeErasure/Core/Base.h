#pragma once

#include <set>

using Real = double;

namespace OpenCadmus{

namespace Geometry{

    class Shape;
}

using Shapes = std::set<Geometry::Shape>;

}
#pragma once

#include "Core/Base.h"
#include "Geometry/D2/Point.h"
#include "Geometry/D3/Point.h"

namespace OpenCadmus::Geometry {
    
    template<typename... Args>
    requires (std::conjunction_v<std::is_convertible<Args, Real>...>)
    auto Point(Args&&... args) {
        static_assert(sizeof...(Args) == 2 || sizeof...(Args) == 3,
                      "Only 2D or 3D points are supported");
    
        if constexpr (sizeof...(Args) == 2) {
            return D2::Point(static_cast<Real>(args)...);
        } else {
            return D3::Point(static_cast<Real>(args)...);
        }
    }
}


#pragma once

#include <iostream>

#include "Line.h"

namespace OPENCADMUS
{

    // === Output Operators ===
    inline std::ostream &operator<<(std::ostream &os, const Point &p);
    inline std::ostream &operator<<(std::ostream &os, const Line &l);
    inline std::ostream &operator<<(std::ostream &os, const Circle &c);
   
}
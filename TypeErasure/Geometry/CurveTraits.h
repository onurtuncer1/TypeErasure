#pragma once

#include <cstddef>

template <typename T>
struct CurveTraits; // Must specialize for every curve type

template <>
struct CurveTraits<struct Line3D> {
    static constexpr size_t Dim = 3;
};

template <>
struct CurveTraits<struct Arc2D> {
    static constexpr size_t Dim = 2;
};

#pragma once

#include <concepts>
#include "Core/Base.h"
#include "CurveTraits.h"

template<typename T>
concept Curve = requires(const T& curve, Real t) {
    typename CurveTraits<T>; // Trait must exist
    requires (CurveTraits<T>::Dim == 2 || CurveTraits<T>::Dim == 3);

    // Geometry
    { curve.Evaluate(t) }     -> std::same_as<std::array<Real, CurveTraits<T>::Dim>>;
    { curve.Tangent(t) }      -> std::same_as<std::array<Real, CurveTraits<T>::Dim>>;
    { curve.Length() }        -> std::same_as<Real>;

    // Derivatives
    { curve.Derivative(t, 1) } -> std::same_as<std::array<Real, CurveTraits<T>::Dim>>;
    { curve.Derivative(t, 2) } -> std::same_as<std::array<Real, CurveTraits<T>::Dim>>;

    // Curvature (scalar)
    { curve.Curvature(t) }     -> std::same_as<double>;

    // Self-intersection check
    { curve.IsSelfIntersecting() } -> std::same_as<bool>;

     // Self-intersection check
    { curve.IsClosed() } -> std::same_as<bool>;
};

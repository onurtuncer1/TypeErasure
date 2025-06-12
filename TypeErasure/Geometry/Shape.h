#pragma once

#include "Core/Base.h"
#include <memory>
#include <vector>

#include "Geometry/Intersect.h"

namespace OpenCadmus::Geometry{

    namespace inner
    {

        struct Concept
        {
            virtual ~Concept() = default;
            virtual std::unique_ptr<Concept> clone() const = 0;
            virtual const std::type_info &type() const = 0;
            virtual void print(std::ostream &) const = 0;
            virtual const void *get_ptr() const = 0;

            virtual std::unique_ptr<Concept> translate(double dx, double dy) const = 0;
            virtual std::unique_ptr<Concept> translate(double dx, double dy, double dz) const = 0;
        };

        template <typename T>
        struct Model : Concept
        {
            T value;
            explicit Model(const T &val) : value(val) {}
            std::unique_ptr<Concept> clone() const override { return std::make_unique<Model<T>>(value); }
            const std::type_info &type() const override { return typeid(T); }
            void print(std::ostream &os) const override { os << value; }
            const void *get_ptr() const override { return &value; }

             // 2D Translate
    std::unique_ptr<Concept> translate(double dx, double dy) const override
    {
        if constexpr (requires(T v) { v.Translate(dx, dy); }) {
            T copy = value;
            copy.Translate(dx, dy);
            return std::make_unique<Model<T>>(copy);
        } else {
            throw std::runtime_error("2D Translate not supported for this shape");
        }
    }

    // 3D Translate
    std::unique_ptr<Concept> translate(double dx, double dy, double dz) const override
    {
        if constexpr (requires(T v) { v.Translate(dx, dy, dz); }) {
            T copy = value;
            copy.Translate(dx, dy, dz);
            return std::make_unique<Model<T>>(copy);
        } else {
            throw std::runtime_error("3D Translate not supported for this shape");
        }
    }
        };

    } 

    class Shape;

    using Shapes = std::vector<Shape>;

    Shapes Intersect(const Shape& a, const Shape& b);

    class Shape
    {
        std::unique_ptr<inner::Concept> self;

    public:
        template <typename T>
        Shape(const T &val) : self(std::make_unique<inner::Model<T>>(val)) {}

        explicit Shape(std::unique_ptr<inner::Concept> impl) : self(std::move(impl)) {}

        Shape(const Shape &other) : self(other.self->clone()) {}
        Shape &operator=(const Shape &other)
        {
            self = other.self->clone();
            return *this;
        }

       Shape Translate(double dx, double dy) const {
    return Shape(self->translate(dx, dy));
}

Shape Translate(double dx, double dy, double dz) const {
    return Shape(self->translate(dx, dy, dz));
}


        bool Intersects(const Shape &other) const
        {
            return Intersect(*this, other).size() > 0;
        }

        template <typename T>
        const T *as() const
        {
            return (self->type() == typeid(T)) ? static_cast<const T *>(self->get_ptr()) : nullptr;
        }

        const std::type_info &type() const { return self->type(); }

        friend std::ostream &operator<<(std::ostream &os, const Shape &shape)
        {
            shape.self->print(os);
            return os;
        }

    private:
        const void *get_ptr() const { return self->get_ptr(); }
    };
}
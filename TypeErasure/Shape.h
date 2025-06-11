#pragma once

#include <memory>

namespace OPENCADMUS{

    // === Internal Type-Erasure Implementation ===
    namespace impl
    {

        struct Concept
        {
            virtual ~Concept() = default;
            virtual std::unique_ptr<Concept> clone() const = 0;
            virtual const std::type_info &type() const = 0;
            virtual void print(std::ostream &) const = 0;
            virtual const void *get_ptr() const = 0;
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
        };

    } // namespace impl

    // === Public Shape Wrapper ===
    class Shape
    {
        std::unique_ptr<impl::Concept> self;

    public:
        template <typename T>
        Shape(const T &val) : self(std::make_unique<impl::Model<T>>(val)) {}

        Shape(const Shape &other) : self(other.self->clone()) {}
        Shape &operator=(const Shape &other)
        {
            self = other.self->clone();
            return *this;
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
#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <algebra/core/concepts.hpp>
#include <algebra/core/operators.hpp>
#include <algebra/core/structures.hpp>

namespace algebra {

template<RingElement T>
class UnitGroup;

template<FieldElement T>
class NonzeroGroup;

template<RingElement T>
class Unit : public MultiplicativeOperators<Unit<T>>,
             public DivisionOperators<Unit<T>> {
    T value_;
    T inverse_;

public:
    using parent_type = UnitGroup<T>;
    using algebra = std::conditional_t<CommutativeRingElement<T>,
        MultiplicativeAbelianGroupDescriptor, MultiplicativeGroupDescriptor>;

    Unit() : value_(T::one()), inverse_(T::one()) {}

    Unit(T value, T inverse) : value_(std::move(value)), inverse_(std::move(inverse)) {
        if (!value_.multiply(inverse_).is_one() || !inverse_.multiply(value_).is_one()) {
            throw std::domain_error("The supplied value and inverse do not form a unit");
        }
    }

    static Unit one() {
        return Unit{};
    }

    Unit multiply(const Unit& other) const {
        return Unit(value_.multiply(other.value_), other.inverse_.multiply(inverse_));
    }

    Unit reciprocal() const {
        return Unit(inverse_, value_);
    }

    bool is_one() const {
        return value_.is_one();
    }

    const T& value() const {
        return value_;
    }

    const parent_type& parent() const {
        static const parent_type instance;
        return instance;
    }

    bool operator==(const Unit& other) const {
        return value_ == other.value_;
    }
};

template<FieldElement T>
class Nonzero : public MultiplicativeOperators<Nonzero<T>>,
                public DivisionOperators<Nonzero<T>> {
    T value_;

public:
    using parent_type = NonzeroGroup<T>;
    using algebra = MultiplicativeAbelianGroupDescriptor;

    Nonzero() : value_(T::one()) {}

    explicit Nonzero(T value) : value_(std::move(value)) {
        if (value_.is_zero()) {
            throw std::domain_error("Zero is not in the multiplicative group");
        }
    }

    static Nonzero one() {
        return Nonzero{};
    }

    Nonzero multiply(const Nonzero& other) const {
        return Nonzero(value_.multiply(other.value_));
    }

    Nonzero reciprocal() const {
        return Nonzero(value_.reciprocal());
    }

    bool is_one() const {
        return value_.is_one();
    }

    const T& value() const {
        return value_;
    }

    const parent_type& parent() const {
        static const parent_type instance;
        return instance;
    }

    bool operator==(const Nonzero& other) const {
        return value_ == other.value_;
    }
};

template<RingElement T>
class UnitGroup : public std::conditional_t<CommutativeRingElement<T>,
    MultiplicativeAbelianGroupStructure<Unit<T>>, MultiplicativeGroupStructure<Unit<T>>> {
public:
    using Element = Unit<T>;

    static Element element(T value, T inverse) {
        return Element(std::move(value), std::move(inverse));
    }
};

template<FieldElement T>
class NonzeroGroup : public MultiplicativeAbelianGroupStructure<Nonzero<T>> {
public:
    using Element = Nonzero<T>;

    static Element element(T value) {
        return Element(std::move(value));
    }
};

}

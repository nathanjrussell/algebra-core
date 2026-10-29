#pragma once

#include <concepts>
#include <algebra/core/operations.hpp>

namespace algebra {

template<class T>
concept AlgebraElement = std::copyable<T> && requires(const T& a, const T& b) {
    typename T::parent_type;
    typename T::algebra;
    { a == b } -> std::convertible_to<bool>;
};

template<class T, class Op = GenericOperation>
concept MagmaElement = AlgebraElement<T> &&
    std::derived_from<typename Op::template category<typename T::algebra>, MagmaCategory> &&
    requires(const T& a, const T& b) {
        { operation<T, Op>::apply(a, b) } -> std::same_as<T>;
    };

template<class T, class Op = GenericOperation>
concept SemigroupElement = MagmaElement<T, Op> &&
    std::derived_from<typename Op::template category<typename T::algebra>, SemigroupCategory>;

template<class T, class Op = GenericOperation>
concept MonoidElement = SemigroupElement<T, Op> &&
    std::derived_from<typename Op::template category<typename T::algebra>, MonoidCategory> &&
    requires(const T& a) {
        { operation<T, Op>::identity() } -> std::same_as<T>;
        { operation<T, Op>::is_identity(a) } -> std::same_as<bool>;
    };

template<class T, class Op = GenericOperation>
concept GroupElement = MonoidElement<T, Op> &&
    std::derived_from<typename Op::template category<typename T::algebra>, GroupCategory> &&
    requires(const T& a) {
        { operation<T, Op>::inverse(a) } -> std::same_as<T>;
    };

template<class T, class Op = GenericOperation>
concept AbelianGroupElement = GroupElement<T, Op> &&
    Op::template category<typename T::algebra>::commutative;

template<class T, class Op = GenericOperation>
concept CyclicGroupElement = AbelianGroupElement<T, Op> &&
    std::derived_from<typename Op::template category<typename T::algebra>, CyclicGroupCategory> &&
    requires { { T::generator() } -> std::same_as<T>; };

template<class T>
concept RngElement = AlgebraElement<T> && T::algebra::rng &&
    AbelianGroupElement<T, Addition> && SemigroupElement<T, Multiplication>;

template<class T>
concept RingElement = RngElement<T> && T::algebra::ring &&
    MonoidElement<T, Multiplication>;

template<class T>
concept CommutativeRingElement = RingElement<T> &&
    T::algebra::multiplicative_category::commutative;

template<class T>
concept IntegralDomainElement = CommutativeRingElement<T> && T::algebra::integral_domain;

template<class T>
concept DivisionRingElement = RingElement<T> && T::algebra::division_ring &&
    requires(const T& a) { { a.reciprocal() } -> std::same_as<T>; };

template<class T>
concept FieldElement = IntegralDomainElement<T> && DivisionRingElement<T> && T::algebra::field;

}

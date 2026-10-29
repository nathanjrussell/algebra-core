#pragma once

#include <algebra/core/descriptors.hpp>

namespace algebra {

template<class T, class Op>
struct operation;

template<class T>
struct operation<T, Addition> {
    static T apply(const T& a, const T& b)
        requires requires { a.add(b); }
    {
        return a.add(b);
    }

    static T identity()
        requires requires { T::zero(); }
    {
        return T::zero();
    }

    static bool is_identity(const T& a)
        requires requires { a.is_zero(); }
    {
        return a.is_zero();
    }

    static T inverse(const T& a)
        requires requires { a.negate(); }
    {
        return a.negate();
    }
};

template<class T>
struct operation<T, Multiplication> {
    static T apply(const T& a, const T& b)
        requires requires { a.multiply(b); }
    {
        return a.multiply(b);
    }

    static T identity()
        requires requires { T::one(); }
    {
        return T::one();
    }

    static bool is_identity(const T& a)
        requires requires { a.is_one(); }
    {
        return a.is_one();
    }

    static T inverse(const T& a)
        requires requires { a.reciprocal(); }
    {
        return a.reciprocal();
    }
};

template<class T>
struct operation<T, GenericOperation> {
    static T apply(const T& a, const T& b)
        requires requires { a.combine(b); }
    {
        return a.combine(b);
    }

    static T identity()
        requires requires { T::identity(); }
    {
        return T::identity();
    }

    static bool is_identity(const T& a)
        requires requires { a.is_identity(); }
    {
        return a.is_identity();
    }

    static T inverse(const T& a)
        requires requires { a.inverse(); }
    {
        return a.inverse();
    }
};

}

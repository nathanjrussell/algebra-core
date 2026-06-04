#pragma once

namespace njr::algebra {

struct UnstructuredCategory {};
struct MagmaCategory {
    static constexpr bool commutative = false;
};
struct SemigroupCategory : MagmaCategory {};
struct MonoidCategory : SemigroupCategory {};
struct CommutativeMonoidCategory : MonoidCategory {
    static constexpr bool commutative = true;
};
struct GroupCategory : MonoidCategory {};
struct AbelianGroupCategory : GroupCategory {
    static constexpr bool commutative = true;
};
struct CyclicGroupCategory : AbelianGroupCategory {};

struct AlgebraDescriptor {
    using additive_category = UnstructuredCategory;
    using multiplicative_category = UnstructuredCategory;
    using generic_category = UnstructuredCategory;
    static constexpr bool rng = false;
    static constexpr bool ring = false;
    static constexpr bool integral_domain = false;
    static constexpr bool division_ring = false;
    static constexpr bool field = false;
};

struct AdditiveGroupDescriptor : AlgebraDescriptor {
    using additive_category = AbelianGroupCategory;
};

struct CyclicAdditiveGroupDescriptor : AdditiveGroupDescriptor {
    using additive_category = CyclicGroupCategory;
};

struct RngDescriptor : AdditiveGroupDescriptor {
    using multiplicative_category = SemigroupCategory;
    static constexpr bool rng = true;
};

struct RingDescriptor : RngDescriptor {
    using multiplicative_category = MonoidCategory;
    static constexpr bool ring = true;
};

struct CommutativeRingDescriptor : RingDescriptor {
    using multiplicative_category = CommutativeMonoidCategory;
};

struct IntegralDomainDescriptor : CommutativeRingDescriptor {
    static constexpr bool integral_domain = true;
};

struct DivisionRingDescriptor : RingDescriptor {
    static constexpr bool division_ring = true;
};

struct FieldDescriptor : IntegralDomainDescriptor {
    static constexpr bool division_ring = true;
    static constexpr bool field = true;
};

struct MultiplicativeGroupDescriptor : AlgebraDescriptor {
    using multiplicative_category = GroupCategory;
};

struct MultiplicativeAbelianGroupDescriptor : AlgebraDescriptor {
    using multiplicative_category = AbelianGroupCategory;
};

struct Addition {
    template<class Descriptor>
    using category = typename Descriptor::additive_category;
};

struct Multiplication {
    template<class Descriptor>
    using category = typename Descriptor::multiplicative_category;
};

struct GenericOperation {
    template<class Descriptor>
    using category = typename Descriptor::generic_category;
};

}

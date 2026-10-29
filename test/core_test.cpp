#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <gtest/gtest.h>
#include <algebra/core/core.hpp>

using namespace algebra;

struct BinaryField;

struct BinaryElement : AdditiveOperators<BinaryElement>,
                       MultiplicativeOperators<BinaryElement>,
                       DivisionOperators<BinaryElement> {
    using parent_type = BinaryField;
    using algebra = FieldDescriptor;
    bool value = false;

    BinaryElement() = default;
    explicit BinaryElement(bool input) : value(input) {}
    static BinaryElement zero() { return BinaryElement(false); }
    static BinaryElement one() { return BinaryElement(true); }
    BinaryElement add(const BinaryElement& other) const { return BinaryElement(value != other.value); }
    BinaryElement multiply(const BinaryElement& other) const { return BinaryElement(value && other.value); }
    BinaryElement negate() const { return *this; }
    BinaryElement reciprocal() const {
        if (!value) {
            throw std::domain_error("Zero has no reciprocal");
        }
        return *this;
    }
    bool is_zero() const { return !value; }
    bool is_one() const { return value; }
    bool operator==(const BinaryElement& other) const { return value == other.value; }
};

struct BinaryField : FieldStructure<BinaryElement> {};

struct SubtractionDescriptor : AlgebraDescriptor {
    using generic_category = MagmaCategory;
};

struct Subtraction {
    using parent_type = Subtraction;
    using algebra = SubtractionDescriptor;
    unsigned value;
    Subtraction combine(const Subtraction& other) const {
        return {(value + 3 - other.value) % 3};
    }
    bool operator==(const Subtraction&) const = default;
};

struct WordDescriptor : AlgebraDescriptor {
    using generic_category = MonoidCategory;
};

struct Word {
    using parent_type = Word;
    using algebra = WordDescriptor;
    std::string value;
    Word combine(const Word& other) const { return {value + other.value}; }
    static Word identity() { return {}; }
    bool is_identity() const { return value.empty(); }
    bool operator==(const Word&) const = default;
};

static_assert(MagmaElement<Subtraction>);
static_assert(!SemigroupElement<Subtraction>);
static_assert(MonoidElement<Word>);
static_assert(!GroupElement<Word>);
static_assert(FieldElement<BinaryElement>);
static_assert(AbelianGroupElement<BinaryElement, Addition>);
static_assert(!GroupElement<BinaryElement, Multiplication>);
static_assert(AbelianGroupElement<Nonzero<BinaryElement>, Multiplication>);
static_assert(!RingElement<int>);
static_assert(!FieldElement<double>);

TEST(Contracts, SeparatesClosureFromAssociativity) {
    EXPECT_FALSE((associative_law<Subtraction, GenericOperation>({0}, {0}, {1})));
}

TEST(Monoids, PreservesOrderAndEmptyIdentity) {
    EXPECT_EQ(repeat<GenericOperation>(Word{"ab"}, 3).value, "ababab");
    EXPECT_TRUE(repeat<GenericOperation>(Word{"ab"}, 0).is_identity());
    EXPECT_TRUE((identity_law<Word, GenericOperation>(Word{"ab"})));
}

TEST(Fields, ValidatesBothDistributiveLaws) {
    for (bool a : {false, true}) {
        for (bool b : {false, true}) {
            for (bool c : {false, true}) {
                EXPECT_TRUE(distributive_law(BinaryElement(a), BinaryElement(b), BinaryElement(c)));
            }
        }
    }
}

TEST(Interfaces, SharesTheCarrierAcrossOperations) {
    BinaryField field;
    const interfaces::Field<BinaryElement>& view = field;
    const auto one = BinaryElement::one();
    EXPECT_TRUE(view.contains(one));
    EXPECT_TRUE(view.add(one, one).is_zero());
    EXPECT_TRUE(view.multiply(one, one).is_one());
    EXPECT_TRUE(view.reciprocal(one).is_one());
    EXPECT_THROW(view.reciprocal(BinaryElement::zero()), std::domain_error);
}

TEST(Units, RequiresVerifiedInverses) {
    using E = BinaryElement;
    EXPECT_TRUE(Unit<E>(E::one(), E::one()).reciprocal().is_one());
    EXPECT_THROW((Unit<E>(E::zero(), E::one())), std::domain_error);
    EXPECT_THROW((Nonzero<E>(E::zero())), std::domain_error);
    EXPECT_TRUE((Nonzero<E>::one() * Nonzero<E>::one()).is_one());
    const auto nonzero = NonzeroGroup<E>::element(E::one());
    const interfaces::AbelianGroup<Nonzero<E>, Multiplication>& view = nonzero.parent();
    EXPECT_TRUE(view.inverse(Multiplication{}, nonzero).is_one());
}

TEST(NumericBounds, ChecksPrimalityAndCardinalityOverflow) {
    static_assert(is_prime(2));
    static_assert(is_prime(11));
    static_assert(!is_prime(1));
    static_assert(!is_prime(9));
    EXPECT_EQ(checked_power(11, 3), 1331u);
    EXPECT_THROW(checked_power(11, 30), std::overflow_error);
}

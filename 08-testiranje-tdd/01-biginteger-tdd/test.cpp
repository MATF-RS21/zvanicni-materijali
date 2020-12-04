#include "catch.hpp"

#include "BigInteger.hpp"

TEST_CASE("Creating the BigInteger", "[BigInteger][constructor]")
{
    SECTION("When BigInteger is default-constructed, its value is zero")
    {
        const BigInteger bigInt;
        const auto expected{0};
        
        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed from one letter string, its value is number in that string")
    {
        const BigInteger bigInt{"1"};
        const auto expected{1};
        
        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed from more than one letter string, the number of digits are equal to the size of the string")
    {
        const BigInteger bigInt{"1234"};
        const auto expected{4u};

        const auto result{bigInt.numberOfDigits()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed from multi-letter string, its value is number in that string")
    {
        const BigInteger bigInt{"123456789"};
        const auto expected{123456789};

        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is default-constructed, its sign is Zero")
    {
        const BigInteger bigInt;
        const auto expected{BigInteger::Zero};

        const auto result{bigInt.sign()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed with a positive number string, its sign is Positive")
    {
        const BigInteger bigInt{"123456789"};
        const auto expected{BigInteger::Positive};

        const auto result{bigInt.sign()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed with a negative number string, its sign is Negative")
    {
        const BigInteger bigInt{"-123456789"};
        const auto expected{BigInteger::Negative};

        const auto result{bigInt.sign()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed with a zero, its sign is Zero")
    {
        const BigInteger bigInt{"0"};
        const auto expected{BigInteger::Zero};

        const auto result{bigInt.sign()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed with a negative number string, its value is the negative number in string")
    {
        const BigInteger bigInt{"-123456789"};
        const auto expected{-123456789};

        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }
}

TEST_CASE("Equality of BigInteger", "[BigInteger][equality]")
{
    SECTION("Two default-constructed BigIntegers are equal")
    {
        const BigInteger bigInt1;
        const BigInteger bigInt2;
        
        const auto equal{bigInt1 == bigInt2};
        REQUIRE(equal);
    }

    SECTION("A default-constructed BigInteger is equal to zero-constructed BigInteger")
    {
        const BigInteger defaultBigInt;
        const BigInteger zeroBigInt{"0"};
        
        const auto equal{defaultBigInt == zeroBigInt};
        REQUIRE(equal);
    }

    SECTION("A default-constructed BigInteger is not equal to nondefault- and nonzero-constructed BigInteger")
    {
        const BigInteger defaultBigInt;
        const BigInteger bigInt{"123456789"};
        
        const auto equal{defaultBigInt == bigInt};
        REQUIRE_FALSE(equal);
    }

    SECTION("Two positive-constructed BigInteger are not equal if they have different number of digits")
    {
        const BigInteger bigInt1{"1"};
        const auto numOfDigits1{bigInt1.numberOfDigits()};
        const BigInteger bigInt2{"123456789"};
        const auto numOfDigits2{bigInt2.numberOfDigits()};
        
        const auto differentNumOfDigits{numOfDigits1 != numOfDigits2};
        const auto equal{bigInt1 == bigInt2};

        CHECK(differentNumOfDigits);
        REQUIRE_FALSE(equal);
    }

    SECTION("Two positive-constructed BigInteger are not equal if they have different number of digits")
    {
        const BigInteger bigInt1{"1"};
        const auto numOfDigits1{bigInt1.numberOfDigits()};
        const BigInteger bigInt2{"123456789"};
        const auto numOfDigits2{bigInt2.numberOfDigits()};
        
        const auto differentNumOfDigits{numOfDigits1 != numOfDigits2};
        const auto equal{bigInt1 == bigInt2};

        CHECK(differentNumOfDigits);
        REQUIRE_FALSE(equal);
    }

    SECTION("Two positive-constructed BigInteger are not equal if they are constructed from different strings with same length")
    {
        const BigInteger bigInt1{"987654321"};
        const BigInteger bigInt2{"123456789"};
        
        const auto equal{bigInt1 == bigInt2};

        REQUIRE_FALSE(equal);
    }

    SECTION("Two positive-constructed BigInteger are equal if they are constructed from the same strings")
    {
        const BigInteger bigInt1{"123456789"};
        const BigInteger bigInt2{"123456789"};
        
        const auto equal{bigInt1 == bigInt2};

        REQUIRE(equal);
    }

    SECTION("Two negative-constructed BigInteger are not equal if they are constructed from different strings with same length")
    {
        const BigInteger bigInt1{"-987654321"};
        const BigInteger bigInt2{"-123456789"};
        
        const auto equal{bigInt1 == bigInt2};

        REQUIRE_FALSE(equal);
    }

    SECTION("Two negative-constructed BigInteger are equal if they are constructed from the same strings")
    {
        const BigInteger bigInt1{"-123456789"};
        const BigInteger bigInt2{"-123456789"};
        
        const auto equal{bigInt1 == bigInt2};

        REQUIRE(equal);
    }
}

// Za domaci: TDD pristupom razviti ostatak implementacije

TEST_CASE("Sum of two BigIntegers", "[BigInteger][sum]")
{

}

TEST_CASE("Subtraction of two BigIntegers", "[BigInteger][sub]")
{

}

TEST_CASE("Product of two BigIntegers", "[BigInteger][prod]")
{

}

TEST_CASE("Division of two BigIntegers", "[BigInteger][div]")
{

}

TEST_CASE("Output of BigIntegers", "[BigInteger][output]")
{

}

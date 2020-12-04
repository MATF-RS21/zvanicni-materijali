#include "catch.hpp"

#include "HelloClass.hpp"

SCENARIO("Should be able to greet with Hello BDD! message")
{
    GIVEN("an instance of Hello class is created")
    {
        const HelloClass hello;

        WHEN("the sayHello method is invoked")
        {
            const auto result{hello.sayHello()};

            THEN("it should return \"Hello BDD!\"")
            {
                const auto expected{"Hello BDD!"};

                REQUIRE(result == expected);
            }
        }
    }
}

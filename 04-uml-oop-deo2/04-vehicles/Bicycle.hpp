#ifndef BICYCLE_HPP
#define BICYCLE_HPP

#include "Vehicle.hpp"

class Bicycle : public Vehicle
{
public:
    Bicycle(const unsigned wheels = 2u, const unsigned seats = 1u)
        : Vehicle(wheels, seats)
    {
    }

    Vehicle *Copy() const override
    {
        return new Bicycle(*this);
    }

    std::string Type() const override
    {
        return "Bicycle";
    }
};

std::ostream &operator<<(std::ostream &out, const Bicycle &b)
{
    return out << b.Type() << " " << b.NumOfSeats() << " " << b.NumOfWheels();
}

#endif // BICYCLE_HPP

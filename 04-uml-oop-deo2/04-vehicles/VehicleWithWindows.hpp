#ifndef VEHICLEWITHWINDOWS_HPP
#define VEHICLEWITHWINDOWS_HPP

#include "Vehicle.hpp"

class VehicleWithWindows : public Vehicle
{
public:
    unsigned NumOfWindows() const
    {
        return m_numOfWindows;
    }

protected:
    VehicleWithWindows(const unsigned windows, const unsigned seats, const unsigned wheels)
        : Vehicle(wheels, seats), m_numOfWindows(windows)
    {
    }

    unsigned m_numOfWindows;
};

std::ostream &operator<<(std::ostream &out, const VehicleWithWindows &vsp)
{
    return out << vsp.Type() << " " << vsp.NumOfSeats() << " " << vsp.NumOfWheels() << " " << vsp.NumOfWindows();
}

#endif // VEHICLEWITHWINDOWS_HPP

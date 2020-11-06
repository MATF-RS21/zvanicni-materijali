#ifndef VEHICLEPARK_HPP
#define VEHICLEPARK_HPP

#include <vector>

#include "Vehicle.hpp"

class VehiclePark
{
public:
    VehiclePark() = default;
    ~VehiclePark()
    {
        // Brisemo memoriju na koju pokazuju pokazivaci iz vektora
        for (auto v : m_vehicles)
        {
            delete v;
        }
        // Cistimo vektor (bice podrazumevano uradjeno)
        m_vehicles.clear();
    }

    VehiclePark(const VehiclePark &other)
    {
        for (const auto v : other.m_vehicles)
        {
            m_vehicles.push_back(v->Copy());
        }
        // Zasto nije moglo sledece:
        // m_vehicles = other.m_vehicles
    }

    // Implementiramo netrivijalni destruktor i konstruktor kopije.
    // Prema "pravilu 5", treba implementirati i:
    // - operator dodeljivanja sa semantikom kopiranja
    // - konstruktor pomeranja
    // - operator dodeljivanja sa semantikom pomeranja
    // Uraditi za domaci!

    void Add(Vehicle *vehicle)
    {
        m_vehicles.push_back(vehicle);
    }

private:
    // Ako deklarisemo u klasi da je neki metod ili neka funkcija njen prijatelj,
    // sto mozemo uraditi navodjenjem kljucne reci kao u primeru ispod,
    // onda taj metod, odnosno, ta funkcija moze pristupati i privatnim clanicama klase.
    friend std::ostream &operator<<(std::ostream &out, const VehiclePark &vp);

    std::vector<Vehicle *> m_vehicles;
};

// Ova funkcija moze da pristupi privatnoj clanici m_vehicles klase VehiclePark,
// zato sto je u njoj deklarisana kao prijatelj.
std::ostream &operator<<(std::ostream &out, const VehiclePark &vp)
{
    for (const auto v : vp.m_vehicles)
    {
        out << *v << ", ";
    }
    return out;
}

#endif // VEHICLEPARK_HPP
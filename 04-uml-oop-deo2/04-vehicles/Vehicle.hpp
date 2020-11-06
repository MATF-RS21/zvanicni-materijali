#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>
#include <iostream>

class Vehicle
{
public:
    virtual ~Vehicle() = default;

    // Tip vozila je nepoznat za baznu klasu,
    // pa zato ovaj metod mora biti apstraktan (notacija `= 0` ispod).
    // Apstraktne klase se ne mogu instancirati, vec vazi pravilo:
    // - U stablu hijerarhije na svakom putu od korena (bazne klase)
    //   do svih listova (najspecificnijih izvedenih klasa)
    //   mora postojati makar jedna implementacija apstraktnog metoda.
    // Na primer, na putu `Vehicle` -> `VehicleWithWindow` -> `Car`,
    // apstraktni metod `Type()` je implementiran u klasi `Car`.
    // Metodi koji su virtualni i apstraktni se nazivaju "cisto virtualni" (engl. pure virtual).
    virtual std::string Type() const = 0;

    // Zasto kreiramo metod koji vraca pokazivac na kopiju objekta?
    // Zato sto konstruktor kopije ne moze biti virtualan!
    // Umesto toga, metod `Copy()` ce u konkretnim klasama biti prevazidjen
    // tako da vraca dinamicki objekat odgovarajuceg tipa.
    // Na primer, u klasi `Car`, ovaj metod kreira dinamicki objekat tipa `Car` i vraca `Car *`.
    // Konverzija iz `Car *` u `Vehicle *` je trivijalna jer je uz istu hijerarhiju.
    virtual Vehicle *Copy() const = 0;

    unsigned NumOfWheels() const
    {
        return m_numOfWheels;
    }

    unsigned NumOfSeats() const
    {
        return m_numOfSeats;
    }

protected:
    Vehicle(const unsigned wheels, const unsigned seats)
        : m_numOfWheels(wheels), m_numOfSeats(seats)
    {
    }

    unsigned m_numOfWheels;
    unsigned m_numOfSeats;
};

std::ostream &operator<<(std::ostream &out, const Vehicle &v)
{
    return out << v.Type() << " " << v.NumOfSeats() << " " << v.NumOfWheels();
}

#endif // VEHICLE_HPP

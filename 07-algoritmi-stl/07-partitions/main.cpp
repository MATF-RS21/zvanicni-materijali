// Zadatak: Dat je vektor celih brojeva od 1 do 15.
// Transformisati vektor tako da oni brojevi koji pri deljenju brojem 3:
//   a) daju ostatak 0 idu na pocetak vektora (prva grupa),
//   b) daju ostatak 1 idu nakon prve grupe (druga grupa),
//   c) daju ostatak 2 idu nakon druge grupe (treca grupa).

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

// Funkcijski objekti ili funkcionali (eng. function objects)
// predstavljaju objekte klasa koji se koriste umesto funkcija.
// Uglavnom se koriste ukoliko izracunavanje neke funkcije
// zavisi od stanja koje se definise u fazi izracunavanja
// (inace, mozemo koristiti sablone).
class DivideRemainderComparator
{
public:
    DivideRemainderComparator(int divider, int remainder)
        : divider_(divider), remainder_(remainder)
    {
    }

    // Da bi objekat klase bio funkcijski objekat,
    // on mora da implementira operator poziva funkcijskog objekta (eng. call operator)
    // ciji je naziv "operator()", a koji moze imati proizvoljne parametre i povratnu vrednost.
    // Obratite paznju na dve vrste zagrada ispod: prve su deo naziva metoda, a druga predstavlja listu parametara.
    bool operator()(const int x) const
    {
        return (x % divider_ == remainder_);
    }

private:
    int divider_;
    int remainder_;
};

int main(int argc, char *argv[])
{
    std::vector<int> xs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    // Funkcijske objekte mozemo instancirati posebno.
    DivideRemainderComparator div_by_3_remainder_0(3, 0);

    // Izdvajamo elemente koji su deljivi brojem 3 na pocetak kolekcije.
    // Algoritam vraca iterator na prvi element koji nije deljiv nakon razdvajanja.
    const auto first_end =
        std::stable_partition(std::begin(xs), std::end(xs),
                              // Funkcijski objekat ce biti pozvan kao funkcija za potrebe izvrsavanja algoritma std::stable_partition
                              div_by_3_remainder_0);

    // Particionisemo ostatak kolekcije (preskacemo elemente koji su deljivi brojem 3).
    // Druga grupa ce imati samo elemente koji daju ostatak 1 pri deljenju brojem 3,
    // dok su elementi iz intervala [second_end, std::end(xs)) u trecoj grupi.
    const auto second_end =
        std::stable_partition(first_end, std::end(xs),
                              // Funkcijske objekte mozemo koristiti i kao privremene objekte
                              DivideRemainderComparator{3, 1});

    std::cout << "Deljivi brojem 3 u xs:" << std::endl;
    std::copy(std::begin(xs), first_end, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nDaju ostatak 1 deljenjem brojem 3 u xs:" << std::endl;
    std::copy(first_end, second_end, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nDaju ostatak 2 deljenjem brojem 3 u xs:" << std::endl;
    std::copy(second_end, std::end(xs), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}

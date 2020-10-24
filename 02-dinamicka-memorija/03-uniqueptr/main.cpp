// Rad sa std::unique_ptr "pametnim" pokazivacem
#include <memory>
#include <string>
#include <iostream>

struct example_object
{
    example_object(const int number, const std::string &text)
        : m_number(number), m_text(text)
    {
        std::cout << "Kreiran je example_object(" << m_number << ", " << m_text << ")" << std::endl;
    }

    ~example_object()
    {
        std::cout << "Obrisan je example_object(" << m_number << ", " << m_text << ")" << std::endl;
    }

    std::string to_string(const std::string &message)
    {
        return message + ": " + std::to_string(m_number) + " - " + m_text;
    }

    int m_number;
    std::string m_text;
};

void test_ownership_change(const std::unique_ptr<example_object> p)
{
    std::cout << p->to_string("U funkciji test_ownership_change") << std::endl;
}

// Primetimo da funkcija ne prima pokazivac kao const.
// Ako bi to radila, onda ne bi mogla da ga "pomeri" nazad kao povratnu vrednost
// jer konstantne podatke ne mozemo pomerati!
std::unique_ptr<example_object> test_ownership_change_and_return(std::unique_ptr<example_object> p)
{
    std::cout << p->to_string("U funkciji test_ownership_change_and_return") << std::endl;
    return p;
}

void test_ref_forward(const std::unique_ptr<example_object> &p)
{
    std::cout << p->to_string("U funkciji test_ref_forward") << std::endl;
}

int main()
{
    // Klasa std::unique_ptr sluzi da zameni koriscenje "cistih" pokazivaca
    // u situacijama kada najvise jedan pokazivac moze da sadrzi adresu na neki objekat,
    // odnosno kada je taj pokazivac glavni i jedini odgovorni vlasnik nad objektom.
    auto p1 = std::make_unique<example_object>(10, "Ovaj objekat sadrzi broj 10");
    // Kopiranje nije dozvoljeno:
    // const auto p2(p1);   // Konstruktor kopije je obrisan (= delete)
    std::unique_ptr<example_object> p3 = nullptr;
    // p3 = p1; // Operator dodele sa semantikom kopiranja je obrisan (= delete)

    // Za unique_ptr (kao i shared_ptr) imamo predefinisane operatore * i -> tako da se
    // unique_ptr objekat sa njima ponasa kao da je sirovi pokazivac, odnosno operator *
    // vrsi dereferensiranje, a -> vrsi pristup objektu na koji pokazuje pametni pokazivac.
    std::cout << p1->to_string("p1") << std::endl;

    std::cout << std::endl;
    std::cout << "Testiramo da li je vlasnistvo prebaceno sa p1 na p2..." << std::endl;

    // Ne mozemo da kopiramo unique_ptr, ali mozemo da ga "pomerimo",
    // odnosno, da pozovemo konstruktor sa semantikom pomeranja ("move konstruktor")
    // (videcemo sta je move konstruktor kada budemo pricali o podrsci za OOP u jeziku C++).
    auto p2(std::move(p1));
    // Linija iznad je isto sto i linija ispod - poziv move konstruktora
    // auto p2 = std::move(p1);

    // U klasi unique_ptr je definisan operator konverzije u bool tako da vraca true,
    // ako unique_ptr pokazuje na neki objekat, odnosno ako vazi get() != nullptr.
    // Kada se promeni vlasnistvo nad objektom, odnosno pozove move konstruktor za unique_ptr,
    // stari unique_ptr ce biti azuriran da pokazuje na nullptr
    // i operator bool za njega ce vracati false (primer ispod).
    if (p1 != nullptr)
    {
        std::cout << p1->to_string("p1") << std::endl;
    }
    else if (p2 != nullptr)
    {
        std::cout << p2->to_string("p2") << std::endl;
    }
    else
    {
        std::cout << "Ni p1 ni p2 nemaju vlasnistvo nad dinamickim objektom" << std::endl;
    }

    p3 = std::move(p2); // Ovo je operator dodeljivanja sa semantikom pomeranja ("move operator dodele")

    std::cout << std::endl;
    std::cout << "Testiramo prosledjivanje pametnog pokazivaca kao argument funkcije..." << std::endl;

    // Naredna linija proizvodi gresku zato sto se pokusava kopiranje std::unique_ptr objekta
    // test_ownership_change(p3);

    // Ali zato naredni poziv uspeva, sa napomenom da ce funkcija preuzeti vlasnistvo objekta.
    // Posto funkcija preuzima vlasnistvo, nakon sto se ona zavrsi i njen argument p biva unisten sa njenog steka,
    // i sam objekat na koji je taj argument p pokazivao ce biti dealociran sa hipa.
    test_ownership_change(std::move(p3));

    if (p3 != nullptr)
    {
        std::cout << p3->to_string("p3") << std::endl;
    }
    else
    {
        std::cout << "p3 je izgubio vlasnistvo nad dinamickim objektom" << std::endl;
    }

    // Ako zelimo da "pomerimo" objekat koji smo prosledili nekoj funkciji nazad u p3,
    // onda mozemo da definisemo da funkcija vraca taj prosledjeni pokazivac.
    p3 = std::make_unique<example_object>(42, "Ovaj objekat sadrzi broj 42");
    p3 = test_ownership_change_and_return(std::move(p3));

    if (p3 != nullptr)
    {
        std::cout << p3->to_string("p3") << std::endl;
    }
    else
    {
        std::cout << "p3 je izgubio vlasnistvo nad dinamickim objektom" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Testiramo promenu vlasnistva pametnog pokazivaca u funkciji kada se on prenosi po referenci..." << std::endl;

    auto p4 = std::make_unique<example_object>(15, "Ovaj objekat sadrzi broj 15");
    std::cout << p4->to_string("p4") << std::endl;

    // Naravno, pokazivac mozemo preneti i po referenci.
    // U tom slucaju nece doci do prenosa vlasnistva.
    test_ref_forward(p4);

    if (p4 != nullptr)
    {
        std::cout << p4->to_string("p4") << std::endl;
    }
    else
    {
        std::cout << "p4 je izgubio vlasnistvo nad dinamickim objektom" << std::endl;
    }

    // Sirovi pokazivac mozemo izvuci koristeci funkciju `get()`.
    // Ovo bi trebalo izbegavati, osim ukoliko nemamo dobar razlog za to - na primer
    // neki stari deo projekta bas zahteva da se prosledi sirovi pokazivac, a nemamo
    // vremena ili dozvolu da menjamo taj deo projekta.
    example_object *raw_ptr = p4.get();

    if (raw_ptr != nullptr)
    {
        std::cout << "raw_ptr: " << raw_ptr->m_number << " - " << raw_ptr->m_text << std::endl;
    }
    else
    {
        std::cout << "raw_ptr nije uspeo da dobije cist pokazivac nad dinamickim objektom" << std::endl;
    }

    return 0;
}

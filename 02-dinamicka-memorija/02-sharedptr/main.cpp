// Rad sa std::shared_ptr "pametnim" pokazivacem
#include <memory>
#include <string>
#include <iostream>

struct example_object
{
    example_object(const int number, const std::string & text)
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

void test_shared_ptr_copy(const std::shared_ptr<example_object> p)
{
    std::cout << p->to_string("U funkciji test_shared_ptr_copy") << std::endl;
}

int main()
{
    // Klasa std::shared_ptr sluzi da zameni koriscenje "cistih" pokazivaca
    // u situacijama kada vise pokazivaca moze da sadrzi adresu na neki objekat.
    // Objekat std::shared_ptr vrsi brojanje referenci na objekat koji je prosledjen pri konstrukciji
    // prvog shared_ptr objekta, i automatski ga dealocira kada broj referenci postane 0.
    // Nije u pitanju nikakva magija i dodatak u jeziku koji omogucava "automatsku" dealokaciju,
    // u pitanju je poziv destruktor klase shared_ptr koji dealocira objekat kada broj referenci postane 0.
    const auto p1 = std::make_shared<example_object>(10, "Ovaj objekat sadrzi broj 10");
    const auto p2(p1); // konstruktor sa semantikom kopiranja ("copy konstruktor")
    std::shared_ptr<example_object> p3 = nullptr;
    p3 = p2; // operator dodele sa semantikom kopiranja ("copy operator dodele")

    std::cout << "Testiramo da li p1, p2 i p3 pokazuju na isti objekat..." << std::endl;
    std::cout << p1->to_string("p1") << std::endl;
    std::cout << p2->to_string("p2") << std::endl;
    std::cout << p3->to_string("p3") << std::endl;

    // Funkcija `use_count()` prikazuje broj referenci na objekat. U nasem slucaju
    // bice 3 usled pokazivaca p1, p2 i p3.
    std::cout << "Broj referenci na objekat: " << p1.use_count() << std::endl;

    {
        std::shared_ptr<example_object> p4 = p1;
        // Sada ce broj referenci biti 4.
        std::cout << "Broj referenci na objekat: " << p1.use_count() << std::endl;
    }

    // Nakon sto je istekao doseg za p4 i on je obrisan, broj referenci ce biti 3.
    std::cout << "Broj referenci na objekat: " << p1.use_count() << std::endl;

    std::cout << "Testiramo prosledjivanje pametnog pokazivaca kao argument funkcije..." << std::endl;
    test_shared_ptr_copy(p1);

    return 0;
}

#include <list>
#include <iostream>

// Tip std::list<T, ...> predstavlja dvostruko povezanu listu (DPL) vednosti tipa T.
void list_showcase()
{
    // Inicijalizacija DPL pocetnim elementima
    std::list<std::string> keywords{"if", "unsigned", "while", "void"};

    std::cout << "keywords:" << std::endl;
    for (const auto &keyword : keywords)
    {
        std::cout << keyword << " " << std::endl;
    }
    std::cout << std::endl;

    // Provera da li je DPL prazna.
    // Vremenska slozenost: Konstantna
    if (!keywords.empty())
    {
        // Izracunavanje broja elemenata
        // Vremenska slozenost: Konstantna (od C++11)
        std::cout << "Broj elemenata u DPL: " << keywords.size() << std::endl;

        // Pristupanje prvom i poslednjem elementu.
        // Vremenska slozenost: Konstantna
        std::cout << "Prvi element DPL je: \"" << keywords.front() << "\"" << std::endl;
        std::cout << "Poslednji element DPL je: \"" << keywords.back() << "\"" << std::endl;
    }

    // Unosenje jednog ili vise elemenata ispred nekog elementa.
    // Vremenska slozenost: Konstantna (u slucaju unosa jedne vrednosti) ili linearna po broju unetih vrednosti
    std::cout << "Dodaje se 'return' na pocetak." << std::endl;
    keywords.insert(keywords.cbegin(), "return");
    std::cout << "Dodaje se '>' na pocetak 3 puta." << std::endl;
    keywords.insert(keywords.cbegin(), 3, ">");
    std::cout << "Dodaje se '<' na kraj 3 puta." << std::endl;
    keywords.insert(keywords.cend(), 3, "<");

    // Unosenje elementa na pocetak i kraj DPL.
    // Vremenska slozenost: Konstantna
    std::cout << "Dodaje se '{' na pocetak." << std::endl;
    keywords.push_front("{");
    std::cout << "Dodaje se '}' na kraj." << std::endl;
    keywords.push_back("}");

    // Prolazak kroz DPL kolekcijskom petljom
    for (const auto &rec : keywords)
    {
        std::cout << rec << " ";
    }
    std::cout << std::endl;
}

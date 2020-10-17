#include <forward_list>
#include <iostream>

/// Tip std::forward_list<T, ...> predstavlja jednostruko povezanu listu (JPL) vrednosti tipa T.
void forward_list_showcase()
{
    // Inicijalizacija JPL.
    std::forward_list<char> chars{'R', 'a', 'z', 'v', 'o', 'j', ' ', 'S', 'o', 'f', 't', 'v', 'e', 'r', 'a'};

    // Vrlo slicno kao za vektor, provera da li je kolekcija prazna i pristup elementima.
    if (!chars.empty())
    {
        std::cout << "Prvi element je: " << chars.front() << std::endl;
        // Primetite da funkcija `back()` ne postoji, da li mozete da pretpostavite zasto?
        //std::cout << "Poslednji element je: " << chars.back() << std::endl;
    }

    // Pored `cbegin()`, `begin()`, `cend()` i `end()` iteratora postoje i iteratori
    // `cbefore_begin()` i `before_begin()` iteratori koji pokazuju na prvu poziciju
    // pre pocetka liste. Namena ovog iteratora je na primer za funkcije poput:
    // `insert_after()`, `emplace_after()`, `erase_after()`, `splice_after()`.
    auto iter = chars.before_begin();
    std::cout << "Iterator before_begin "
              << ((++iter == chars.begin()) ? "jeste" : "nije")
              << " ispred begin iteratora" << std::endl;

    // Dodajemo element pre elementa na koji pokazuje prosledjeni iterator,
    // u ovom slucaju, dodajemo '>' na pocetak liste.
    // Vremenska slozenost:
    //  * konstantna - u slucaju unosa jedne vrednosti
    //  * linearna po broju unetih vrednosti
    chars.insert_after(chars.cbefore_begin(), '>');

    // Iterira se kroz listu.
    for (const auto &ch : chars)
    {
        std::cout << ch;
    }
    std::cout << std::endl;

    // Obrtanje liste u mestu.
    // Vremenska slozenost: Linearna
    // Da li znate algoritam vremenske slozenosti O(n) i memorijske slozenosti O(1)
    // koji vrsi obrtanje jednostruko povezane liste duzine n?
    chars.reverse();
    // Dodajemo tri karaktera `!` na pocetak (obrnute liste).
    chars.insert_after(chars.cbefore_begin(), 3, '!');
    chars.reverse();

    for (const auto &ch : chars)
    {
        std::cout << ch;
    }
    std::cout << std::endl;
}

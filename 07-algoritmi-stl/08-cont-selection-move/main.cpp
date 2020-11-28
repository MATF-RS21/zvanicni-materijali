// Zadatak: Napisati sablonsku funkciju slide_selection koja prihvata
// iteratore na pocetak i kraj dela kolekcije i iterator na poziciju
// ispred koje se pomeraju elementi datog dela kolekcije.
// Funkcija treba da izvrsi dato pomeranje i vrati par iteratora
// koji pokazuju na pomereni deo kolekcije.

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

template <typename It>
std::pair<It, It> slide_selection(It selection_begin, It selection_end, It destination)
{
    if (destination < selection_begin)
    {
        // Ne moramo koristiti std::make_pair, vec ga mozemo konstruisati inicijalizatorom
        return {
            destination,
            // Algoritam vrsi levu rotaciju dela kolekcije, tako sto zamenjuje elemente iz [first, last)
            // tako da element n_first postaje prvi element u novom delu kolekcije
            // i element n_first - 1 postaje poslednji element u novom delu kolekcije.
            // (Od C++11) Algoritam vraca iterator na novu lokaciju elementa koji pokazuje na first,
            // tj. first + (last - n_first).
            std::rotate(/* first = */ destination, /* n_first = */ selection_begin, /* last = */ selection_end)};
    }

    if (selection_end < destination)
    {
        return {
            std::rotate(selection_begin, selection_end, destination),
            destination};
    }

    const auto first = selection_begin - (selection_end - destination);
    return {first, std::rotate(first, selection_begin, selection_end)};
}

int main()
{
    std::vector<std::string> items{
        "aardvark",
        "compunctious",
        "**congratulations**", // +2 --> selection_begin
        "**contrafribblarity**",
        "**contrary**",
        "dictionary", // +5 --> selection_end
        "interphrastical",
        "patronise", // +7 --> destination
        "pericombobulation",
        "phrasmotic",
        "syllables"};

    const auto [selection_begin, selection_end] =
        slide_selection(std::begin(items) + 2,
                        std::begin(items) + 5,
                        std::begin(items) + 7);

    // std::copy(selection_begin, selection_end,
    //           std::ostream_iterator<std::string>(std::cout, "\n"));
    // std::cout << std::endl;

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    std::cout << "---" << std::endl;

    std::vector<std::string> items2 = {
        "aardvark", // +0 --> destination
        "compunctious",
        "dictionary",
        "interphrastical",
        "**congratulations**", // +4 --> selection_begin
        "**contrafribblarity**",
        "**contrary**", 
        "patronise", // +7--> selection_end
        "pericombobulation",
        "phrasmotic",
        "syllables"};

    slide_selection(std::begin(items2) + 4,
                    std::begin(items2) + 7,
                    std::begin(items2) + 0);

    std::copy(std::begin(items2), std::end(items2),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    std::cout << "---" << std::endl;

    std::vector<int> items3{
        0,
        1,
        2,
        3,
        9,
        10,
        4, // +6 --> selection_begin
        5,
        6,
        7, // +9 --> destination
        8,
        11, // +11 --> selection_end
        12};

    slide_selection(std::begin(items3) + 6,
                    std::begin(items3) + 11,
                    std::begin(items3) + 9);

    std::copy(std::begin(items3), std::end(items3),
              std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}

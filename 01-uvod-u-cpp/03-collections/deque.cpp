#include <deque>
#include <iostream>

void deque_showcase()
{
    std::deque<unsigned> xs{0, 1, 2, 3, 4, 5, 6, 7};

    for (const auto &x : xs)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "Istraziti mogucnosti kolekcije std::deque<T, ...> za domaci." << std::endl
              << "Napraviti uporednu analizu sa preostalim kolekcijama." << std::endl;
} 

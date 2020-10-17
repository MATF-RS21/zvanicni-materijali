#include <set>
#include <iostream>
#include <chrono>

static std::set<double> init_set_with_values();
static void print_set(const std::set<double> &xs);
static void find_element_in_set(const std::set<double> &xs);
static void find_upper_bound_element_in_set(const std::set<double> &xs);
static void find_lower_bound_element_in_set(const std::set<double> &xs);
static void find_first_lower_element_in_set(const std::set<double> &xs);
static void insert_elements_in_set(std::set<double> &xs);

/// Tip std::set<T, ...> predstavlja kolekciju koja
/// sadrzi uredjeni skup jedinstvenih vrednosti.
void set_showcase()
{
    auto xs = init_set_with_values();
    print_set(xs);
    find_element_in_set(xs);
    find_upper_bound_element_in_set(xs);
    find_lower_bound_element_in_set(xs);
    find_first_lower_element_in_set(xs);
    insert_elements_in_set(xs);
    print_set(xs);
} 

std::set<double> init_set_with_values()
{
    // Inicijalizacija skupa pocetnim vrednostima.
    return std::set<double>{1.0, 2.0, 3.0, -1.0, -4.3, -2.0, 5.0, -6.4};
}

void print_set(const std::set<double> &xs)
{
    // Prikazujemo korisniku skup.
    std::cout << "[Ispis elemenata skupa]" << std::endl;
    for (const auto &x : xs)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void find_element_in_set(const std::set<double> &xs)
{
    std::cout << "\n[Pretraga broja]" << std::endl;
    std::cout << "Unesite broj za pretragu:" << std::endl;
    double x;
    std::cin >> x;

    // Pronalazak elementa u skupu.
    // Vremenska slozenost: Logaritamska
    const auto iter = xs.find(x);
    if (iter != xs.cend())
    {
        std::cout << "Pronadjen je element " << *iter << std::endl;
    }
    else
    {
        std::cout << "Nije pronadjen element " << x << std::endl;
    }
}

void find_upper_bound_element_in_set(const std::set<double> &xs)
{
    std::cout << "\n[Pretraga prvog veceg]" << std::endl;
    std::cout << "Unesite broj za pretragu:" << std::endl;
    double x;
    std::cin >> x;

    // Pretraga prvog elementa strogo veceg od datog.
    // Vremenska slozenost: Logaritamska
    const auto iter = xs.upper_bound(x);
    if (iter != xs.cend())
    {
        std::cout << "Pronadjen je prvi element " << *iter << " strogo veci od " << x << std::endl;
    }
    else
    {
        std::cout << "Nije pronadjen element strogo veci od " << x << std::endl;
    }
}

void find_lower_bound_element_in_set(const std::set<double> &xs)
{
    std::cout << "\n[Pretraga prvog veceg ili jednakog]" << std::endl;
    std::cout << "Unesite broj za pretragu:" << std::endl;
    double x;
    std::cin >> x;

    // Pretraga prvog elementa veceg ili jednakog od datog.
    // Vremenska slozenost: Logaritamska
    const auto iter = xs.lower_bound(x);
    if (iter != xs.cend())
    {
        std::cout << "Pronadjen je prvi element " << *iter << " veci ili jednak od " << x << std::endl;
    }
    else
    {
        std::cout << "Nije pronadjen element veci ili jednak od " << x << std::endl;
    }
}

void find_first_lower_element_in_set(const std::set<double> &xs)
{
    std::cout << "\n[Pretraga prvog strogo manjeg]" << std::endl;
    std::cout << "Unesite broj za pretragu:" << std::endl;
    double x;
    std::cin >> x;

    // Kako da nadjemo prvi element strogo manji od zadatog?
    auto iter = xs.lower_bound(x); // 1. Pronadji prvi veci ili jednak
    --iter; // 2. Pomeri iterator za 1 unazad (prvi element pre pronadjenog)
    if (iter != xs.cend())
    {
        std::cout << "Pronadjen je prvi element " << *iter << " strogo manji od " << x << std::endl;
    }
    else
    {
        std::cout << "Nije pronadjen element strogo manji od " << x << std::endl;
    } 
}

void insert_elements_in_set(std::set<double> &xs)
{
    std::cout << "\n[Dodavanje elemenata u skup]" << std::endl;

    // Unos jednog elementa u skup
    xs.insert(15.0);

    // Mozemo dodati element u skup zadavajuci iterator pozicije, tj. "hint" gde bi trebalo ubaciti element
    xs.insert(xs.cbegin(), -100.0);
    // Ovo preopterecenje treba inteligentno koristiti, 
    // inace slozenost moze biti gora nego da smo pozvali bez prosledjivanja "hint"-a
    auto begin = std::chrono::steady_clock::now();
    auto iter = xs.insert(xs.cbegin(), 5000.0);
    auto end = std::chrono::steady_clock::now();
    const auto t_period1 = end - begin;

    // Brisemo uneti element kako bismo vratili skup na pocetno stanje
    xs.erase(iter);

    begin = std::chrono::steady_clock::now();
    auto [iter2, _] = xs.insert(5000.0);
    end = std::chrono::steady_clock::now();
    const auto t_period2 = end - begin;

    std::cout << (t_period2 < t_period1 ? "Brze je bez hinta" : "Brze je sa losim hintom") << std::endl;

    // Brisemo uneti element kako bismo vratili skup na pocetno stanje
    xs.erase(iter2);

    // A da li je bolje ako damo dobar hint?
    begin = std::chrono::steady_clock::now();
    xs.insert(xs.cend(), 5000.0);
    end = std::chrono::steady_clock::now();
    const auto t_period3 = end - begin;
    std::cout << (t_period2 < t_period3 ? "Brze je bez hinta\n" : "Brze je sa dobrim hintom\n") << std::endl;

    // Unos vise elemenata u skup
    xs.insert({7.3, 5.0, 7.3, 3.0, 4.0});
}

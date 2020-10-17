#include <vector>
#include <complex>
#include <iterator>
#include <iostream>

// Funkcije oznacene kljucnom recju static imaju unutrasnje povezivanje,
// tj. nece biti vidljive u drugim kompilacionim jedinicama.
static std::vector<int> init_vector_with_ints_from_stdin();
static void print_vector_size(const std::vector<int> &xs);
static void insert_into_vector(std::vector<int> &xs);
static void print_vector_values_with_for(const std::vector<int> &xs);
static void print_some_elements_of_vector(const std::vector<int> &xs);

static std::vector<std::complex<double>> init_vector_with_complex_nums();
static void emplace_values_into_vector(std::vector<int> &xs, std::vector<std::complex<double>> &cs);
static void print_vector_values_with_forward_iterator(const std::vector<std::complex<double>> &cs);
static void erase_some_elements_from_vector(std::vector<std::complex<double>> &cs);
static void print_vector_values_with_reverse_iterator(const std::vector<std::complex<double>> &cs);

// Ako se za neku funkciju ne navede tip povezivanja,
// onda se podrazumeva da ima spoljasnje povezivanje (kljucna rec extern)
// i bice vidljiva u drugim kompilacionim jedinicama.
void vector_showcase()
{
    auto xs = init_vector_with_ints_from_stdin();
    print_vector_size(xs);
    insert_into_vector(xs);
    print_vector_values_with_for(xs);
    print_some_elements_of_vector(xs);

    auto cs = init_vector_with_complex_nums();
    emplace_values_into_vector(xs, cs);
    print_vector_values_with_forward_iterator(cs);
    erase_some_elements_from_vector(cs);
    print_vector_values_with_reverse_iterator(cs);
} 

// S obzirom da smo u deklaracijama naveli da naredne funkcije imaju unutrasnje povezivanje,
// onda nije neophodno navoditi kljucnu rec static i u njihovim definicijama.
std::vector<int> init_vector_with_ints_from_stdin()
{
    // Inicijalizacija praznog vektora
    std::vector<int> xs;
    int x;

    std::cout << "Unesite nekoliko celih brojeva: " << std::endl;
    while (std::cin >> x)
    {
        // Dodajemo na kraj vektora svaki uneti broj.
        // Vektor vrsi povremenu realokaciju memorije pri kojoj rezervise
        // vise nego sto mu u tom trenutku potrebno kako bi dodavanje na kraj
        // bilo efikasnije.
        xs.push_back(x);
    }

    return xs;
}

void print_vector_size(const std::vector<int> &xs)
{
    // Izracunavanje broja elemenata vektora.
    if (!xs.empty())
    {
        // Prikazujemo broj elemenata u vektoru.
        std::cout << "\nBroj unetih brojeva: " << xs.size() << std::endl;
    }
    else
    {
        std::cout << "\nVektor je prazan." << std::endl;
    }
}

void insert_into_vector(std::vector<int> &xs)
{
    std::cout << "\nVrsi se dodavanje u vektor xs koristeci `insert`..." << std::endl;
    // Dodaje se broj na pocetak vektora.
    // Umesto std::cbegin i std::cend moze se koristiti i xs.cbegin() i xs.cend.
    // Preporuceno je koristiti opstiju verziju funkcije std::cbegin() i std::cend()
    // jer rade u vise slucajeva u zavinosti od tipa na kojim se pozivaju (na primer pokazivaci).
    xs.insert(std::cbegin(xs), 17);
    // Dodaje se pet 0 na kraj vektora.
    xs.insert(std::cend(xs), 5, 0);
}

void print_vector_values_with_for(const std::vector<int> &xs)
{
    // Ispisivanje sadrzaja vektora koristeci kolekcijsku petlju.
    // Ako zelimo da ispisemo indeks elementa, treba nam brojacka promenljiva.
    size_t i = 0;
    std::cout << "\nSadrzaj vektora:" << std::endl;
    for (const auto &x : xs)
    {
        std::cout << i++ << ". " << x << std::endl;
    }
}

void print_some_elements_of_vector(const std::vector<int> &xs)
{
    // STL kolekcije su pravljenje sa ciljem da budu izuzetno efikasne,
    // tako da se ne vrsi provera granica prilikom pristupu elementima
    // kolekcije. Ovde treba biti pazljiv i obratiti paznju na granice.
    std::cout << "\nPrvi element u vektoru xs: " << xs.front() << std::endl;
    std::cout << "3. element u vektoru xs: " << xs[2] << std::endl;
    std::cout << "Poslednji element u vektoru xs: " << xs.back() << std::endl;
}

std::vector<std::complex<double>> init_vector_with_complex_nums()
{
    // Vracamo objekat tipa std::initializer_list<std::initializer_list<double>>.
    // Zasto se kompilator ne buni?
    return { {1, 2}, {3, 4}, {-1, -2}, {-3, -4} };
}

void emplace_values_into_vector(std::vector<int> &xs, std::vector<std::complex<double>> &cs)
{
    // Dodavanje vrednosti na kraj vektora,
    // pri cemu vrednost konstruisemo u mestu.
    // Vremenska slozenost: Amortizovana konstantna O(1)
    xs.emplace_back(42);
    
    // Za elementarne tipove podataka poput int-a, ovo i nije neka velika usteda.
    // Medjutim, ovo moze biti korisno umesto kreiranja pomocnih promenljivih za vece objekte.
    // Umesto izvrsavanja dve operacije...
    std::complex<double> tmp = { -42.0, 42.0 }; // 1. konstruisanje objekta
    cs.push_back(tmp); // 2. kopiranje objekta na kraj vektora
    
    // ...mozemo koristiti emplace_back() na sledeci nacin:
    cs.emplace_back(-42.0, 42.0); // konstruisanje objekta u mestu (na kraj vektora)
}

void print_vector_values_with_forward_iterator(const std::vector<std::complex<double>> &cs)
{
    // Kroz vektor mozemo da iteriramo unapred i unazad koristeci iteratore.
    std::cout << "\nSadrzaj vektora cs koristeci cbegin:" << std::endl;
    for (auto iter = std::cbegin(cs); iter != std::cend(cs); iter++)
    {
        // Objekat iter predstavlja iterator koji "pokazuje" na element u kolekciji.
        // Zbog toga, elementu mozemo pristupiti pomocu *iter.
        const auto &element = *iter; // Da bismo izbegli kopiranje, kreiramo referencu!

        // Da li nam i ovde treba brojacka promenljiva?
        // Mozemo iskoristiti informaciju o razlici izmedju tekuceg iteratora i pocetnog iteratora:
        const auto i = std::distance(cs.begin(), iter);

        std::cout << i << ". " << element << std::endl;
    }
}

void erase_some_elements_from_vector(std::vector<std::complex<double>> &cs)
{
    std::cout << "\nBrisemo nekoliko elemenata iz cs" << std::endl;

    // Brisanje poslednjeg elementa.
    // Vremenska slozenost: O(1)
    cs.pop_back();

    // Brisanje elementa na poziciji koja je definisana iteratorom,
    // u ovom slucaju, brisemo element na indeksu 0+3=3.
    // Vremenska slozenost: Linearna
    cs.erase(std::cbegin(cs) + 3);
}

void print_vector_values_with_reverse_iterator(const std::vector<std::complex<double>> &cs)
{
    std::cout << "\nSadrzaj vektora xs koristeci crbegin:" << std::endl;
    for (auto iter = std::crbegin(cs); iter != std::crend(cs); iter++)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}
#include <map>
#include <iostream>
#include <string>

using student_type = std::pair<unsigned, std::string>;
using student_map = std::map<unsigned, std::string>;

static student_map init_map();
static void print_map(const student_map &students);
static void find_in_map_1(student_map &students, unsigned &existing_key, unsigned &non_existing_key);
static void find_in_map_2(student_map &students, unsigned &existing_key, unsigned &non_existing_key);
static void insert_in_map(student_map &students, const student_type &new_student, const student_type &new_student_with_same_key);
static void emplace_in_map(student_map &students, unsigned &non_existing_key);
static void insert_or_assign_in_map(student_map &students, const student_type &new_student_with_same_key);

student_map init_map()
{
    const student_map students({{20100050u, "Nevena"},
                                {20110145u, "Petar"},
                                {20100043u, "Ana"}});
    return students;
}

void print_map(const student_map &students)
{
    std::cout << "[Ispisivanje mape]" << std::endl;
    for (const auto &student : students)
    {
        // Elementi mape su objekti klase std::pair<const Key, T>.
        // Oni imaju javna polja first i second kojim se pristupa kljucu, odnosno, vrednosti, redom.
        std::cout << '\t' << student.first << " -> " << student.second << std::endl;
    }
}

void find_in_map_1(student_map &students, unsigned &existing_key, unsigned &non_existing_key)
{
    // Pristupanje elementima sa datim kljucem.
    // Vremenska slozenost: Logaritamska

    // Koriscenjem prvog pristupa - operatorom [],
    // ukoliko kljuc ne postoji u recniku,
    // bice unet novi par vrednosti u recnik,
    // pri cemu se za vrednost u tom paru uzima podrazumevana vrednost za dati tip (std::string u ovom primeru).
    std::cout << "\nStudent sa indeksom " << existing_key
              << " se zove \"" << students[existing_key] << "\"" << std::endl;
    std::cout << "Student sa indeksom " << non_existing_key
              << " se zove \"" << students[non_existing_key] << "\"" << std::endl;
}

void find_in_map_2(student_map &students, unsigned &existing_key, unsigned &non_existing_key)
{
    // Koriscenjem drugog pristupa - metodom at(),
    // ukoliko kljuc ne postoji u recniku,
    // bice ispaljen std::out_of_range izuzetak.
    const auto student_name = students.at(existing_key);
    std::cout << "\nStudent sa indeksom " << existing_key
              << " se zove \"" << student_name << "\"" << std::endl;

    // Pomeramo kljuc (povecavamo broj) jer je prethodna vrednost
    // dodata u mapu kad se izvrsio izraz: students[non_existing_key]
    ++non_existing_key;
    try
    {
        // Sledeca linija ispaljuje std::out_of_range izuzetak.
        const auto student_name = students.at(non_existing_key);

        std::cout << "Student sa indeksom " << non_existing_key
                  << " se zove \"" << student_name << "\"" << std::endl;
    }
    catch (std::out_of_range &ex)
    {
        std::cout << "Ispaljen je izuzetak! Poruka: " << ex.what() << std::endl;
    }
}

void insert_in_map(student_map &students, const student_type &new_student, const student_type &new_student_with_same_key)
{
    // Unosesenje novog para (kljuc, vrednost)
    // Vremenska slozenost: Logaritamska
    std::string state_of_input;

    // Povratna vrednost je par (iterator, bool).
    // Ukoliko je unos uspesan, iterator "pokazuje" na uneti par u recniku, a bool vrednost je tacna.
    // Ukoliko unos nije uspesan, iterator "pokazuje" na postojeci par u recniku, a bool vrednost je netacna.
    {
        const auto input = students.insert(new_student);
        const auto iter = input.first; // uzimamo prvi element uredjenog para
        const auto successfull = input.second;
        if (successfull)
        {
            state_of_input = "\nStudent je uspesno dodat.";
        }
        else
        {
            state_of_input = "\nStudent nije uspesno dodat.";
        }
        std::cout
            << state_of_input << " Recnik sadrzi: ("
            << iter->first << ", " << iter->second << ")" << std::endl;
    }

    // Primer za unos koji ne uspeva.
    {
        // Mozemo koristiti i otpakivanje koje je dodato u standardu c++17,
        // odnosno mozemo rezultat sa desne strane otpakovati u zasebne promenljive.
        const auto [iter, successfull] = students.insert(new_student_with_same_key);

        if (successfull)
        {
            state_of_input = "Student je uspesno dodat.";
        }
        else
        {
            state_of_input = "Student nije uspesno dodat.";
        }
        std::cout
            << state_of_input << " Recnik sadrzi: ("
            << iter->first << ", " << iter->second << ")" << std::endl;
    }
}

void emplace_in_map(student_map &students, unsigned &non_existing_key)
{
    // Element za unos mozemo konstruisati i u mestu.
    std::string state_of_insert;
    const auto [iter, successfull] = students.emplace(++non_existing_key, "Nikola");
    if (successfull)
    {
        state_of_insert = "\nStudent je uspesno dodat.";
    }
    else
    {
        state_of_insert = "\nStudent nije uspesno dodat.";
    }
    std::cout
        << state_of_insert << " Recnik sadrzi: ("
        << iter->first << ", " << iter->second << ")" << std::endl;
}

void insert_or_assign_in_map(student_map &students, const student_type &new_student_with_same_key)
{
    // Ako zelimo da novu vrednost upisemo preko stare ako postoji
    // mozemo koristiti `insert_or_assign`.
    std::string state_of_insert;
    std::cout << "\nDodajemo ili azuriramo studenta sa kljucem: " << new_student_with_same_key.first << std::endl;
    const auto [iter, successfull] = students.insert_or_assign(
        new_student_with_same_key.first,
        new_student_with_same_key.second);
    if (successfull)
    {
        state_of_insert = "Student je uspesno dodat.";
    }
    else
    {
        state_of_insert = "Student je azuriran na ime " + new_student_with_same_key.second + ".";
    }
    std::cout
        << state_of_insert << " Recnik sadrzi: ("
        << iter->first << ", " << iter->second << ")" << std::endl;
}

/// Tip std::map<Key, T, ...> predstavlja kolekciju parova (kljuc, vrednost)
/// pri cemu su kljucevi jedinstveni, a kolekcija je uredjena po parovima.
void map_showcase()
{
    auto students = init_map();
    print_map(students);

    unsigned existing_key = 20110145u;
    unsigned non_existing_key = 20000001u;

    find_in_map_1(students, existing_key, non_existing_key);
    print_map(students);
    find_in_map_2(students, existing_key, non_existing_key);
    print_map(students);

    // Konstruisemo par koji zelimo da dodamo.
    const std::pair<unsigned, std::string> new_student(non_existing_key, "Mihajlo");
    const std::pair<unsigned, std::string> new_student_with_same_key(non_existing_key, "Jelena");
    insert_in_map(students, new_student, new_student_with_same_key);
    print_map(students);

    emplace_in_map(students, non_existing_key);
    print_map(students);

    insert_or_assign_in_map(students, new_student_with_same_key);
    print_map(students);
}

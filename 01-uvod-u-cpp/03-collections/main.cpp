#include <iostream>
#include <string>

void show_help_and_quit();
void vector_showcase();
void set_showcase();
void map_showcase();
void forward_list_showcase();
void list_showcase();
void deque_showcase();

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        show_help_and_quit();
    }

    const std::string option(argv[1]);

    if (option == "v")
        vector_showcase();
    else if (option == "m")
        map_showcase();
    else if (option == "s")
        set_showcase();
    else if (option == "fl")
        forward_list_showcase();
    else if (option == "l")
        list_showcase();
    else if (option == "d")
        deque_showcase();
    else
        show_help_and_quit();

    return 0;
}

void show_help_and_quit()
{
    std::cerr << "Program se poziva naredbom: \"./main opcija\"" << std::endl
              << std::endl
              << "Opcija mora biti jedna od: " << std::endl
              << "\tv   = Demonstracija rada kolekcije std::vector<T, ...>" << std::endl
              << "\ts   = Demonstracija rada kolekcije std::set<T, ...>" << std::endl
              << "\tm   = Demonstracija rada kolekcije std::map<Key, T, ...>" << std::endl
              << "\tfl  = Demonstracija rada kolekcije std::forward_list<T, ...>" << std::endl
              << "\tl   = Demonstracija rada kolekcije std::list<T, ...>" << std::endl
              << "\td   = Demonstracija rada kolekcije std::deque<T, ...>" << std::endl;
    exit(EXIT_FAILURE);
}

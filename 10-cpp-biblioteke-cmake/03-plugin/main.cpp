#include "polygon.hpp"
#include <iostream>
#include <dlfcn.h>

int main()
{
    using std::cerr;
    using std::cout;
    using std::endl;

    // Ucitavamo plugin biblioteku
    void *matf_library_handle = dlopen("libmatf.so", RTLD_LAZY);
    if (!matf_library_handle)
    {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // Resetujemo greske
    dlerror();

    // Ucitavamo simbol
    create_t *create_triangle = reinterpret_cast<create_t *>( dlsym(matf_library_handle, "create") );
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        cerr << "Cannot load symbol create: " << dlsym_error << endl;
        return 1;
    }

    destroy_t *destroy_triangle = reinterpret_cast<destroy_t *>( dlsym(matf_library_handle, "destroy") );
    dlsym_error = dlerror();
    if (dlsym_error)
    {
        cerr << "Cannot load symbol destroy: " << dlsym_error << endl;
        return 1;
    }

    // Kreiramo instancu klase
    polygon *poly = create_triangle();

    poly->set_side_length(12);
    cout << "Povrsina trougla je: " << poly->area() << endl;

    // Ucistavamo instancu klase
    destroy_triangle(poly);

    // Zatvaramo biblioteku
    dlclose(matf_library_handle);

    return 0;
}
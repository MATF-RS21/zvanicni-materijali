#include <iostream>
#include <string>

struct point
{
    point(double x = .0, double y = .0)
    {
        m_x = x;
        m_y = y;
    }

    std::string toString()
    {
        return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
    }

    double m_x;
    double m_y;
};

int main()
{
    // Objekat strukture point na stek memoriji
    point p1(2.0, 5.0);
    point p2 = point(1.0, -3.6);

    std::cout << "Objekti na stek memoriji:" << std::endl
        << "p1: " << p1.toString() << std::endl
        << "p2: " << p2.toString() << std::endl;

    // Objekat strukture point na hip memoriji
    point *p3 = new point(3.14, 0);

    std::cout << "Objekat na hip memoriji:" << std::endl
        << "p3: " << (*p3).toString() << std::endl
        << "p3: " << p3->toString() << std::endl;

    // Niz objekata na stek memoriji
    point arr1[] = { {2.0, 5.0}, {1.0, -3.6}, {3.14, 0} };
    std::cout << "Niz objekata na stek memoriji:" << std::endl;
    for (point & p : arr1) {
        std::cout << p.toString() << " ";
    }
    std::cout << std::endl;

    // Niz objekata na hip memoriji
    size_t numberOfPoints = 3;
    point *arr2 = new point[numberOfPoints];
    std::cout << "Niz objekata na hip memoriji:" << std::endl;
    for (size_t i = 0; i < numberOfPoints; ++i) {
        std::cout << arr2[i].toString() << " ";
    }
    std::cout << std::endl;

    // Objekti koji se nalaze na stek memoriji ce biti automatski uklonjeni na kraju dosega
    // u obrnutom redosledu u odnosu na redosled u kojem su kreirani.
    // Objekte koji se nalaze na hip memoriji OBAVEZNO moramo sami ukloniti,
    // jer inace dolazi do curenja memorije.

    // Brisanje jednog objekta na hip memoriji
    delete p3;

    // Sada vise ne mozemo da pristupimo objektu,
    // ali to ne znaci da pokazivac ne sadrzi nekakvu adresu
    if (p3) {
        std::cout << "Nakon brisanja p3, pokazivac NIJE nullptr: " << p3 << std::endl;
        // Pa moramo rucno da ga "invalidiramo"
        p3 = nullptr;
    }
    else {
        std::cout << "Nakon brisanja p3, pokazivac JESTE nullptr " << p3 << std::endl;
    }

    // Brisanje niza objekata na hip memoriji
    delete[] arr2;

    if (arr2) {
        std::cout << "Nakon brisanja arr2, pokazivac NIJE nullptr: " << arr2 << std::endl;
        // Pa moramo rucno da ga "invalidiramo"
        arr2 = nullptr;
    }
    else {
        std::cout << "Nakon brisanja arr2, pokazivac JESTE nullptr " << arr2 << std::endl;
    }
}
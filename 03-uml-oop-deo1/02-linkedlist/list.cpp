#include "list.hpp"

namespace matf
{
    list::~list()
    {
        while (m_start)
        {
            pop_front();
        }
    }

    list::list(const list &other)
    {
        for (auto i = 0u; i < other.m_size; ++i)
        {
            push_back(other[i]);
        }
    }

    // Ideja ove funkcije je da omoguci sledece (pseudokod):
    // list xs([1, 2, 3, 4, 5])
    // Odnosno, da se privremena lista [1, 2, 3, 4, 5] ne kopira pa potom obrise, 
    // vec da se direktno preuzme pri konstrukciji nase liste.
    list::list(list &&other) noexcept
        // Pozivom std::move "krademo" implementaciju od liste koja se prosledjuje.
        : m_start(std::move(other.m_start))
        // Za primitivne tipove, kao sto je size_t, nema potrebe zvati std::move.
        , m_size(other.m_size)
    {
        // Posto smo "ukrali" unique_ptr iz druge liste (cime se on postavlja na nullptr),
        // onda je neophodno da rucno postavimo da je duzina druge liste 0,
        // kako bi ostali kod radio korektno (poput metoda size()).
        other.m_size = 0;
    }

    // Alternativna implementacija:
    //   - Pozivamo podrazumevani konstruktor koji ce inicijalizovati podatke ove liste:
    //     m_start = nullptr, m_size = 0u (pogledati definicije ovih atributa u list.hpp)
    //   - A zatim vrsimo razmenu podataka izmedju privremene liste i ove liste
    // list::list(list &&other) noexcept
    //     : list()
    // {
    //     std::swap(m_start, other.m_start);
    //     std::swap(m_size, other.m_size);
    // }

    list &list::operator=(const list &other)
    {
        // Ovde demonstriramo tzv. "Copy and Swap" idiom.
        // Da bi operator dodele bio bezbedan prilikom pojave izuzetaka,
        // obavezno je implementirati ga na ovaj nacin:

        // 1. Pravi se privremena kopija objekta (poziva se konstruktor kopije)
        auto temp(other);
        // 2. Zamene se sve clanske promenljive u *this i privremenoj kopiji
        std::swap(temp.m_start, m_start);
        std::swap(temp.m_size, m_size);
        // Operator dodele uvek vraca referencu na tekuci objekat,
        // kako bismo mogli ulancavati ovaj operator.
        return *this;
    }

    list &list::operator=(list &&other) noexcept
    {
        // Ovde demonstriramo tzv. "Move and Swap" idiom.
        // Ideja je ista kao u "Copy and Swap" idiomu:

        // 1. Poziva se konstruktor sa semantikom pomeranja
        auto temp(std::move(other));
        // 2. Zamene se sve clanske promenljive u *this i privremenoj kopiji
        std::swap(temp.m_start, m_start);
        std::swap(temp.m_size, m_size);
        // Operator dodele uvek vraca referencu na tekuci objekat,
        // kako bismo mogli ulancavati ovaj operator.
        return *this;
    }

    void list::push_front(int value)
    {
        auto new_element = std::make_unique<element>(value, std::move(m_start));
        m_start = std::move(new_element);
        ++m_size;
    }

    void list::push_back(int value)
    {
        auto new_element = std::make_unique<element>(value);

        if (!m_start)
        {
            m_start = std::move(new_element);
        }
        else
        {
            auto e = m_start.get();

            while (e->next)
            {
                e = e->next.get();
            }

            e->next = std::move(new_element);
        }

        ++m_size;
    }

    void list::pop_front()
    {
        auto old_start = std::move(m_start);
        m_start = std::move(old_start->next);
        m_size--;
    }

    int &list::operator[](const size_t index) const
    {
        return at(index)->value;
    }

    int &list::operator[](const size_t index)
    {
        return at(index)->value;
    }

    size_t list::size() const
    {
        return m_size;
    }

    list::element::element(const int value, std::unique_ptr<element> &&next)
        : value(value), next(std::move(next))
    {
    }

    list::element *list::at(const size_t index) const
    {
        if (!m_start)
        {
            return nullptr;
        }

        auto e = m_start.get();

        for (auto i = 0u; i < index; ++i)
        {
            e = e->next.get();

            if (!e)
            {
                return nullptr;
            }
        }

        return e;
    }
} // namespace matf

std::ostream &operator<<(std::ostream &out, const matf::list &l)
{
    for (auto i = 0u; i < l.size(); ++i)
    {
        out << l[i] << " ";
    }
    return out;
}

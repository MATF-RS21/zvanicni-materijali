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

    list::list(list &&other) noexcept
        : m_start(std::move(other.m_start))
        , m_size(other.m_size)
    {
        other.m_size = 0;
    }

    list &list::operator=(const list &other)
    {
        auto temp(other);
        std::swap(temp.m_start, m_start);
        std::swap(temp.m_size, m_size);
        return *this;
    }

    list &list::operator=(list &&other) noexcept
    {
        m_start = std::move(other.m_start);
        m_size = other.m_size;
        other.m_size = 0;
        return *this;
    }

    void list::push_front(const fraction &value)
    {
        auto new_element = std::make_unique<element>(value, std::move(m_start));
        m_start = std::move(new_element);
        ++m_size;
    }

    void list::push_back(const fraction &value)
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

    const fraction &list::operator[](const size_t index) const
    {
        return at(index)->value;
    }

    fraction &list::operator[](const size_t index)
    {
        return at(index)->value;
    }

    size_t list::size() const
    {
        return m_size;
    }

    list::element::element(const fraction &value, std::unique_ptr<element> &&next)
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

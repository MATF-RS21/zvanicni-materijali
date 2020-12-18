#ifndef MATF_LIST_HPP
#define MATF_LIST_HPP

#include <memory>
#include <iostream>

#include "fraction.hpp"

namespace matf
{
    class list
    {
    public:
        list() = default;
        ~list();

        list(const list &other);
        list(list &&other) noexcept;
        list &operator=(const list &other);
        list &operator=(list &&other) noexcept;

        void push_front(const fraction &value);
        void push_back(const fraction &value);

        void pop_front();

        size_t size() const;

        const fraction &operator[](const size_t index) const;
        fraction &operator[](const size_t index);

    private:
        struct element
        {
            explicit element(const fraction &value = 0.f, std::unique_ptr<element> &&next = nullptr);

            fraction value;
            std::unique_ptr<element> next;
        };

        element *at(const size_t index) const;

        std::unique_ptr<element> m_start = nullptr;
        size_t m_size = 0;
    };

} // namespace matf

std::ostream &operator<<(std::ostream &out, const matf::list &l);

#endif /* !MATF_LIST_HPP */

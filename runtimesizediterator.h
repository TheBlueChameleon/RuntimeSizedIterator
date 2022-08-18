#ifndef RUNTIMESIZEDITERATOR_H
#define RUNTIMESIZEDITERATOR_H

#include <iterator>

class RuntimeSizedIterator
{
    protected:
        using base_type     = void** ;
        using traits_type   = std::iterator_traits<base_type>;

    public:
        using iterator_type     = base_type;
        using iterator_category = traits_type::iterator_concept;
        using value_type        = traits_type::value_type;
        using element_type      = traits_type::value_type;
        using difference_type   = traits_type::difference_type;
        using reference         = traits_type::reference;
        using pointer           = traits_type::pointer;

    protected:
        base_type   current;
        size_t      stride;

    public:
        RuntimeSizedIterator();

        pointer     operator->() const;
        reference   operator*() const;
        reference   operator[](int) const;

        RuntimeSizedIterator& operator++();
        RuntimeSizedIterator operator++(int);
        RuntimeSizedIterator& operator--();
        RuntimeSizedIterator operator--(int);
        RuntimeSizedIterator& operator+=(int);
        RuntimeSizedIterator& operator-=(int);

        friend auto operator<=>(RuntimeSizedIterator, RuntimeSizedIterator) = default;
        friend difference_type operator-(RuntimeSizedIterator, RuntimeSizedIterator);
        friend RuntimeSizedIterator operator+(RuntimeSizedIterator, int);
        friend RuntimeSizedIterator operator-(RuntimeSizedIterator, int);
        friend RuntimeSizedIterator operator+(int, RuntimeSizedIterator);
};

static_assert(1);
static_assert(std::input_iterator        <RuntimeSizedIterator>);
static_assert(std::forward_iterator      <RuntimeSizedIterator>);
static_assert(std::bidirectional_iterator<RuntimeSizedIterator>);
static_assert(std::random_access_iterator<RuntimeSizedIterator>);
static_assert(std::contiguous_iterator   <RuntimeSizedIterator>);

#endif // RUNTIMESIZEDITERATOR_H

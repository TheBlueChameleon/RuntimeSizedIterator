#include <cxxabi.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <span>
#include <typeinfo>
#include <vector>

#include "runtimesizediterator.h"

constexpr size_t N = 256;
constexpr size_t chunkSize = 16;

char* getFreeFormData()
{
    constexpr char offset = 64;

    auto freeFormData = new char[N];

    for (auto i = 0u; i < N; ++i)
    {
        freeFormData[i] = offset + (i % chunkSize);
    }

    return freeFormData;
}

std::string demangle(const char* name)
{
    int status = 0; // some arbitrary value to eliminate the compiler warning

    std::unique_ptr<char, void(*)(void*)> res
    {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

template<typename T>
std::string getTypeName(T t)
{
    auto& typeinfo = typeid(t);
    return demangle(typeinfo.name());
}

void showAndAlignTo(const std::string& str, const size_t tab = 20)
{
    std::cout << str << std::string(tab - str.size(), ' ');
}

void showSideBySide(const std::string& lhs, const std::string& rhs, const size_t tab = 80)
{
    showAndAlignTo(lhs, tab);
    std::cout << rhs << std::endl;
}

void compareInternalTypes()
{
    auto field = new void* [N];
    std::span span(field, field+N);
    delete[] field;

    decltype(span.begin()) iter;
    RuntimeSizedIterator    rsi;
    showAndAlignTo("full name:");
    showSideBySide(getTypeName(iter), getTypeName(rsi));

    decltype(iter)::iterator_type iterator_iterator_type;
    decltype(rsi) ::iterator_type      rsi_iterator_type;
    showAndAlignTo("iterator type:");
    showSideBySide(getTypeName(iterator_iterator_type), getTypeName(rsi_iterator_type));

    decltype(iter)::iterator_category iterator_iterator_category;
    decltype(rsi) ::iterator_category      rsi_iterator_category;
    showAndAlignTo("iterator category:");
    showSideBySide(getTypeName(iterator_iterator_category), getTypeName(rsi_iterator_category));

    decltype(iter)::value_type iterator_value_type;
    decltype(rsi) ::value_type      rsi_value_type;
    showAndAlignTo("value type:");
    showSideBySide(getTypeName(iterator_value_type), getTypeName(rsi_value_type));

    decltype(iter)::difference_type iterator_difference_type;
    decltype(rsi) ::difference_type      rsi_difference_type;
    showAndAlignTo("difference type:");
    showSideBySide(getTypeName(iterator_difference_type), getTypeName(rsi_difference_type));

    void* pc = nullptr;
    decltype(iter)::reference iterator_reference_type = pc;
    decltype(rsi) ::reference      rsi_reference_type = pc;
    showAndAlignTo("reference type:");
    showSideBySide(getTypeName(iterator_reference_type), getTypeName(rsi_reference_type));

    decltype(iter)::pointer iterator_pointer_type;
    decltype(rsi) ::pointer      rsi_pointer_type;
    showAndAlignTo("pointer type:");
    showSideBySide(getTypeName(iterator_pointer_type), getTypeName(rsi_pointer_type));
}

int main()
{
    auto freeFormData = getFreeFormData();

    compareInternalTypes();

    RuntimeSizedIterator rsa, rsb;
    std::vector x(rsa, rsb);
    std::span   y(rsa, rsb);

    delete[] freeFormData;
    return 0;
}

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <ostream>
#include <array>


template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, std::array<T, N> const& a)
{
    out << "[ ";

    for(auto x : a)
    {
        out << x << " ";
    }

    out << "]";
    return out;
}




#endif
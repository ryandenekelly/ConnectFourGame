#ifndef DERIVED_CLASS_B_HPP
#define DERIVED_CLASS_B_HPP

#include <string>
#include "BaseClass.hpp"

class DerivedClassB : public BaseClass
{
    public:
        virtual std::string methodTwo();

};

#endif
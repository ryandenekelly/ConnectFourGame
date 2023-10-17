#ifndef DERIVED_CLASS_A_HPP
#define DERIVED_CLASS_A_HPP

#include <string>
#include "BaseClass.hpp"

class DerivedClassA : public BaseClass
{
    public:
        virtual std::string methodTwo();

};

#endif
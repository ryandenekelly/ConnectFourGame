#ifndef DERIVED_CLASS_AB_HPP
#define DERIVED_CLASS_AB_HPP

#include <string>
#include "BaseClass.hpp"
#include "DerivedClassA.hpp"

class DerivedClassAB : public DerivedClassA
{
    public:
        virtual std::string methodTwo();

};

#endif
#include <iostream>
#include "BaseClass.hpp"
#include "DerivedClassA.hpp"
#include "DerivedClassAB.hpp"
#include "DerivedClassB.hpp"


int main()
{
    BaseClass base = BaseClass();
    DerivedClassA derivedA = DerivedClassA();
    DerivedClassAB derivedAB = DerivedClassAB();
    DerivedClassB derivedB = DerivedClassB();

    std::cout << base.methodOne() << " : " << base.methodTwo() << "\n";
    std::cout << derivedA.methodOne() << " : " << derivedA.methodTwo() << "\n";
    std::cout << derivedAB.methodOne() << " : " << derivedAB.methodTwo() << "\n";
    std::cout << derivedB.methodOne() << " : " << derivedB.methodTwo() << "\n";

    BaseClass *base_ptr;
    base_ptr = &derivedA;
    std::cout << base_ptr->methodTwo() << "\n";

    base_ptr = &derivedB;
    std::cout << base_ptr->methodTwo() << "\n";

    return 0;
}
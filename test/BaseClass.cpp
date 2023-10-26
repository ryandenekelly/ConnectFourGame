#include "BaseClass.hpp"

BaseClass::BaseClass()
{
    attributeA = 0;
    attributeB = "Hello";
}

std::string BaseClass::methodOne()
{
    return "Method One!";
}

std::string BaseClass::methodTwo()
{
    return "BaseClass";
}
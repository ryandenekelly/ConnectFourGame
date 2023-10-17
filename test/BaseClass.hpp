#ifndef BASE_CLASS_HPP
#define BASE_CLASS_HPP

#include <string>

class BaseClass
{
    public:
        BaseClass();
        std::string methodOne();
        virtual std::string methodTwo();
    
    private:
        int attributeA;
        std::string attributeB;
};

#endif
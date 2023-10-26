#ifndef COMPONENT_CLASS_HPP
#define COMPONENT_CLASS_HPP

#include "SampleObject.hpp"
class ComponentClass
{

    private:
        int m_id;
        SampleObject m_object;
    public:
        ComponentClass(SampleObject object);
        ~ComponentClass();
        int getID();
        SampleObject getObject();
};

#endif
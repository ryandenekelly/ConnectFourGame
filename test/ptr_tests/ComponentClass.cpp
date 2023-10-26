#include "ComponentClass.hpp"

ComponentClass::ComponentClass(SampleObject object)
{
    m_id = 0;
    m_object = object;
}

ComponentClass::~ComponentClass()
{

}

int ComponentClass::getID()
{
    return m_id;
}

SampleObject ComponentClass::getObject()
{
    return m_object;
}




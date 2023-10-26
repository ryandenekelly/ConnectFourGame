#include "SampleObject.hpp"

SampleObject::SampleObject()
{
    m_number = 0;
    m_word = "";
}

SampleObject::SampleObject(int number, const std::string& word)
{
    m_number = number;
    m_word = word;
}

SampleObject::~SampleObject()
{
}

int SampleObject::getNumber()
{
    return m_number;
}
void SampleObject::setNumber(int number)
{
    m_number = number;
}

std::string SampleObject::getWord()
{
    return m_word;
}
void SampleObject::setWord(std::string word)
{
    m_word = word;
}


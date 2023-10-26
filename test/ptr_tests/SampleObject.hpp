#ifndef SAMPLE_OBJECT_HPP
#define SAMPLE_OBJECT_HPP

#include <string>

class SampleObject
{
    private:
        int m_number;
        std::string m_word;
    public:
        SampleObject();
        SampleObject(int number, const std::string& word);
        ~SampleObject();
        int getNumber();
        void setNumber(int number);
        std::string getWord();
        void setWord(std::string word);

        friend std::ostream& operator<<(std::ostream& out, const SampleObject& object)
        {
            out << std::to_string(object.m_number)  + " - " + object.m_word;
            return out;
        }



};

#endif
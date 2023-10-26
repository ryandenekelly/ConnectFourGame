#include "ComponentClass.hpp"
#include "SampleObject.hpp"

#include <string>
#include <iostream>
#include <memory>

int main()
{
    SampleObject objectOne = SampleObject();
    objectOne.setNumber(100);
    objectOne.setWord("Hello");

    SampleObject objectTwo = SampleObject();
    objectTwo.setNumber(200);
    objectTwo.setWord("World");

    SampleObject objectThree = SampleObject();
    objectThree.setNumber(300);
    objectThree.setWord("Hey!");

    std::cout << objectOne << "\n";
    std::cout << objectTwo << "\n";
    std::cout << objectThree << "\n";

    SampleObject * ptr = SampleObject(400, "Hello World!");
    std::cout << *objectPtr << "\n";

    std::shared_ptr<SampleObject> sharedPtrOne(&objectOne);
    std::shared_ptr<SampleObject> sharedPtrTwo(&objectOne);

    std::cout << *sharedPtrOne << "\n";
    std::cout << *sharedPtrTwo << "\n";

    return 0;
}
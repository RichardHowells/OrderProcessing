// DevelopToyVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "toy_vector.h"

class Person {
    std::string name;
public:
    Person(const std::string& name) : name{ name } {}
};

int main()
{
    std::cout << "Hello World!\n";

    toy_vector<int> v_int;

    v_int.push_back(99);
    std::cout << v_int.back() << "\n";

    toy_vector<std::string> v_string;

    v_string.push_back("Hello world");

    std::cout << v_string.back() << "\n";

    // Will not compile.  toy_vector's contained type must have a default constructor
    //toy_vector<Person> v_person;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

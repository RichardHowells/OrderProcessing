// DevelopToyVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

// Very crude leak checker.  Does NOT cover all cases
// On entry to a block of code where new and delete should balance, set the allocationCount to 0
// AFTER the block exits, check allocationCount.  If new/delete *do* balance, it should be zero
unsigned long allocationCount{ 0 };

void* operator new(std::size_t amount)
{
    auto p = ::malloc(amount);

    ++allocationCount;
    return p;
}
void operator delete(void* p)
{
    --allocationCount;
    ::free(p);
}

int main()
{
    {
        std::cout << "Hello World!\n";

        // Place your code to test toy_vector here.  Then you will get the limited leak checking

    }

    if (allocationCount == 0)
        std::cout << "No obvious leaks\n";
    else
        std::cout << "Leaked " << allocationCount << " heap object(s)\n";

    std::cout << "Program completed successfully\n";

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

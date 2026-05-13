// ConvertAndCompare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

class Experiment
{
	std::string content;

public:
	Experiment(std::string content) : content{ content } {}

	void display()
	{
		std::cout << "The content is " << content << "\n";
	}

	int to_int() {
		return stoi(content);
	}

};

int main()
{
	std::cout << "Hello World!\n";

	Experiment a{ "99" };
	a.display();

	std::cout << a.to_int() << "\n";


	Experiment b{ "99" };


	//bool z = a == b;  //will not compile
	//bool y = a < b;  //will not compile
	//bool x = a > b;  //will not compile

}


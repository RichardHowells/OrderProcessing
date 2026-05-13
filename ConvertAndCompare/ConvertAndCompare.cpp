// ConvertAndCompare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Experiment
{
	std::string content;

public:
	Experiment(std::string content) : content{ content } {}

	void display()
	{
		std::cout << "The content is " << content << "\n";
	}

	const std::string& getContent() const
	{
		return content;
	}

	int to_int() {
		return stoi(content);
	}

	operator int() {
		return stoi(content);
	}

};

inline bool operator <(const Experiment& left, const Experiment& right) {
	return left.getContent() < right.getContent();
}

inline bool operator ==(const Experiment& left, const Experiment& right) {
	return left.getContent() < right.getContent();
}

inline bool operator !=(const Experiment& left, const Experiment& right) {
	return !(left == right);
}

inline bool operator >=(const Experiment& left, const Experiment& right) {
	return !(left < right);
}

inline bool operator <=(const Experiment& left, const Experiment& right) {
	return left < right || left == right;
}

inline bool operator >(const Experiment& left, const Experiment& right) {
	return !(left < right) && !(left == right);
}

int main()
{
	std::cout << "Hello World!\n";

	Experiment a{ "99" };
	a.display();

	std::cout << a.to_int() << "\n";

	std::cout << a << "\n";

	Experiment b{ "99" };


	bool z = a == b;  //will not compile
	bool y = a < b;  //will not compile
	bool x = a > b;  //will not compile

	std::vector<Experiment> experiments{ Experiment{"300"}, Experiment{"2000"}, Experiment{"5"}, Experiment{"40"},  Experiment{"10000"} };

	std::cout << "Sorted experiments\n";
	std::sort(experiments.begin(), experiments.end());
	for (auto e : experiments)
		std::cout << e << "\n";


	// Surprising - if x < y == true then a normal human expects x > y to be false
	std::cout << "Is 10 < 2? " << (Experiment{ "10" } < Experiment{ "2" }) << "\n";
	std::cout << "Is 10 > 2? " << (Experiment{ "10" } > Experiment{ "2" }) << "\n";

	// Guideline - if you implement any comparison you should do them all.
	// The standard approach (pre C++20) is to implement > and ==
	// Then the rest are one line each.  See above




}


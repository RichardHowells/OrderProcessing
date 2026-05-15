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
	explicit Experiment(int i) : content{ std::to_string(i) } {}

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

	friend bool operator <(const Experiment& left, const Experiment& right) {
		return left.content < right.content;
	}

	//friend inline bool operator ==(const Experiment& left, const Experiment& right) = default;
	//friend std::strong_ordering operator <=>(const Experiment& left, const Experiment& right) = default;
	//friend inline std::strong_ordering operator <=>(const Experiment& left, const Experiment& right) {
	//	if (left.getContent() < right.getContent())
	//		return std::strong_ordering::less;
	//	else if (left.getContent() > right.getContent())
	//		return std::strong_ordering::greater;
	//	else
	//		return std::strong_ordering::equal;
	//}



};
//
//inline bool operator <(const Experiment& left, const Experiment& right) {
//	return left.getContent() < right.getContent();
//}
//
//inline bool operator ==(const Experiment& left, const Experiment& right) {
//	return left.getContent() < right.getContent();
//}
// 
// Once we have op < and op == the others *should* be implemented
// using them...
//
//inline bool operator !=(const Experiment& left, const Experiment& right) {
//	return !(left == right);
//}
//
//inline bool operator >=(const Experiment& left, const Experiment& right) {
//	return !(left < right);
//}
//
//inline bool operator <=(const Experiment& left, const Experiment& right) {
//  NOTE - the swapped left/right
//	return !(right < left);
//}
//
//inline bool operator >(const Experiment& left, const Experiment& right) {
//  NOTE - the swapped left/right
//	return right < left;
//}
//

void f(Experiment e) {}

void g(int i) {}
int main()
{
	std::cout << "Hello World!\n";

	f(Experiment{ 99 });

	Experiment a{ 99 };
	a.display();

	g(a);


	Experiment b{ 99 };

	bool z = a == b;
	bool y = a != b;
	bool x = a < b;
	bool w = a <= b;
	bool v = a >= b;
	bool u = a > b;


	std::cout << a.to_int() << "\n";

	//std::cout << a << "\n";


	std::vector<Experiment> experiments{ Experiment{300}, Experiment{2000}, Experiment{5}, Experiment{40},  Experiment{10000} };

	std::cout << "Sorted experiments\n";
	std::sort(experiments.begin(), experiments.end());
	for (auto e : experiments)
		e.display();


	// Surprising - if x < y == true then a normal human expects x > y to be false
	std::cout << "Is 10 < 2? " << (Experiment{ 10 } < Experiment{ 2 }) << "\n";
	std::cout << "Is 10 > 2? " << (Experiment{ 10 } > Experiment{ 2 }) << "\n";

	// Guideline - if you implement any comparison you should do them all.
	// The standard approach (pre C++20) is to implement < and ==
	// Then the rest are one line each.  See the comments above




}


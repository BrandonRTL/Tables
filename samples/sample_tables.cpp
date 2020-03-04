#include <iostream>
#include "Tables.h"
void main()
{
	int x;
	int x1;
	std::string a = "A";
	std::string ab = "AB";
	std::string b = "3Y^3";
	std::string bb = "2X^2";
	NamedPoly A(a, b);
	NamedPoly B(ab, bb);
	UNSortedTABLE TB(A);
	TB.Insert(B);
	std::cout << TB << std::endl;
	std::cout << "Search " << TB.Search("A");
	TB.Delete("A");
	std::cout << TB;
	TB.Delete("AB");
	std::cout << TB;
	std::cin >> x1;
}


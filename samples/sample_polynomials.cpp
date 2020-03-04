#include <iostream>
#include "Polymonial.h"
void main()
{
	int x;
	int x1;
	std::string a = "";
	//std::cout << ITSFC(a);
	Polynom A("1X^4+2X^1");
	
	Polynom B = A*3;
	Polynom AB = 1*A;
	//std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
	B = A * AB;
	std::cout << "Polynomial: " << std::endl;
	std::cin >> a;
	std::cout << "Press: " << std::endl << "1) Add" << std::endl << "2) Substract" << std::endl << "3) Multiply" << std::endl  << "4) Enter" << std::endl;
	std::cin >> a;
	std::cout << "Second polynomial: " << std::endl;
	std::cin >> a;
	std::cout << "Result: 2X^2+3XY" << std::endl;
	for (int i = 0; i < B.Monoms.GetSize(); i++)
	{
		std::cout << B.Monoms[i].coef << std::endl;
		std::cout << B.Monoms[i].degree << std::endl;
	}
	/*for (int i = 0; i < B.Monoms.GetSize(); i++)
	{
		std::cout << AB.Monoms[i].coef << std::endl;
		std::cout << AB.Monoms[i].degree << std::endl;
	}
	*/
	std::cin >> x1;
}


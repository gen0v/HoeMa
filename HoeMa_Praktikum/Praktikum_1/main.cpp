#include <iostream>
#include <vector>
#include "CMyVektor.h"

/*
double function(CMyVektor a) {
	a[1] = 33;
	return a[1] + 50; 
}
*/
double function_f(CMyVektor x) {
	return sin(x[0] + pow(x[1], 2)) + pow(x[1], 3) - 6 * pow(x[1], 2) + 9 * x[1];
}
double(*f)(CMyVektor a) = function_f;

double function_g(CMyVektor x) {
	if (x.getDimension() == 3) {
		return (-1 * (2 * pow(x[0],2) - 2 * x[0] * x[1] + pow(x[1], 2) + pow(x[2], 2) - 2 * x[0] - 4 * x[2]));
	}
	else std::cout << " -- WRONG DIMENSION --\n";
}
double(*g)(CMyVektor a) = function_g;
int main()
{
	CMyVektor x;
	x.createVektorWithDim(2);
	x[0] = 3;
	x[1] = 2;
	CMyVektor y;
	y.createVektorWithDim(3);

	//x.maximaze(x, function_f);
	y.maximaze(y, function_g, 0.1);

	system("PAUSE");
	return 0;
}
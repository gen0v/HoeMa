#include <iostream>
#include "CMyMatrix.h"
#include "CMyVektor.h"

double test_1(double a, double b, double c) {
	return a * b * std::exp(c);
}
double test_2(double a, double b, double c) {
	return a * b * c;
}
double test_3(double a) {
	return a;
}

CMyVektor function_f(CMyVektor x) {
	CMyVektor temp;
	temp.createVektorWithDim(x.getSize());
	temp[0] = pow(x(0), 3)*pow(x(1), 3) - 2 * x(1);
	temp[1] = x(0) - 2 ;
	return temp;
}
CMyVektor(*f)(CMyVektor a) = function_f;

CMyVektor function_test(CMyVektor x) {
	CMyVektor temp;
	temp.createVektorWithDim(3);
	temp[0] = x(0) * x(1) * std::exp(x(2));
	//temp[0] = test_1(x(0), x(1), x(2));
	temp[1] = x(1) * x(2) * x(3);
	//temp[1] = test_2(x(1), x(2), x(3));
	temp[2] = x(3);
	//temp[2] = test_3(x(3));

	return temp;
}
CMyVektor(*t)(CMyVektor a) = function_test;

int main() {


	CMyVektor vec,res;
	vec.createVektorWithDim(2);
	vec[0] = 1;
	vec[1] = 1;
	
	//CMyMatrix jac;
	//jac.createMatrixWithDim(2, 2);
	//std::cout << "TEST JACOBI MATRIX\n";
	//jac.jacobi(vec, function_f);
	//jac = jac.jacobi(vec, function_f);
	//jac.print();

	CMyVektor newton;;
	newton = CMyMatrix().newton(vec, function_f);
	newton.printAll();





	system("PAUSE");
	return 0;
}
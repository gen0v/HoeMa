#include "CMyMatrix.h"
#include <iostream>

double test_1(CMyVektor x) {
	return x(0) * x(1) * std::exp(x(2));
}
double test_2(CMyVektor x) {
	return x(1) * x(2) * x(3);
}
double test_3(CMyVektor x) {
	return x(3);
}
double f_1(CMyVektor x) {
	return pow(x(0),3)*pow(x(1),3) - 2 * x(1);
}
double f_2(CMyVektor x) {
	return x(0) - 2;
}
double(*test1)(CMyVektor a) = test_1;
double(*test2)(CMyVektor a) = test_2;
double(*test3)(CMyVektor a) = test_3;

double(*f1)(CMyVektor a) = f_1;
double(*f2)(CMyVektor a) = f_2;



CMyMatrix::CMyMatrix()
{
}

CMyMatrix::~CMyMatrix()
{
}
/*Create Matrix with Width and height*/
void CMyMatrix::createMatrixWithDim(int w, int h)
{
	this->height = h;
	this->width = w;
	matrix.resize(w*h,0);
}

double CMyMatrix::getComponent(int x, int y)
{
	//return x*height+y;
	return matrix[x + y * height];
}

void CMyMatrix::setComponent(int x, int y, double value)
{
	//matrix[x*height + y] = value;
	matrix[x + y * height] = value;
}

CMyMatrix CMyMatrix::invers()
{
	//it needs to be a 2x2 matrix
	//det matrix need to be != 0
	if(height == 2 && width == 2 && detNotZero()){
		CMyMatrix inv;
		double c = 1 / (this->getComponent(0, 0)*this->getComponent(1, 1) - this->getComponent(0, 1)*this->getComponent(1, 0));
		inv.createMatrixWithDim(2, 2);
		inv.setComponent(0, 0, this->getComponent(1, 1) * c);//d
		inv.setComponent(0, 1, -1 * this->getComponent(0, 1) * c);//b
		inv.setComponent(1, 0, -1 * this->getComponent(1, 0) * c);//c
		inv.setComponent(1, 1, this->getComponent(0, 0) * c);//a
		return inv;
	}
	else
	{
		std::cout << "FEHLER AUFGETRETEN BEI DER INVERSE !\n PROGRAMM WIRD BEENDET \n";
		system("PAUSE");
		exit(0);
	}

}

bool CMyMatrix::detNotZero()
{
	//works atm just for 2x2
	if (this->getComponent(0, 0)*this->getComponent(1, 1) - this->getComponent(0, 1)*this->getComponent(1, 0))return true;
	else return false;
}

void CMyMatrix::print()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			std::cout << this->getComponent(x,y) << " ";
		}
		std::cout << std::endl;
	}
}

void CMyMatrix::operator=(CMyMatrix copy)
{

	if (height == copy.height && width == copy.width) {

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			this->setComponent(x, y, copy.getComponent(x, y));
			//this->setComponent(x, y, 1);
			//copy.setComponent(x, y, 1);
		}
	}
	}
	else {
		std::cout << "CANNOT COPY | WRONG DIMENSIONS !\n";
	}
}

CMyMatrix CMyMatrix::jacobi(CMyVektor x, CMyVektor(*function)(CMyVektor x))
{
	double h = pow(10, -4);

	CMyVektor copy = x;
	CMyMatrix res;
	res.createMatrixWithDim(2, 2);


	copy = x.gradient(copy, f_1);
	for (int i = 0; i < res.height; i++) {
		res.setComponent(i, 0, copy(i));
	}
	copy = x;
	copy = x.gradient(copy, f_2);
	for (int i = 0; i < res.height; i++) {
		res.setComponent(i, 1, copy(i));
	}
	//res.print();
	/*
	copy = x.gradient(copy, test1);
	copy.printAll();

	copy = x;
	copy = x.gradient(copy, test2);
	copy.printAll();

	copy = x;
	copy = x.gradient(copy, test3);
	copy.printAll();
	*/



	return res;

}

CMyVektor CMyMatrix::newton(CMyVektor x, CMyVektor(*function)(CMyVektor x))
{
	int counter = 0;
	CMyVektor res = x;
	CMyMatrix test;
	test.createMatrixWithDim(2, 2);
	double h = pow(10, -5);

	CMyVektor dt, x2;

	while (counter < 50 && function(x).absolutValue() > h ) {


		x2 = (jacobi(x, function).invers() * (-1 * function(x))) + x;
		dt = (jacobi(x, function).invers() * function(x));
		dt = -1 * dt;


		std::cout << "-------Schritt " << counter << ":\n";
		std::cout << "\tx = ";
		x.printAll();


		std::cout << "\tf(x) = ";
		function(x).printAll();
		std::cout << std::endl;

		std::cout << "\tf'(x) = \n";
		jacobi(x, function).print();
		std::cout << std::endl;

		std::cout << "\t(f'(x)))^-1 = \n";
		jacobi(x, function).invers().print();
		std::cout << std::endl;

		std::cout << "\tdx = ";
		dt.printAll();

		std::cout << "\t||f(x)|| = "<< function(x).absolutValue()<<"\n";


		x = x2;
		counter++;
	}
	if (counter>50) {
		//counter
		std::cout << "ENDE WEGEN COUNTER > 50\n";
		std::cout << "\tx = ";
		x.printAll();
		std::cout << "\tf(x) = ";
		function(x).printAll();
		std::cout << "\t||f(x)|| = " << function(x).absolutValue() << "\n";

	}
	else {

		//lenght
		std::cout << "ENDE WEGEN ||f(x)|| > 1e-5 bei\n";
		std::cout << "\tx = ";
		x.printAll();
		std::cout << "\tf(x) = ";
		function(x).printAll();
		std::cout << "\t||f(x)|| = " << function(x).absolutValue() << "\n";
	}

	return CMyVektor();
}


CMyVektor operator*(CMyMatrix m, CMyVektor v)
{
	CMyVektor res;
	if (v.getDimension() == m.width) {
		res.createVektorWithDim(v.getDimension());
		for (int y = 0; y < m.height; y++)
		{
			for (int x = 0; x < m.width; x++)
			{
				res[y] =res(y) + m.getComponent(x, y) * v(x);
				//std::cout << res(y) << " res \n";
				//std::cout << "\n" <<res(y)<<" + "<< m.getComponent(x, y) << " * " << v(x);
			}
		}
	}
	return res;
}


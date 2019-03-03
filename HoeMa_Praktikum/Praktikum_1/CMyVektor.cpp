#include "CMyVektor.h"
#include <iostream>


CMyVektor::CMyVektor()
{
}


CMyVektor::~CMyVektor()
{
}

void CMyVektor::createVektorWithDim(int d)
{
	//doesnt delete the values just adds the dim
	for (int i = 0; i <= d; i++)
	{
		if (i > dimension) {
			this->values.push_back(0);
		}
		//values[i] = 0;
	}
	dimension = d;
}

void CMyVektor::printAll()
{
	bool started = false;
	std::cout << "( ";
	for (double d : values) {
		if (started == true) {
			std::cout << ";";
		}
		std::cout<< d;
		started = true;
	}
	std::cout << ")" << std::endl;
}

double& CMyVektor::operator[](int a)
{
	if (dimension < a) {
		std::cout << "ERROR OUT OF BOUNDS";
		return t;
	}
	//std::cout <<values[a] << std::endl;
	return values[a];
}

void CMyVektor::operator=(CMyVektor a)
{
	if (dimension < a.getDimension()) {
		std::cout << "ERROR OUT OF BOUNDS";
		return;
	}
	for (int i = 0; i < a.getSize(); i++)
	{
		this->values[i] = a[i];
	}
}

void CMyVektor::operator()(int a)
{
	if (dimension < a) {
		std::cout << "ERROR OUT OF BOUNDS";
		return;
	}
	std::cout <<values[a] << std::endl;
}

CMyVektor CMyVektor::gradient(CMyVektor x, double(*function)(CMyVektor x))
{
	CMyVektor res;
	res.createVektorWithDim(x.getDimension());
	double h = pow(10, -8);
	CMyVektor temp = x;
	int half = x.getDimension() / 2;

	for (int i = 0; i < temp.getDimension(); i++)
	{
		temp = x;
		temp.values[i] = temp.values[i] + h;


		//function(x);
		//function(temp);

		//(function(temp) - function(x)) / h;//hier error

		res[i] = (function(temp) - function(x)) / h;
	}
	return res;
	
}

double CMyVektor::maximaze(CMyVektor x, double(*function)(CMyVektor x), double lambda)
{
	int counter = 0;
	double l_test = lambda;
	CMyVektor x_neu = x;
	CMyVektor x_test;
	x_test.createVektorWithDim(x.getDimension());

	//fabs |x|
	while (fabs(gradient(x, function).absolutValue()) > pow(10, -5) && counter < 50) {
		std::cout << "Schritt "<< counter << ":" << std::endl;

		std::cout << "\t x = ";
		x.printAll();
		std::cout << std::endl;

		std::cout << "\t lambda = " << lambda;
		std::cout << std::endl;

		std::cout << "\t f(x) = " << function(x);
		std::cout << std::endl;

		std::cout << "\t grad f(x) = ";
		gradient(x, function).printAll();
		//std::cout << std::endl;

		std::cout << "\t ||grad f(x)|| = " << gradient(x, function).absolutValue();
		std::cout << std::endl;
		std::cout << std::endl;

		x_neu = x + lambda * gradient(x, function);

		std::cout << "\t x_neu = ";
		x_neu.printAll();
		std::cout << std::endl;

		std::cout << "\t f(x_neu) = " << function(x_neu);
		std::cout << std::endl;

		if (function(x_neu) > function(x)) {
			//Schrittweite verdoppeln
			l_test = 2 * lambda;
			x_test = x + (l_test *gradient(x, function));
			std::cout << "\t Test mit doppelter Schrittweite (lambda = "<< l_test << "):";
			std::cout << std::endl;
			
			std::cout << "\t x_test = ";
			x_test.printAll();

			std::cout << "\t f(x_test) = " << function(x_test);
			std::cout << std::endl;

			if (function(x_test) > function(x_neu)) {
				x = x_test;
				lambda = lambda * 2;
				std::cout << "\t Verdopple Schrittweite!" << std::endl;
			}
			else {
				x = x_neu;
				std::cout << "\t Behalte alte Schrittweite!" << std::endl;
			}
		}

		else if (function(x_neu) <= function(x)) {
			while (!(function(x_neu) > function(x))) {
				//Schrittweite halbieren

				std::cout << "\t halbiere Schrittweite (lambda = " << lambda / 2 << "):";
				lambda = lambda / 2;
				std::cout << std::endl;

				std::cout << "\t x_neu = ";
				x_neu = x + lambda * gradient(x, function);
				x_neu.printAll();
				std::cout << std::endl;

				std::cout << "\t f(x_neu) = " << function(x_neu);
				std::cout << std::endl;

			}
			x = x_neu;
		}

		counter++;
	}
	std::cout << std::endl;
	if (counter == 50) {
		std::cout << "Ende wegen Schrittanzahl = 50 bei " <<std::endl;

		std::cout << "\t x = ";
		x.printAll();

		std::cout << "\t lambda = " << lambda;
		std::cout << std::endl;

		std::cout << "\t f(x) = " << function(x);
		std::cout << std::endl;

		std::cout << "\t grad f(x) = ";
		gradient(x, function).printAll();
		//std::cout << std::endl;

		std::cout << "\t ||grad f(x)|| = " << gradient(x, function).absolutValue();
		std::cout << std::endl;
		std::cout << std::endl;
	}
	else {
		std::cout << "Ende wegen ||grad(f(x)||<1e-5 bei " << std::endl;

		std::cout << "\t x = ";
		x.printAll();

		std::cout << "\t lambda = " << lambda;
		std::cout << std::endl;

		std::cout << "\t f(x) = " << function(x);
		std::cout << std::endl;

		std::cout << "\t grad f(x) = ";
		gradient(x, function).printAll();
		//std::cout << std::endl;

		std::cout << "\t ||grad f(x)|| = " << gradient(x, function).absolutValue();
		std::cout << std::endl;
		std::cout << std::endl;
	}
	return gradient(x,function).absolutValue(); // ??
}

double CMyVektor::absolutValue(CMyVektor x)
{
	double res = 0;
	for (double d : x.values) {
		res = res + (d*d);
	}
	res = sqrt(res);
	return res;
}

double CMyVektor::absolutValue()
{
	double res = 0;
	for (double d : this->values) {
		res = res + (d*d);
	}
	res = sqrt(res);
	return res;
}

CMyVektor operator+(CMyVektor a, CMyVektor b) {
	if (a.getSize() != b.getSize()) {
		std::cout << "ERROR WRONG DIMENSIONS\n";
	}
	else {
		CMyVektor h;
		h.createVektorWithDim(a.getSize());
		for (int i = 0; i < a.getSize(); i++)
		{		
			h.values[i] = a[i] + b[i];
		}
		return h;
	}
}

CMyVektor operator-(CMyVektor a, CMyVektor b) {
	if (a.getSize() != b.getSize()) {
		std::cout << "ERROR WRONG DIMENSIONS\n";
	}
	else {
		CMyVektor h;
		h.createVektorWithDim(a.getSize());
		for (int i = 0; i < a.getSize(); i++)
		{
			h.values[i] = a[i] - b[i];
		}
		return h;
	}
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	CMyVektor e;
	e.createVektorWithDim(a.getSize());
	for (int i = 0; i < a.getSize(); i++)
	{
		e[i] = lambda * a[i];
	}
	return e;
}


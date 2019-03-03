#include "C_DGLSolver.h"
#include <iostream>

C_DGLSolver::C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x))
{
	//first-order
	fo = f_DGL_System;
}

C_DGLSolver::C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x))
{
	//higher-order
	higher_order = true;
	ho = f_DGL_nterOrdnung;

}

C_DGLSolver::~C_DGLSolver()
{
}

CMyVektor C_DGLSolver::ableitung(CMyVektor y, double x)
{
	CMyVektor solve;
	int dim = y.getDimension();

	if (this->higher_order == true) {
		solve.createVektorWithDim(dim);
		for (int i = 0; i < dim-1; i++)
		{
			solve[i] = y[i + 1];
		}
		solve[dim - 1] = ho(y, x);
	}
	else {
		solve =  fo(y, x);
	}



	return solve;
}

CMyVektor C_DGLSolver::euler(double xstart, double xend, double schrittanzahl, CMyVektor y_Start)
{
	double weite = (xend - xstart) / schrittanzahl;
	std::cout << "h = " << weite << std::endl;
	int x_point = xstart;
	CMyVektor res = y_Start;
	int counter = 0;

	while (counter < schrittanzahl) {

		std::cout << "Schritt " << counter << " :\n";
		std::cout << "\t x = " << xstart << std::endl;
		std::cout << "\t y = ";
		res.printAll();
		std::cout << std::endl;
		std::cout << "\t y' = ";
		(ableitung(res, xstart)).printAll();
		std::cout << std::endl;

		//naechster Schritt/next step
		res = res + (weite*ableitung(res, xstart));
		xstart += weite;


		//xpoint+
		counter++;
	}
	std::cout << "Ende bei \n";
	std::cout << "\t x = "<<xstart<<std::endl;
	std::cout << "\t y = ";
	res.printAll();
	std::cout << std::endl;

	return res;
}

CMyVektor C_DGLSolver::heun(double xstart, double xend, double schrittanzahl, CMyVektor y_Start)
{
	double weite = (xend - xstart) / schrittanzahl;
	std::cout << "h = " << weite << std::endl;
	int x_point = xstart;
	CMyVektor res = y_Start;
	CMyVektor test = res;
	int counter = 0;

	while (counter < schrittanzahl) {

		std::cout << "Schritt " << counter << " :\n";
		std::cout << "\t x = " << xstart << std::endl;
		std::cout << "\t y = ";
		res.printAll();
		std::cout << std::endl;
		std::cout << "\t y' orig = ";
		(ableitung(res, xstart)).printAll();
		std::cout << std::endl;
		//test
		test = res + (weite*ableitung(res, xstart));

		std::cout << "\t y test = ";
		test.printAll();
		std::cout << std::endl;
		std::cout << "\t y' test = ";
		ableitung(test, (xstart + weite)).printAll();
		std::cout << std::endl;

		//y(x1) = y(x0)+h*y'mittel
		test = 0.5 * ((ableitung(test, xstart + weite)) + ableitung(res, xstart));
		std::cout << "\t y' mittel = ";
		test.printAll();
		std::cout << std::endl;
		//naechster Schritt/next step mit mittlerem wert
		res = res + (weite*test);
		xstart += weite;


		//xpoint+
		counter++;
	}
	std::cout << "Ende bei \n";
	std::cout << "\t x = " << xstart << std::endl;
	std::cout << "\t y = ";
	res.printAll();
	std::cout << std::endl;

	return res;
}

CMyVektor C_DGLSolver::euler_fast(double xstart, double xend, double schrittanzahl, CMyVektor y_Start)
{
	double weite = (xend - xstart) / schrittanzahl;

	int x_point = xstart;
	CMyVektor res = y_Start;
	int counter = 0;

	while (counter < schrittanzahl) {

		//naechster Schritt/next step
		res = res + (weite*ableitung(res, xstart));
		xstart += weite;


		//xpoint+
		counter++;
	}

	return res;
}

CMyVektor C_DGLSolver::heun_fast(double xstart, double xend, double schrittanzahl, CMyVektor y_Start)
{
	double weite = (xend - xstart) / schrittanzahl;

	int x_point = xstart;
	CMyVektor res = y_Start;
	CMyVektor test = res;
	int counter = 0;

	while (counter < schrittanzahl) {
		//test
		test = res + (weite*ableitung(res, xstart));

		//y(x1) = y(x0)+h*y'mittel
		test = 0.5 * ((ableitung(test, xstart + weite)) + ableitung(res, xstart));

		//naechster Schritt/next step mit mittlerem wert
		res = res + (weite*test);
		xstart += weite;

		//xpoint+
		counter++;
	}

	return res;
}
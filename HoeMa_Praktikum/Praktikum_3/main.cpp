#include<iostream>
#include"C_DGLSolver.h"
#include"CMyVektor.h"


CMyVektor f(CMyVektor y, double x) {
	CMyVektor res;
	res.createVektorWithDim(2);

	res[0] = (2 * y[1]) - (x*y[0]);
	res[1] = (y[0] * y[1]) - (2 * pow(x, 3));
	
	return res;
}

double g(CMyVektor y, double x) {
	return((2 * x*y[1] * y[2]) + 2 * pow(y[0], 2)*y[1]);
}


int main() {


	std::cout << "Praktikum 3 Mathe\n";

	//std::cout << "EULER \n";
	CMyVektor dgl;
	dgl.createVektorWithDim(2);
	dgl[0] = 0;
	dgl[1] = 1;

	C_DGLSolver solver(f);
	//3)1)
	//solver.euler(0, 2, 100, dgl);
	//solver.heun(0, 2, 100, dgl);


	//3)2)
	C_DGLSolver solver2(g);
	CMyVektor dgl2;
	dgl2.createVektorWithDim(3);
	dgl2[0] = 1;
	dgl2[1] = -1;
	dgl2[2] = 2;

	for (int i = 0, schritt = 10; i < 4; i++,schritt*=10)
	{
		std::cout << "Abweichung bei Euler bei " << schritt << " Schritten: "<<0.5 - (solver2.euler_fast(1, 2, (double)schritt, dgl2))[0]<<std::endl;
		
		std::cout << "Abweichung bei Heun bei " << schritt << " Schritten: " << 0.5 - (solver2.heun_fast(1, 2, (double)schritt, dgl2))[0] << std::endl;

	}



	system("PAUSE");
	return 0;
}
#pragma once
#include "CMyVektor.h"

class C_DGLSolver
{
public:

	//first-order
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x));
	//higher-order
	C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x));
	~C_DGLSolver();

	CMyVektor ableitung(CMyVektor y, double x);

	CMyVektor euler(double xstart, double xend, double schrittanzahl, CMyVektor y_Start);
	CMyVektor heun(double xstart, double xend, double schrittanzahl, CMyVektor y_Start);

	CMyVektor euler_fast(double xstart, double xend, double schrittanzahl, CMyVektor y_Start);
	CMyVektor heun_fast(double xstart, double xend, double schrittanzahl, CMyVektor y_Start);

private:

	bool higher_order = false;
	//functionpointer save to
	CMyVektor(*fo)(CMyVektor y, double x);
	double(*ho)(CMyVektor y, double x);
};

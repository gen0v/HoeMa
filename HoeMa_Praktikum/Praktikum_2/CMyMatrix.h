#pragma once
#include <vector>
#include "CMyVektor.h"

class CMyMatrix {
	friend class CMyVektor;

public:
	CMyMatrix();
	~CMyMatrix();
	void createMatrixWithDim(int w, int h);
	double getComponent(int x, int y);
	void setComponent(int x, int y, double value);
	CMyMatrix invers();
	bool detNotZero();
	void print();
	void operator=(CMyMatrix copy);
	friend CMyVektor operator*(CMyMatrix m, CMyVektor v);

	CMyMatrix jacobi(CMyVektor x, CMyVektor(*function)(CMyVektor x));
	CMyVektor newton(CMyVektor x, CMyVektor(*function)(CMyVektor x));

private:
	int height = 0;
	int width = 0;
	std::vector<double> matrix;





};
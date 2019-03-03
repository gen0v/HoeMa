#pragma once
#include <vector>


class CMyVektor
{
public:
	CMyVektor();
	~CMyVektor();
	void createVektorWithDim(int d);
	int getDimension() { return dimension; }
	void printAll();
	double& operator[](int);
	void operator=(CMyVektor a);
	//void operator()(int);
	double operator()(int);
	int getSize() { return values.size(); }
	friend CMyVektor operator+(CMyVektor a, CMyVektor b);
	friend CMyVektor operator-(CMyVektor a, CMyVektor b);
	friend CMyVektor operator*(double lambda, CMyVektor a);
	friend CMyVektor operator/(CMyVektor a, double lambda);

	CMyVektor gradient(CMyVektor x, double(*function)(CMyVektor x));
	double maximaze(CMyVektor x, double(*function)(CMyVektor x), double lambda = 1.0);
	double absolutValue(CMyVektor x);
	double absolutValue();

private:
	int dimension = 0;
	std::vector<double> values;
	double t = 0;//for error return



};


#pragma once
#include <vector>
#include <math.h>

class CKomplex {

private:
	double realteil, imaginaerteil;

public:
	CKomplex(double a, double b);
	CKomplex(double phi);
	CKomplex();
	
	
	friend CKomplex operator + (CKomplex a, CKomplex b);
	friend CKomplex operator * (CKomplex a, CKomplex b);
	friend CKomplex operator * (double d, CKomplex b);
	
	
	double re();
	double im();
	double abs();

};





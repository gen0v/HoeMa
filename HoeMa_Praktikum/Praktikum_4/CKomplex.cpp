#include "CKomplex.h"

CKomplex::CKomplex() {

}

CKomplex::CKomplex(double a, double b) {
	realteil = a;
	imaginaerteil = b;
}

CKomplex::CKomplex(double phi) {
	realteil = cos(phi);
	imaginaerteil = sin(phi);
}
double CKomplex::re() {
	return realteil;
}
double CKomplex::im() {
	return imaginaerteil;
}
double CKomplex::abs() {
	return sqrt((realteil*realteil) + (imaginaerteil*imaginaerteil));
}

CKomplex operator + (CKomplex a, CKomplex b)
{
	return CKomplex(a.realteil + b.realteil, a.imaginaerteil + b.imaginaerteil);
}
CKomplex operator * (CKomplex a, CKomplex b) {
	return CKomplex((a.realteil*b.realteil) + (a.imaginaerteil*b.imaginaerteil*(-1.0)), (a.realteil*b.imaginaerteil) + (a.imaginaerteil*b.realteil));
}
CKomplex operator * (double k, CKomplex b) {
	return CKomplex(k*b.realteil, k*b.imaginaerteil);
}
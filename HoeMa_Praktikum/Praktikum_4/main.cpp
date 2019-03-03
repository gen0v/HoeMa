#include <iostream>
#include "CKomplex.h"
#include <fstream>   
#include <vector>

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;


vector<CKomplex> werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i<N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}


double differenz(vector<CKomplex> oldV, vector<CKomplex> newV)
{
	double max = 0;
	for (int i = 0; i < oldV.size(); i++)
	{
		double oldn = oldV[i].abs();
		double newn = newV[i].abs();
		double difn = newn - oldn;
		if (difn < 0) {
			difn = difn * (-1);
		}
		if (difn > max) {
			max = difn;   
		}
	}
	return max;
}

vector<CKomplex> fourier_Transformation(vector<CKomplex> data, bool hin) {
	vector<CKomplex> res;
	int size = data.size();
	int way = 0;
	if (hin == true) {
		way = -1;
	}
	else way = 1;

	double oneDivSqrtSize = 1.0 / sqrt(size);
	for (int n = 0; n < size; n++) {
		CKomplex back(0, 0);//new Complex
		for (int k = 0; k < size; k++) {
			back = back + (data.at(k) * CKomplex((way*(2 * 3.14159265358979323846*k*n)) / size));
		}
		res.push_back(oneDivSqrtSize * back);
	}
	return res;
}


int main() {

	vector<CKomplex> daten = werte_einlesen("Daten_original.txt");
	vector<CKomplex> hin = fourier_Transformation(daten, true);

	double eps = 0;
	werte_ausgeben("AusgabeHin_0.txt", hin, eps);
	vector<CKomplex> rueck = werte_einlesen("AusgabeHin_0.txt");
	rueck = fourier_Transformation(rueck, false);
	werte_ausgeben("AusgabeRueck_0.txt", rueck, eps);
	std::cout << "Maximale Abweichung bei Epsilon = 0: \t" << differenz(daten, rueck) << endl;

	eps = 0.1;
	werte_ausgeben("AusgabeHin_0.1.txt", hin, eps);
	vector<CKomplex> rueck2 = werte_einlesen("AusgabeHin_0.1.txt");
	rueck2 = fourier_Transformation(rueck2, false);
	werte_ausgeben("AusgabeRueck_0.1.txt", rueck2, eps);
	std::cout << "Maximale Abweichung bei Epsilon = 0.1: \t" << differenz(daten, rueck2) << endl;

	eps = 1.0;
	werte_ausgeben("AusgabeHin_1.0.txt", hin, eps);
	vector<CKomplex> rueck3 = werte_einlesen("AusgabeHin_1.0.txt");
	rueck3 = fourier_Transformation(rueck3, false);
	werte_ausgeben("AusgabeRueck_1.0.txt", rueck3, eps);
	std::cout << "Maximale Abweichung bei Epsilon = 1.0: \t" << differenz(daten, rueck3) << endl;



	system("pause");
}
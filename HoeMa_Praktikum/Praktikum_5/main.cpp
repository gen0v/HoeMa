#include <iostream>
#include "CZufall.h"
#include "CLotto.h"

using namespace std;

int main() {

	CZufall tester;
	tester.initialisiere(1);
	vector<int> t;

	//b--------------
	cout << "b) n = 1\n";
	t = tester.test(3, 7, 10000);
	for (int i = 0; i < 5; i++)
	{
		for (int a : t) {
			cout << " " << a << " ";
		}
		cout << endl;
	}

	//c--------------
	cout << "c) n = 0,1,2,3,4\n";
	for (int i = 0; i < 5; i++)
	{
		tester.initialisiere(i);
		t = tester.test(3, 7, 10000);
		for (int a : t) {
			cout << " " << a << " ";
		}
		cout << endl;
	}

	//d--------------
	cout << "d) n = time(NULL)\n";
	tester.initialisiere(time(NULL));
	t = tester.test(3, 7, 10000);
	for (int i = 0; i < 5; i++)
	{
		for (int a : t) {
			cout << " " << a << " ";
		}
		cout << endl;
	}

	//e--------------
	cout << "e)\n";

	t = tester.test_falsch(3, 7, 10000);
	for (int i = 0; i < 5; i++)
	{
		for (int a : t) {
			cout << " " << a << " ";
		}
		cout << endl;
	}

	cout << "2)\n";
	CLotto lotto(-1);

	vector<int> zettel = { 1,2,3,4,5,6 };

	lotto.setTippzettel(zettel);
	int g = lotto.lottoZiehung();
	cout << "Anzahl Richtige bei einer Lotto Ziehung:" << g << " \n";
	g = lotto.lottoZiehung2();
	cout << "Anzahl Richtige bei zwei Lotto Ziehung:" << g << " \n";


	cout << "3)\n";
	cout << "Monte-Carlo-Simulation mit 100000 Ziehungen (2d)\n";
	double count0 = 0;
	double count1 = 0;
	double count2 = 0;
	double count3 = 0;
	double count4 = 0;
	double count5 = 0;
	double count6 = 0;
	int in = 0;
	CLotto lottoM(-1);
	vector<int> zettelM = { 9,5,14,41,3,26 };
	lottoM.setTippzettel(zettelM);

	lottoM.doPrint = false;
	//wenn NUR 3 richtig
	for (int i = 0; i < 100000; i++)
	{
		in = lottoM.lottoZiehung();
		if (in >= 6) count6++;
		else if (in >= 5) count5++;
		else if (in >= 4) count4++;
		else if (in >= 3) count3++;
		else if (in >= 2) count2++;
		else if (in >= 1) count1++;
		else if (in >= 0) count0++;
	}
	cout << "0 Richtige - Ergebnis: " << (count0/100000)*100<<"% \n";
	cout << "1 Richtige - Ergebnis: " << (count1 / 100000) * 100 << "% \n";
	cout << "2 Richtige - Ergebnis: " << (count2 / 100000) * 100 << "% \n";
	cout << "3 Richtige - Ergebnis: " << (count3 / 100000) * 100 << "% \n";
	cout << "4 Richtige - Ergebnis: " << (count4 / 100000) * 100 << "% \n";
	cout << "5 Richtige - Ergebnis: " << (count5 / 100000) * 100 << "% \n";
	cout << "6 Richtige - Ergebnis: " << (count6 / 100000) * 100 << "% \n";



	CLotto lottoN(-1);
	lottoN.setTippzettel(zettelM);
	lottoN.doPrint = false;
	cout << "Monte-Carlo-Simulation mit 100000 Ziehungen (2e)\n";
	for (int i = 0; i < 100000; i++)
	{
		in = lottoN.lottoZiehung2();
		if (in >= 6) count6++;
		else if (in >= 5) count5++;
		else if (in >= 4) count4++;
		else if (in >= 3) count3++;
		else if (in >= 2) count2++;
		else if (in >= 1) count1++;
		else if (in >= 0) count0++;
	}
	cout << "0 Richtige - Ergebnis: " << (count0 / 100000) * 100 << "% \n";
	cout << "1 Richtige - Ergebnis: " << (count1 / 100000) * 100 << "% \n";
	cout << "2 Richtige - Ergebnis: " << (count2 / 100000) * 100 << "% \n";
	cout << "3 Richtige - Ergebnis: " << (count3 / 100000) * 100 << "% \n";
	cout << "4 Richtige - Ergebnis: " << (count4 / 100000) * 100 << "% \n";
	cout << "5 Richtige - Ergebnis: " << (count5 / 100000) * 100 << "% \n";
	cout << "6 Richtige - Ergebnis: " << (count6 / 100000) * 100 << "% \n";

	system("PAUSE");
	return 0;
}
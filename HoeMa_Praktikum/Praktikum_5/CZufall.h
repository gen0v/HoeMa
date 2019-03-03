#pragma once
#include <stdlib.h>
#include<vector>
#include<time.h>
#include <windows.h>

class CZufall
{
public:
	CZufall();
	~CZufall();

	int wert(int a, int b);
	void initialisiere(int n);
	std::vector<int> test(int a, int b, int N);
	std::vector<int> test_falsch(int a, int b, int N);

	std::vector<int> zufallWerte(int a, int b, int N);
private:

};

CZufall::CZufall()
{
}

CZufall::~CZufall()
{
}

int CZufall::wert(int a, int b)
{
	int res = rand() % (b - a + 1) + a;
	return res;
}

void CZufall::initialisiere(int n)
{
	srand(n);
}

std::vector<int> CZufall::zufallWerte(int a, int b, int N)
{
	std::vector<int> liste;
	std::vector<int> res;
	std::vector<int> vorgekommen;

	std::vector<int> werte;
	for (int i = a; i <= b; i++)
	{
		werte.push_back(i);
	}

	int w = 0;
	bool einfuegen = true;

	for (int i = 0; i < N; i++)
	{
		w = wert(a, b);
		for (int j = 0; j < liste.size(); j++)
		{
			if (w == liste[j]) {
				//wenn der wert vorkommt nicht einfugen N erhohen und noch eine zahl testen
				//std::cout << " WERTE GLEICH " << w << " == " << liste[j] << "\n";
				einfuegen = false;
				N++;
			}
		}
		if(einfuegen) liste.push_back(w);
		einfuegen = true;
	}
	//std::cout << " Abgegeben \n";
	return liste;
}

std::vector<int> CZufall::test(int a, int b, int N)
{
	std::vector<int> liste;
	std::vector<int> res;
	std::vector<int> vorgekommen;

	std::vector<int> werte;
	for (int i = a; i <= b; i++)
	{
		werte.push_back(i);
	}

	for (int i = 0; i < N; i++)
	{
		liste.push_back(wert(a, b));
	}

	//int vorkommen = 0;
	int count = 0;

	for (int wert_ab = 0; wert_ab < werte.size(); wert_ab++)
	{
		for (int j = 0; j < liste.size(); j++)
		{
			if (werte[wert_ab] == liste[j])count++;
		}
		res.push_back(count);
		count = 0;
	}


	return res;
}

std::vector<int> CZufall::test_falsch(int a, int b, int N)
{
	std::vector<int> liste;
	std::vector<int> res;
	std::vector<int> vorgekommen;

	std::vector<int> werte;
	for (int i = a; i <= b; i++)
	{
		werte.push_back(i);
	}

	//wait
	Sleep(1000);
	initialisiere(time(NULL));
	for (int i = 0; i < N; i++)
	{
		liste.push_back(wert(a, b));
		
	}

	//int vorkommen = 0;
	int count = 0;

	for (int wert_ab = 0; wert_ab < werte.size(); wert_ab++)
	{
		for (int j = 0; j < liste.size(); j++)
		{
			if (werte[wert_ab] == liste[j])count++;
		}
		res.push_back(count);
		count = 0;
	}


	return res;
}

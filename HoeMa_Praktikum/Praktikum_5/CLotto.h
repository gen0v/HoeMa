#pragma once
#include "CZufall.h"

class CLotto
{
public:
	CZufall zufall;
	CLotto(int n);
	~CLotto();
	void setTippzettel(std::vector<int> zettel);
	int lottoZiehung();
	int lottoZiehung2();

	void printTipp();
	void printZiehung();

	bool doPrint = true;

private:
	std::vector<int> Tippzettel;
	std::vector<int> Lottozettel;
	std::vector<int> ziehung();
};

CLotto::CLotto(int n)
{
	if (n > 0)
		zufall.initialisiere(n);
	else
		zufall.initialisiere(time(NULL));
}

CLotto::~CLotto()
{
}

void CLotto::setTippzettel(std::vector<int> zettel)
{
	Tippzettel = zettel;
}

int CLotto::lottoZiehung()
{
	int count = 0;
	std::vector<int> ziehungN = ziehung();
	
	std::vector<int> gewinnZahlen;

	printTipp();
	printZiehung();

	for (int i = 0; i < Tippzettel.size(); i++)
	{
		for (int j = 0; j < ziehungN.size(); j++)
		{
			if (Tippzettel[i] == ziehungN[j]) {
				count++;
				gewinnZahlen.push_back(Tippzettel[i]);
			}
		}
	}

	return count;
}

std::vector<int> CLotto::ziehung()
{
	std::vector<int> ziehung;
	ziehung = zufall.zufallWerte(1, 49, 6);

	Lottozettel = ziehung;
	return ziehung;
}

int CLotto::lottoZiehung2()
{
	int count = 0;
	std::vector<int> ziehungN;
	std::vector<int> gewinnZahlen;

	printTipp();

	//2 mal
	for (int k = 0; k < 2; k++)
	{
		ziehungN = ziehung();

		printZiehung();

		for (int i = 0; i < Tippzettel.size(); i++)
		{
			for (int j = 0; j < ziehungN.size(); j++)
			{
				if (Tippzettel[i] == ziehungN[j])
				{	
					count++;
					gewinnZahlen.push_back(Tippzettel[i]);
				}
			}
		}
	}

	return count;
}

void CLotto::printTipp()
{
	if (doPrint) {
		std::cout << "Der Tippzettel: \n";
		for (int a : Tippzettel)
			std::cout << " " << a;
		std::cout << std::endl;

	}
}

void CLotto::printZiehung()
{
	if (doPrint) {
		std::cout << "Die Ziehung: \n";
		for (int a : Lottozettel)
			std::cout << " " << a;
		std::cout << std::endl;
	}
}
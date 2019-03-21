#ifndef __STAJALISTE_
#define __STAJALISTE_ 1
#include<string>
#include<set>
#include<list>
#include"Lokacija.h"
class Linija;

using namespace std;
class Stajaliste{
	string naziv;
	int broj;
	Lokacija lokacija;
	list<Linija*> linije;
public:
	 
	Stajaliste() {}
	Stajaliste(int _broj, string _naziv, double _x, double _y, Linija* l);
	string getNaziv() const {return naziv;}
	int dohvBroj() const { return broj; }
	void dodajLiniju(Linija* l);
	bool izbrisiLiniju(Linija* l);
	friend ostream& operator<<(ostream& it,Stajaliste& s);
	list<Linija*> * getLinije();
	Lokacija getLokacija() { return lokacija; }
};

#endif
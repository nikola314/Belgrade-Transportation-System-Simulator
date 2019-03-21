#ifndef __LINIJA
#define __LINIJA 1
#include<list>
#include<set>
class Mreza;
class Stajaliste;
using namespace std;

class Linija{
	string naziv;
	list<Stajaliste*> smerA, smerB; 
	Mreza* mojaMreza;
	short zone[4] = { 0,0,0,0 };
	void pisi(ostream&);
	

public:
	static int brLinije(string);
	Linija * linijaSaNajviseZajednickihStajalista();
	int brZajednickihStajalista(Linija*l);
	short * getZone() { return zone; }
	string getNaziv() { return naziv; }
	Linija(string _naziv, Mreza* _mreza): naziv(_naziv), mojaMreza(_mreza){}
	void citajLiniju();
	int brStajalista();
	friend ostream& operator<<(ostream& it, Linija& l);
	void dodajStajaliste(Stajaliste *_ss, char smer) { if (smer == 'A' || smer == 'a') smerA.push_back(_ss); else if (smer == 'B' || smer == 'b') smerB.push_back(_ss); }
	bool operator<(Linija& l);
	set<Linija*> linijeSaZajednickimStajalistima();
	bool prolaziKrozOba(Stajaliste* s1, Stajaliste*s2);
	Stajaliste* sledeceStajaliste(Stajaliste* s);
	list<Stajaliste*> getStajalista();
};

#endif

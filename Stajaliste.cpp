#include "Stajaliste.h"
#include<algorithm>

Stajaliste::Stajaliste(int _broj, string _naziv, double _x, double _y, Linija* l) : lokacija(_x, _y) {
	broj = _broj;
	naziv = _naziv;
	linije.push_back(l);
}

void Stajaliste::dodajLiniju(Linija * l)
{
	// Ako nije vec unutra! -> if()
	linije.push_back(l);
}

bool Stajaliste::izbrisiLiniju(Linija * l)
{
	//zbog filtriranja linija
	//ako nakon brisanja linije lista linija ostane prazna treba vratiti false

	list<Linija*>::iterator it;
	it = search_n(linije.begin(), linije.end(), 1, l, []( Linija* l1,  Linija* l2)->bool {return (l2 == l1); });
	if (it == linije.end()) return true;
	linije.erase(it);
	if (linije.size() == 0) return false;
	return true;
}

list<Linija*>* Stajaliste::getLinije()
{
	return &linije;
}

ostream & operator<<(ostream & it, Stajaliste & s)
{
	return it << s.naziv << " " << s.broj << " "<<s.lokacija;
}

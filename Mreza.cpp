#include "Mreza.h"
#include <fstream>
#include<regex>
#include<iostream>
#include<utility>
#include"Linija.h"
#include"Stajaliste.h"
#include"CGenerator.h"
#include"LGenerator.h"

void Mreza::napraviGraf()
{
	if (cGenerator || lGenerator) return;
	cGenerator = new CGenerator(this);
	lGenerator = new LGenerator(this);
	cGenerator->generisi(linije,stajalista);
 	lGenerator->generisi(linije,stajalista);
}

void Mreza::ucitajLinije()
{
	ifstream file("data/_lines.txt");
	if (!file) { /*ne radi*/ }
	string s;
	regex reg("([^!]*).*");
	while (getline(file, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {
			linije.push_back(new Linija(result.str(1),this));
		}
	}
	file.close();
}

Stajaliste* Mreza::stajalisteUSkupu(int id)
{
	for (auto e : stajalista) {
		if (e->dohvBroj() == id) return e;
	}
	return nullptr;
}

void Mreza::ucitajStajalista()
{
	for (auto x : linije) {
		x->citajLiniju();
	}
}

void Mreza::dodajStajaliteUSkup(Stajaliste * s)
{
	stajalista.push_back(s);
}

ostream & operator<<(ostream & it, Mreza &m)
{
	m.pisi(it);
	return it;
}

void Mreza::pisi(ostream &it)
{
	for (auto x : linije)
		it << *x << endl;
}




/*
	mod: 0-> ostaju oni sa manjim brojem
		 1-> ostaju oni sa vecim brojem
		 2-> ostaju oni iz opsega zadatog drugim i trecim argumentom
*/
void Mreza::filtriraj(int mod, string _linije, string _do = "")
{
	int down = Linija::brLinije(_linije);
	int up;
	if (mod == 2) up = Linija::brLinije(_do);
	
	auto i = linije.begin();
	while (i != linije.end()) {	
		bool neispravan = false;
		switch (mod) {
		case 0: if (Linija::brLinije((*i)->getNaziv()) > down) neispravan = true; break;
		case 1: if (Linija::brLinije((*i)->getNaziv()) < down) neispravan = true; break;
		case 2: if (Linija::brLinije((*i)->getNaziv())<=down || Linija::brLinije((*i)->getNaziv()) >=up) neispravan = true; break;
		}
		if (neispravan) {
			//izbrisati liniju iz niza stajalista
			brisiLinijuIzStajalista(*i);
			i = linije.erase(i);
		}
		else i++;
	}
}

//_veci==1 ->ostaju oni sa vecim brojem od _broj_stajalista
void Mreza::filtriraj(bool _veci, int _broj_stajalista)
{
	auto i = linije.begin();
	while (i != linije.end()) {
		bool neispravan = false;

		if (_veci)
			if ((*i)->brStajalista() <= _broj_stajalista) neispravan = true;
			else if ((*i)->brStajalista() >= _broj_stajalista) neispravan = true;

			if (neispravan) {
				//izbrisati liniju iz niza stajalista
				brisiLinijuIzStajalista(*i);
				i = linije.erase(i);
			}
			else i++;
	}
}

void Mreza::filtriraj(int _zona) //za samo prvu _zona ==1, za prvu i drugu _zona==2 itd...
{
	if (_zona > 3) return;
	auto i = linije.begin();
	bool neispravan;
	while (i != linije.end()) {
		short * zone = (*(i))->getZone();
		neispravan = false;
		for (int j = _zona; j < 4; j++)
			if (zone[j] > 0)
				neispravan = true;
		if (neispravan) {
			//izbrisati liniju iz niza stajalista
			brisiLinijuIzStajalista(*i);
			i = linije.erase(i);
		}
		else i++;
	}
}

void Mreza::brisiLinijuIzStajalista(Linija *l)
{
	vector<Stajaliste*>::iterator it = stajalista.begin();
	while (it != stajalista.end()) {
		if (!((*it)->izbrisiLiniju(l))) {
			//brisanje celog stajalista ako vise nema linija koje prolaze kroz njega
			it = stajalista.erase(it);
		}
		else it++;
	}
}

set<Linija*> Mreza::linijeSaZajednickimStajalistima(Linija *l)
{
	return l->linijeSaZajednickimStajalistima();
}

Stajaliste * Mreza::najblizeStajaliste(Lokacija _l, Linija * _linija)
{
	vector<Stajaliste*>::iterator it;
	Lokacija lok = _l;
	if (_linija == nullptr)
		it = min_element(stajalista.begin(), stajalista.end(), [_l](Stajaliste* s1, Stajaliste* s2)->bool {
		return s1->getLokacija().razdaljina(_l) < s2->getLokacija().razdaljina(_l);
	});
	else
		it = min_element(stajalista.begin(), stajalista.end(), [_l, _linija](Stajaliste* s1, Stajaliste* s2)->bool {
		list<Linija*> *line1 = s1->getLinije();
		list<Linija*> *line2 = s2->getLinije();
		bool ima1 = (find(line1->begin(), line1->end(), _linija) != line1->end());
		bool ima2 = (find(line2->begin(), line2->end(), _linija) != line2->end());
		if (!ima1) return false;
		if (!ima2) return true;
		return s1->getLokacija().razdaljina(_l) < s2->getLokacija().razdaljina(_l);
	});
	return *it;
}

Mreza::~Mreza()
{
	if (cGenerator) delete cGenerator;
	if (lGenerator) delete lGenerator;
	for (auto &i : linije) delete i;
	for (auto &i : stajalista) delete i;
}

void Mreza::zajednicka()
{
	Linija* l = linije.front();
	set<Linija*> lii = linijeSaZajednickimStajalistima(l);
	for (auto x : lii) {
		cout << x->getNaziv() << endl;
	}
}

void Mreza::testNajkraciPut()
{
	cout << "NAJKRACI PUT:" << endl;
	Stajaliste* s1, *s2;
	s1 = stajalisteUSkupu(343);
	s2 = stajalisteUSkupu(19);
	cout << *s1 << " - ";
	cout << *s2;
	cout << endl;
	cout << "Najmanje stajalista: " << najkraciPut(s1, s2);
	cout << endl << "Najmanje presedanja: " << najmanjePresedanja(s1, s2) << endl;
	cout << endl << endl;
	s1 = stajalisteUSkupu(339);
	s2 = stajalisteUSkupu(449);
	cout << *s1 << " - ";
	cout << *s2;
	cout << endl;
	cout << "Najmanje stajalista: " << najkraciPut(s1, s2);
	cout << endl << "Najmanje presedanja: " << najmanjePresedanja(s1, s2) << endl;
	cout << endl << endl;
	s1 = stajalisteUSkupu(340);
	s2 = stajalisteUSkupu(339);
	cout << *s1 << " - ";
	cout << *s2;
	cout << endl;
	cout <<"Najmanje stajalista: "<< najkraciPut(s1, s2);
	cout << endl <<"Najmanje presedanja: "<<najmanjePresedanja(s1,s2)<< endl;
	

	cout << endl << endl << "Broj zajednickih stajalista za sve parove linija: " << endl << endl;
	vector<pair<pair<Linija*, Linija*>, int>> parovi = brojZajednickihStajalista(5);
	for (auto par : parovi) 
		cout << endl << par.first.first->getNaziv() << " - " << par.first.second->getNaziv() << " -> " << par.second;
	cout << endl << endl;

	cout << "ODREDJIVANJE NAJBLIZEG STAJALISTA U ODNOSU NA LOKACIJU: \n";
	cout << "49, 53 -> " << *najblizeStajaliste(*(new Lokacija(49, 53)))<<endl;
	cout << "41, 20 -> " << *najblizeStajaliste(*(new Lokacija(41, 20))) << endl;
	cout << "20, 44 -> " << *najblizeStajaliste(*(new Lokacija(20, 44))) << endl;
	cout << endl << endl;
	cout << "LINIJA SA NAJVISE ZAJEDNICKIH STAJALISTA: \n";
	int i = 0;
	for (list<Linija*>::iterator it = linije.begin(); i < 10; it++, i++) {
		cout << (*it)->getNaziv() << " - " << (*it)->linijaSaNajviseZajednickihStajalista()->getNaziv() << endl;
	}
	system("pause");
}

vector<pair<pair<Linija*, Linija*>, int>> Mreza::brojZajednickihStajalista(int _limit)
{
	vector<pair<pair<Linija*, Linija*>, int>> parovi;
	for (auto i = linije.begin(); i != linije.end(); i++){
		set<Linija*> z_linije = linijeSaZajednickimStajalistima(*i);
		for (auto j = next(i, 1); j != linije.end(); j++) {
			if (!z_linije.count(*j)) continue;
			int cnt = (*i)->brZajednickihStajalista(*j);
			if (cnt > _limit) 
				parovi.push_back(make_pair(make_pair(*i,*j),cnt));		
		}
	}
	return parovi;
}

list<Linija*> Mreza::linijeKrozStajaliste(Stajaliste * _s)
{
	return *(_s->getLinije());
}

set<Stajaliste*> Mreza::zaJednuStanicu(Stajaliste * _s)
{
	list<Linija*> *linije = _s->getLinije();
	set<Stajaliste*> stajalista;
	for (auto i : (*linije)) {
		Stajaliste* st;
		if (st = i->sledeceStajaliste(_s))
			stajalista.insert(st);
	}
	return stajalista;
}

int Mreza::najmanjePresedanja(Stajaliste * s1, Stajaliste * s2)
{
	int cnt = 0;
	vector<Linija*> target;
	vector<Linija*> current;
	vector<Stajaliste*> stajalista;
	vector<Stajaliste*> stajalista2;
	stajalista.push_back(s1);
	for (auto i : *s2->getLinije())
		target.push_back(i);

	bool done = false;
	while (!done) {
		while (!stajalista.empty()) {
			Stajaliste* temp = stajalista.back();
			stajalista.pop_back();
			list<Linija*>* linije = temp->getLinije();
			for (auto i : *linije) {
				if (find(target.begin(), target.end(), i) != target.end()) {
					done = true; break;
				}
				if (find(current.begin(), current.end(), i) != current.end()) continue;
				else current.push_back(i);
				list<Stajaliste*> st = i->getStajalista();
				for (auto x : st) stajalista2.push_back(x);
			}
			if (done) break;
		}
		if (done) break;
		cnt++;

		//isti while
		while (!stajalista2.empty()) {
			
			Stajaliste* temp = stajalista2.back();
			stajalista2.pop_back();
			list<Linija*>* linije = temp->getLinije();
			for (auto i : *linije) {
				if (find(target.begin(), target.end(), i) != target.end()) {
					done = true; break;
				}
				if (find(current.begin(), current.end(), i) != current.end()) continue;
				else current.push_back(i);
				list<Stajaliste*> st = i->getStajalista();
				for (auto x : st) stajalista.push_back(x);
			}
			if (done) break;
		}
		if (!done) cnt++;
	}
	return cnt;
}


int Mreza::ukupnoStajalista()
{
	return stajalista.size();
}

int Mreza::ukupnoLinija()
{
	return linije.size();
}


int Mreza::najkraciPut(Stajaliste * _s1, Stajaliste * _s2)
{
	int cnt = 0;

	set<Stajaliste*> s1;
	set<Stajaliste*> s2;
	set<Stajaliste*> prosli;
	s1 = zaJednuStanicu(_s1);
	bool found = false;
	while (s1.size() > 0 || s2.size() > 0) {
		for (auto i : s1) {
			if (i == _s2) { found = true; break; }
			if (prosli.find(i) == prosli.end()) {
				prosli.insert(i);
				set<Stajaliste*> temp = zaJednuStanicu(i);
				for (auto j : temp) s2.insert(j);
			}
		}
		s1.clear();
		cnt++;
		if (found) return cnt;

		for (auto i : s2) {
			if (i == _s2) { found = true; break; }
			if (prosli.find(i) == prosli.end()) {
				prosli.insert(i);
				set<Stajaliste*> temp = zaJednuStanicu(i);
				for (auto j : temp) s1.insert(j);
			}
		}
		s2.clear();
		cnt++;
		if (found) return cnt;

	}
	return -1;
}

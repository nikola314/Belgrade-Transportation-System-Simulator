
#include <fstream>
#include<regex>
#include<iostream>
#include<string>
#include<set>
#include"linija.h"
#include"Stajaliste.h"
#include "Mreza.h"
#include <algorithm>
#include <map>
void Linija::citajLiniju()
{
string imeFajla = "data/" + naziv + "_dirA.txt";
ifstream file(imeFajla);
if (!file) { cout << "NE RADI A"; }
string s;
regex reg("([^!]*)!([^!]*)!([^!]*)!([^!]*)!(.)");
while (getline(file, s)) {
	smatch result;
	if (regex_match(s, result, reg)) {
		Stajaliste* novi = nullptr;
		if (novi = mojaMreza->stajalisteUSkupu(atoi(result.str(1).c_str()))) {
			smerA.push_back(novi);
			novi->dodajLiniju(this);
		}
		else {
			novi = new Stajaliste(
				atoi(result.str(1).c_str()),
				result.str(2),
				atof(result.str(3).c_str()),
				atof(result.str(4).c_str()),
				this);
			mojaMreza->dodajStajaliteUSkup(novi);
			smerA.push_back(novi); 
		}	
		zone[atoi(result.str(5).c_str())-1] = 1;
	}
}
file.close();
imeFajla = "data/" + naziv + "_dirB.txt";
ifstream file1(imeFajla);
if (!file1) { cout << "NE RADI B";/*ne radi*/ }
while (getline(file1, s)) {
	smatch result;
	if (regex_match(s, result, reg)) {
		Stajaliste* novi = nullptr;

		if (novi = mojaMreza->stajalisteUSkupu(atoi(result.str(1).c_str()))) {
			smerB.push_back(novi);
			novi->dodajLiniju(this);
		}
		else {
			novi = new Stajaliste(
				atoi(result.str(1).c_str()),
				result.str(2),
				atof(result.str(3).c_str()),
				atof(result.str(4).c_str()),
				this);
			mojaMreza->dodajStajaliteUSkup(novi);
			smerB.push_back(novi);
		}
		zone[atoi(result.str(5).c_str())-1] = 1;
	}
}
file1.close();
}

int Linija::brStajalista()
{
	return smerA.size() + smerB.size();
}

bool Linija::operator<(Linija & l)
{
	return Linija::brLinije(naziv) < Linija::brLinije(l.getNaziv());
}

set<Linija*> Linija::linijeSaZajednickimStajalistima()
{
	set<Linija*> zajednicke;

	for (auto x : smerA) {
		list<Linija*> * linije = x->getLinije();
		for (auto st : (*linije)) {
			if (st != this)
				zajednicke.insert(st);
		}
	}
	for (auto x : smerB) {
		list<Linija*> * linije = x->getLinije();
		for (auto st : (*linije)) {
			if(st!=this)
				zajednicke.insert(st);
		}
	}
	return zajednicke;
}

int Linija::brZajednickihStajalista(Linija*l) {
	int cnt = 0;
	vector<Stajaliste*> prosli;

	for (auto x : smerA) {
		list<Linija*> * linije = x->getLinije();
		for (auto st : (*linije)) 
			if (st == l) 
				if (find(prosli.begin(), prosli.end(), x) == prosli.end()) {
					cnt++; prosli.push_back(x);
				}
	}
	for (auto x : smerB) {
		list<Linija*> * linije = x->getLinije();
		for (auto st : (*linije)) 
			if (st == l)
				if (find(prosli.begin(), prosli.end(), x) == prosli.end()) {
					cnt++; prosli.push_back(x);
				}
	}
	return cnt;
}

bool Linija::prolaziKrozOba(Stajaliste * s1, Stajaliste * s2)
{
	if ((find(smerA.begin(), smerA.end(), s1) != smerA.end()
			&& find(smerA.begin(), smerA.end(), s2) != smerA.end())
		|| (find(smerB.begin(), smerB.end(), s1) != smerB.end()
			&& find(smerB.begin(), smerB.end(), s2) != smerB.end()))
		return true;
	return false;
}

Stajaliste * Linija::sledeceStajaliste(Stajaliste * s)
{
	list<Stajaliste*>::iterator it = find(smerA.begin(), smerA.end(), s);
	list<Stajaliste*>::iterator ib = find(smerB.begin(), smerB.end(), s);
	if (it == smerA.end()){
		if (ib == smerB.end()) return nullptr;
		auto ii = next(ib, 1);
		if (ii == smerB.end()) return smerA.size() > 0 ? *smerA.begin() : nullptr;
		return *ii;
	}
	else {
		if (it == smerA.end()) return nullptr;
		auto ii = next(it, 1);
		if (ii == smerA.end()) return smerB.size() > 0 ? *smerB.begin() : nullptr;
		return *ii;
	}
}

list<Stajaliste*> Linija::getStajalista()
{
	list<Stajaliste*> l(smerA);
	list<Stajaliste*> l2(smerB);
	l.sort();
	l2.sort();
	l.merge(l2);
	return l;
}


void Linija::pisi(ostream& it) {
	it << "Linija " << naziv << endl;
	it << "Zone: ";
	for (int i = 0; i < 4; i++) 
		if (zone[i]) 
			it << i + 1 << " ";
	it << endl << endl;
	it << "Smer A:" << endl;
	for (auto x : smerA) {
		it << *x << endl;
	}
	it << "Smer B:" << endl;
	for (auto x : smerB) {
		it << *x << endl;
	}
	it << endl << endl << endl;
}

int Linija::brLinije(string s)
{
	regex reg("[^0-9]*([0-9]*).*");
	smatch result;
	if (regex_match(s, result, reg)) {
		return atoi(result.str(1).c_str());
	}
	return -1;
}

ostream & operator<<(ostream & it, Linija & l)
{
	l.pisi(it);
	return it;
}

Linija* Linija::linijaSaNajviseZajednickihStajalista() {
	map<Linija*, int> cnt;
	int max = 0;
	Linija* l = nullptr;
	int tr;
	for (auto st : smerA) {
		for (auto li : *(st->getLinije())) {
			if (li == this) continue;
			if (cnt.count(li) > 0) {
				int temp = cnt[li];
				cnt.erase(li);
				cnt[li] = temp + 1;
				tr = temp + 1;
			}
			else {
				cnt[li] = 1; tr = 1;
			}
			if (tr > max) {
				max = tr;
				l = li;
			}
		}
	}
	for (auto st : smerA) {
		for (auto li : *(st->getLinije())) {
			if (li == this) continue;
			if (cnt.count(li) > 0) {
				int temp = cnt[li];
				cnt.erase(li);
				cnt[li] = temp + 1;
				tr = temp + 1;
			}
			else {
				cnt[li] = 1; tr = 1;
			}
			if (tr > max) {
				max = tr;
				l = li;
			}
		}
	}
	return l;
}

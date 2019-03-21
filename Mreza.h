#ifndef __MREZA
#define __MREZA 1

#include<string>
#include<vector>
#include<list>
#include"Lokacija.h"
#include<set>
#include"Generator.h"
class Linija;
class Stajaliste;
using namespace std;
class Mreza{
	list<Linija*> linije;
	vector<Stajaliste*> stajalista;
	Generator* cGenerator = nullptr;
	Generator* lGenerator = nullptr;

	void pisi(ostream&);
	
public:
	int ukupnoStajalista();
	int ukupnoLinija();
	void napraviGraf();
	void ucitajLinije();
	Stajaliste* stajalisteUSkupu(int id);
	void ucitajStajalista();
	void dodajStajaliteUSkup(Stajaliste*);
	void infoLinija(string _ime_linije);
	void infoStajaliste(string _broj_stajalista);
	void dodajStajalisteLiniji(Stajaliste _stajaliste, string _ime_linije,int _index);
	void filtriraj(int _zona);
	void filtriraj(int mod, string _linije, string _do);
	void filtriraj(bool _veci, int _broj_stajalista);
	void brisiLinijuIzStajalista(Linija*);
	void izlazGML(string _imeFajla);
	void izlazCSV(string _imeFajla);
	set<Linija> linijeSaZajednickimStajalistima(string _linija);
	bool prolazeKrozOba(pair<Stajaliste,Stajaliste> _stajalista);
	vector<pair<pair<Linija*, Linija*>, int>> brojZajednickihStajalista(int _limit=0);
	list<Linija*> linijeKrozStajaliste(Stajaliste* _s);
	set<Stajaliste*> zaJednuStanicu(Stajaliste* _s);
	int najmanjePresedanja(Stajaliste * s1,Stajaliste *s2);
	int najkraciPut(Stajaliste* _s1,Stajaliste* _s2);
	set<Linija*> linijeSaZajednickimStajalistima(Linija *);
	Stajaliste* najblizeStajaliste(Lokacija _l, Linija* _linija = nullptr);
	~Mreza();

	//test
	friend ostream& operator<<(ostream&, Mreza&);
	void zajednicka();
	void testNajkraciPut();
};


#endif
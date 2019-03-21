#ifndef __GENERATOR
#define __GENERATOR 1
#include"Format.h"
#include<list>
#include<vector>
using namespace std;
class Linija;
class Stajaliste;
class Mreza;

struct grana {
	string a, b;
	grana(string aa, string bb) {
		a = aa;
		b = bb;
	}
	bool operator==(grana&bb) {
		if (a == bb.a &&b == bb.b) return true;
		if (b == bb.a && a == bb.b) return true;
		return false;
	}
};

struct granaS {
	string a, b;
	granaS(int aa, int bb) {
		a = aa;
		b = bb;
	}
	bool operator==(granaS&bb) {
		if (a == bb.a &&b == bb.b) return true;
		if (b == bb.a && a == bb.b) return true;
		return false;
	}
};

class Generator{
	
public:
	Generator(Mreza*mm) :m(mm) {}
	virtual void generisi(std::list<Linija*> l, std::vector<Stajaliste*> s) = 0;
	~Generator() { if (CSV) delete CSV; if (GML) delete GML; }
protected:
	Mreza* m;
	Format * CSV = nullptr;
	Format * GML = nullptr;
};

#endif
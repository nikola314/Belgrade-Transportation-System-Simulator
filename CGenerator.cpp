#include "CGenerator.h"
#include "CSVFormat.h"
#include"GMLFormat.h"
#include<set>
#include"linija.h"
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
void CGenerator::generisi(std::list<Linija*> l, std::vector<Stajaliste*> s)
{	
	if (CSV || GML) return;
	CSV = new CSVFormat("C_CSV.csv");
	GML = new GMLFormat("C_GML.gml");

	vector<grana> grane;
	for (auto i : l) {
		set<Linija*> komsije = i->linijeSaZajednickimStajalistima();
		for (auto x : komsije) {
			
			//ako ne postoji grana
			bool postoji = false;
			grana g(x->getNaziv(), i->getNaziv());
			for (auto k : grane) {
				if (k == g) { postoji = true;
				break;
				}
			}
			if (!postoji) {
				grane.push_back(g);
				CSV->dodaj(1, i->getNaziv(), x->getNaziv());
				GML->dodaj(1, i->getNaziv(), x->getNaziv());
			}			
		}
	}
	CSV->zavrsi();
	GML->zavrsi();
}

#include "LGenerator.h"
#include "CSVFormat.h"
#include"GMLFormat.h"
#include"Mreza.h"
#include"Stajaliste.h"
void LGenerator::generisi(std::list<Linija*> l, std::vector<Stajaliste*> s)
{
	if (CSV || GML) return;
	CSV = new CSVFormat("L_CSV.csv");
	GML = new GMLFormat("L_GML.gml");

	
	vector<granaS> grane;

	for (auto i : s) {
		set<Stajaliste*> komsije = m->zaJednuStanicu(i);
		for (auto x : komsije) {
			
			bool postoji = false;
			granaS g(x->dohvBroj(), i->dohvBroj());
			for (auto k : grane) {
				if (k == g) {
					postoji = true;
					break;
				}
			}
			if (!postoji) {
				grane.push_back(g);
				CSV->dodaj(1, to_string(i->dohvBroj()), to_string(x->dohvBroj()));
				GML->dodaj(1, to_string(i->dohvBroj()), to_string(x->dohvBroj()));
			}
		}
	}
	CSV->zavrsi();
	GML->zavrsi();

}

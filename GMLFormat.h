#ifndef __GMLFORMAT
#define __GMLFORMAT 1
#include "Format.h"

class GMLFormat: public Format{
public:
	GMLFormat(char * ime) {
		f.open(ime);
		f << "graph\n[\n";
	}
	 void dodaj(int tip, std::string a, std::string b);
	 void zavrsi();
};

#endif
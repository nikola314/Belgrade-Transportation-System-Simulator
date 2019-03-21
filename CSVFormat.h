#ifndef __CSVFORMAT
#define __CSVFORMAT 1

#include "Format.h"
class CSVFormat: public Format{
public:
	CSVFormat(char * ime) {
		f.open(ime);
	}
	void dodaj(int tip, std::string a, std::string b);
	
};

#endif
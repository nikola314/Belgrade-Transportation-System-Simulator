#ifndef __CGENERATOR
#define __CGENERATOR 1

#include "Generator.h"
class CGenerator: public Generator{
public:
	CGenerator(Mreza* mm) :Generator(mm) {}
	void generisi(std::list<Linija*> l, std::vector<Stajaliste*> s);
};

#endif
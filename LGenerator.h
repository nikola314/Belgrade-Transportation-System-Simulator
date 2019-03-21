#ifndef __LGENERATOR
#define __LGENERATOR 1
#include "Generator.h"


class LGenerator: public Generator{
public:
	LGenerator(Mreza* mm) :Generator(mm) {}
	void generisi(std::list<Linija*> l, std::vector<Stajaliste*> s);
};

#endif
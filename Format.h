#ifndef __FORMAT
#define __FORMAT 1
#include<fstream>
class Format{
public:
	
	//tip== 0-> cvor ; 1->grana
	virtual void dodaj(int tip, std::string a, std::string b) = 0;
	virtual void zavrsi() { f.close(); }
protected:
	
	std::ofstream f;

};

#endif
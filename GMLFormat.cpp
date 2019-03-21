#include "GMLFormat.h"
#include<fstream>
#include<string>
#include"linija.h"
using namespace std;
void GMLFormat::dodaj(int tip, std::string a, std::string b)
{	
	f << "edge\n[\nsource " << a << "\ntarget " << b << "\n]\n";
	
}
void GMLFormat::zavrsi() {
	f << "]";
}

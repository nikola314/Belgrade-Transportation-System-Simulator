#include "CSVFormat.h"
#include<fstream>
#include<string>
using namespace std;
void CSVFormat::dodaj(int tip, std::string a, std::string b)
{
	f << a << ";" << b << endl;
}



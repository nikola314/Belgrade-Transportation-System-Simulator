#include"Mreza.h"

using namespace std;

int main() {
	Mreza * m = new Mreza();
	m->ucitajLinije();
	m->ucitajStajalista();
	cout << "Ucitano..\n";
	//test
	/*cout << "sve 4: " << m->ukupnoLinija() << " - " << m->ukupnoStajalista() << endl;
	system("pause");
	m->filtriraj(3);
	cout << "u prve 3: " << m->ukupnoLinija() << " - " << m->ukupnoStajalista() << endl;
	system("pause");
	m->filtriraj(2);
	cout << "u prve 2: " << m->ukupnoLinija() << " - " << m->ukupnoStajalista() << endl;
	system("pause");*/
	//m->filtriraj(1);
	//cout << "u prvoj: " << m->ukupnoLinija() << " - " << m->ukupnoStajalista() << endl;
	//system("pause");
	m->testNajkraciPut();
	//m->napraviGraf();
	//m->zajednicka();
	system("pause");
	//cout << *m;
	return 0;
}
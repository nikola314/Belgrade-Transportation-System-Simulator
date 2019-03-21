#ifndef __LOKACIJA
#define __LOKACIJA 1
#include<iostream>
using std::ostream;
struct Lokacija {
	double x;
	double y;
	Lokacija(double _x = 0, double _y = 0) {
		x = _x; y = _y;
	}
	double razdaljina(Lokacija l) {
		return
			sqrt((x - l.x)*(x - l.x) + (y - l.y)*(y - l.y));
	}
	friend ostream& operator<<(ostream& it, Lokacija& l);
};

#endif
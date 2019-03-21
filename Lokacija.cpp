#include "Lokacija.h"

ostream & operator<<(ostream & it, Lokacija & l)
{
	return it <<  l.x << " " << l.y;
}

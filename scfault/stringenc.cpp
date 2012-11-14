#include <string>
#include <cstring>
using std::string;

#include "stringenc.h"

string strtolower(string s)
{
	string t = s;
	int i = -1;
	while(t[i++])
	{
		t[i] = tolower(t[i]);
	}
	return t;
}


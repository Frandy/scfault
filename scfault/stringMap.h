#ifndef STRING_MAP_H
#define STRING_MAP_H

#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

unsigned int myJSHash(const char *str);
unsigned int myBKDRHash(const char *str);

class StringHash
{
	public:
		size_t operator()(const string& s) const 
		{
			return myBKDRHash(s.c_str());
		}
};

class StringCompare
{
	public:
		bool operator()(const string& a,const string& b) const 
		{
			return (a==b);
		}
};

typedef unordered_map<string,int,StringHash,StringCompare> StringMap;


#endif

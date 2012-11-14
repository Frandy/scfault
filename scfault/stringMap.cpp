#include "stringMap.h"

unsigned int myJSHash(const char *str)
{
	unsigned int hash = 1315423911;     
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}         
	return (hash & 0x7FFFFFFF);
}

unsigned int myBKDRHash(const char* str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0; 
		
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
 
	return (hash & 0x7FFFFFFF);
}

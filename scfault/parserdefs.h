#ifndef PARSERDEFS_H
#define PARSERDEFS_H

struct mytoken{
	double d;
	char *s;
	int paramflag;
};

typedef struct mytoken mytoken_t;

int myparser(const char filename[]);

#endif

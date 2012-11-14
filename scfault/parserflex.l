%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserdefs.h"
#include "parserbison.hpp"
int linenum = 1;

double myatof(char *s){
	double a = atof(s);
	int c = strlen(s);
	double b = 1.0;
	char unit = s[c-1];
	switch(unit){
		case 'f': b = 1e-15; break;
		case 'p': b = 1e-12; break;
		case 'P': b = 1e-12; break;
		case 'n': b = 1e-9;  break;
		case 'u': b = 1e-6;  break;
		case 'm': b = 1e-3;  break;
		case 'k': b = 1e3;   break;
		case 'K': b = 1e3;   break;
		case 'M': b = 1e6;   break;
		case 'x': b = 1e6;   break;
		case 'g': b = 1e9;   break;
		default: b = 1.0;
	}
	return a*b;
}

void saveAsNum(){
	double a = myatof(yytext);
	int c = strlen(yytext);
	yylval.token = (mytoken_t*)malloc(sizeof(mytoken_t));
	char *newstr = (char*)malloc(sizeof(char)*(c+1));
	strcpy(newstr,yytext);
	newstr[c] = '\0';
	yylval.token->s = newstr;
	yylval.token->d = a;
	yylval.token->paramflag = 0;
}

void saveAsText(){
	yylval.token = (mytoken_t*)malloc(sizeof(mytoken_t));
	int len = strlen(yytext);
	char *newstr = (char*)malloc(sizeof(char)*(len+1));
	strcpy(newstr,yytext);
	newstr[len] = '\0';
	yylval.token->s = newstr;
	yylval.token->paramflag = 1;
}

%}

%option outfile="parserflex.cpp"
%option noyywrap

%x comment

INF		[-+]?((inf)|(INF))
DIGIT 	[0-9]
NAME  	[_a-zA-Z0-9]+
SIGN	[-+]
EXP		[eE][-+]?[0-9]+
INT		[-+]?[0-9]+
REAL	[-+]?([0-9]+)([.]([0-9]+))?([eE][-+]?([0-9]+))?
UNIT	[f|p|P|n|u|m|k|K|M|x|g]
SPACE   [ \t]+

%%

^[r|R]{NAME}?	{
		//printf("return a r name\n");
		saveAsText();
		return RID;
	}

^[c|C]{NAME}?	{
		//printf("return a c name\n");
		saveAsText();
		return CID;
	}

^[l|L]{NAME}?	{
		//printf("return a l name\n");
		saveAsText();
		return LID;
	}

^[v|V]{NAME}?	{
		//printf("return a v name\n");
		saveAsText();
		return VID;
	}

^[i|I]{NAME}?	{
		saveAsText();
		return IID;
	}

^[e|E]{NAME}?	{
		saveAsText();
		return EID;
	}

^[f|F]{NAME}?	{
		saveAsText();
		return FID;
	}

^[g|G]{NAME}?	{
		saveAsText();
		return GID;
	}

^[h|H]{NAME}?	{
		saveAsText();
		return HID;
	}

^[x|X]{NAME}?	{
		saveAsText();
		return XID;
	}

^[s|S]{NAME}?	{
		saveAsText();
		return SID;
}

"opamp"|"OPAMP"	{
		return OPAMP;
	}

"phase"|"PHASE" {
	return PHASE;
}

"short"|"open"|"SHORT"|"OPEN" {
		saveAsText();
		return SHORTOPEN;
	}

"fault"|"FAULT" {
		saveAsText();
		return FAULT;
	}

"level"|"LEVEL"	{
	return LEVEL;
}

"="	{
//	printf("equal\n");
	return EQUAL;
}

("+"|"-")?("INF"|"inf")	{
	saveAsText();
	printf("return INF");
	return INF;
	}


".title"|".TITLE"	{
		//printf("return dot title\n");
		return DOTTITLE;
	}

".op"|".OP"		{
		//printf("return dot op\n");
		return DOTOP;
	}


".print"|".PRINT"	{
		//printf("return dot print\n");
		return DOTPRINT;
	}

".dc"|".DC"		{
		//printf("return dot dc\n");
		return DOTDC;
	}

".tran"|".TRAN"	{
		//printf("return dot tran\n");
		return DOTTRAN;
	}

".ac"|".AC"		{
		//printf("return dot ac\n");
		return DOTAC;
	}

".pz"|".PZ"		{
		//printf("return dot pz\n");
		return DOTPZ;
	}

".DDD"|".print"|".PRINT"	{
		//printf("return dotDDD\n");
		return DOTDDD;
	}

".sc"|".SC" {
	return DOTSC;
}

".param"|".PARAM" {
	//printf("return DOTPARAM\n");
	return DOTPARAM;
}

".clock"|".CLOCK" {
	return DOTCLOCK;
}

"VOO"	{
	return VOO;	
}

"VOE"	{
	return VOE;
}

"VEO"	{
	return VEO;
}

"VEE"	{
	return VEE;
}

"dc"|"DC"		{
		//printf("return dc\n");
		return DC;
	}

"ac"|"AC"		{
		//printf("return ac\n");
		return AC;
	}

"dec"|"DEC"		{
		return DEC;
	}	

"lin"|"LIN"		{
		return LIN;
	}

{INT}{UNIT}?	{
		//printf("return num \n");
		saveAsNum();
		return NUM;
	}

{REAL}{UNIT}?	{
		//printf("return num \n");
		saveAsNum();
		return NUM;
	}

{NAME}		{
		printf("return text:%s\n",yytext);
		saveAsText();
		return TEXT;
	}

"("		{
		//printf("return OP\n");
		return OP;
	}

")"		{
		//printf("return CP\n");
		return CP;
	}

","		{
		return COMMA;
	}

{SPACE}		{
	}

[\n]		{
		//printf("line:%d,LINEEND\n",linenum);
		linenum++;
		return LINEEND;
	}

"*"		{
		BEGIN(comment);
}	

<comment>[\n] {
		linenum++;
		BEGIN(INITIAL);
	}

<comment>.*	

".end"|".END"	{
		printf("return end\n");
		yyterminate();
	}


%%

/** @file */
#include "funkcje.h"
#include "nvwa/debug_new.h"
int main(int argc,char*argv[])
{
	
	Parametr p;
	if (!Parsuj(argc,argv,p))
	{
		PrintUsage(argv[0]);
	}
	Wykonaj(p);
	return 0;
}
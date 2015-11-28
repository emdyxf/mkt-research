#include "csvreader.h"

int ReadDateCount ()
{
	int nDateCount = 0;
	ifstream fInputFile ("./../_dates.csv");
	if (!fInputFile.good())	{	printf("Error opening file!\n"); return	RET_FALSE;	}

	string sLine;
	while(!fInputFile.eof())
	{
		getline(fInputFile,sLine);
		nDateCount++;
	}
	nDateCount--;
	return nDateCount;
}

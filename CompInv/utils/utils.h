#ifndef _UTILS_H_
#define _UTILS_H_

#ifndef _COMMON_LOGGER_H_
#include "common.h"
#endif

#ifndef _COMMON_LOGGER_H_
#include "logger.h"
#endif


int Init2DArray (double mMarketData [][IDX_MAX_COL], int nNumRol, int nNumCol, double dInitValue)
{
	if (IDX_MAX_COL < nNumCol)
	{
		CERR << "Out of Bound! NumCol " << nNumCol << " greater than MaxIndex " << IDX_MAX_COL << "!" << std::endl;
		return FAILURE;
	}
	for (int i=0; i<nNumRol; i++)
	{
		for (int j=0; j<nNumCol; j++)
		{
			mMarketData[i][j] = dInitValue;
		}
	}
	return SUCCESS;
}

int PrintArrayDouble (double vArrayDouble[], int nMaxIdx)
{
	for (int i=0; i<nMaxIdx; i++)
	{
		CDEBUG << "Index #" << i << ": " <<  vArrayDouble[i] << std::endl;
	}
	return SUCCESS;
}

int Print2DArrayDouble (double mMarketData [][IDX_MAX_COL], int nNumRow, int nNumCol)
{
	for (int i=0; i<nNumRow; i++)
	{
		CDEBUG << "==== Row #" << i << " ====!" << std::endl;
		for (int j=0; j< nNumCol; j++)
		{
			CDEBUG << "Col #" << j << ": " <<  mMarketData[i][j] << std::endl;
		}
	}
	return SUCCESS;
}

#endif

#define _DEBUG_LEVEL_	(1)  // 0 - Info; 1 - Verbose; Else - Full.

#ifndef _COMMON_LOGGER_H_
#include "common.h"
#endif

#ifndef _COMMON_LOGGER_H_
#include "logger.h"
#endif

#ifndef _UTILS_H_
#include "utils.h"
#endif

#include "./utils/csvreader.h"

int ProcessMarketData ();

int CalculateEMA (double mMarketData [][IDX_MAX_COL], int nNumRol, int nNumCol, int nPeriod, int nIdxCol);

int CalculateADX (double mMarketData [][IDX_MAX_COL], int nNumRol, int nNumCol, int nPeriod, int nIdxCol);

int CalculateMid (double mMarketData [][IDX_MAX_COL], int nNumRol, int nNumCol);


int main()
{
	ProcessMarketData();

return 0;
}


int ProcessMarketData ()
{
	int nDateCount = 0;
	nDateCount = ReadDateCount();
	_LOG_VERB_(CINFO << "Total " << nDateCount << " Days!" << std::endl);

	double mMarketData [nDateCount][IDX_MAX_COL];
	Init2DArray (mMarketData, nDateCount, IDX_MAX_COL, 0.0);
	ReadCSV(mMarketData, nDateCount, IDX_MAX_COL);

	CalculateMid (mMarketData, nDateCount, IDX_MAX_COL);

	CalculateEMA (mMarketData, nDateCount, IDX_MAX_COL, 5, IDX_SEMA);
	CalculateEMA (mMarketData, nDateCount, IDX_MAX_COL, 10, IDX_MEMA);
	CalculateEMA (mMarketData, nDateCount, IDX_MAX_COL, 20, IDX_LEMA);

	CalculateADX (mMarketData, nDateCount, IDX_MAX_COL, ADX_PERIOD, IDX_ADX);


	_LOG_VERB_(Print2DArrayDouble (mMarketData, nDateCount, IDX_MAX_COL));

	return SUCCESS;
}


int CalculateMid (double mMarketData [][IDX_MAX_COL], int nNumRow, int nNumCol)
{
	if (IDX_MAX_COL < nNumCol)
	{
		CERR << "Out of Bound! NumCol " << nNumCol << " greater than IndexMaxCol " << IDX_MAX_COL << "!" << std::endl;
		return FAILURE;
	}

/*
	if (nIdxCol > IDX_MAX_COL-1)
	{
		CERR << "Out of Bound! ColIdx " << nIdxCol << " greater than IndexMaxCol-1 " << IDX_MAX_COL-1 << "!" << std::endl;
		return FAILURE;
	}
*/
	for (int i=0; i<nNumRow; i++)
	{
			mMarketData[i][IDX_MID] = (mMarketData[i][IDX_HIGH] + mMarketData[i][IDX_LOW] ) / 2.0;
	}

	return SUCCESS;
}

int CalculateEMA (double mMarketData [][IDX_MAX_COL], int nNumRow, int nNumCol, int nPeriod, int nIdxCol)
{
	_LOG_VERB_(CDEBUG << "Calculating EMA. Period = " << nPeriod << " Index = " << nIdxCol << "!" << std::endl);

	if (IDX_MAX_COL < nNumCol)
	{
		CERR << "Out of Bound! NumCol " << nNumCol << " greater than IndexMaxCol " << IDX_MAX_COL << "!" << std::endl;
		return FAILURE;
	}

	if (nIdxCol > IDX_MAX_COL-1)
	{
		CERR << "Out of Bound! ColIdx " << nIdxCol << " greater than IndexMaxCol-1 " << IDX_MAX_COL-1 << "!" << std::endl;
		return FAILURE;
	}

	if (nPeriod<5)
	{
		CERR << "Period too short! Period = " << nPeriod << "!" << std::endl;
		return FAILURE;
	}


	double dSumSMA = 0.0;
	for (int i=0; i<nPeriod; i++)
	{
		dSumSMA += mMarketData[i][IDX_CLOSE];
	}
	for (int i=0; i<nPeriod; i++)
	{
		mMarketData[i][nIdxCol] = dSumSMA / (nPeriod*1.0);
	}

	double dMultiplier = 0.0;
	dMultiplier = (2.0 / ((nPeriod+1)*1.0));

	for (int i=nPeriod; i<nNumRow; i++)
	{
		mMarketData[i][nIdxCol] = (mMarketData[i][IDX_CLOSE] - mMarketData[i-1][nIdxCol]) * dMultiplier * 1.0 + mMarketData[i-1][nIdxCol];
	}

	return SUCCESS;

}

int CalculateADX (double mMarketData [][IDX_MAX_COL], int nNumRow, int nNumCol, int nPeriod, int nIdxCol)
{
	double vTrueRange[nNumRow];
	double vAvgTrueRange[nNumRow];
	double vPosDM [nNumRow];
	double vNegDM [nNumRow];

	if (IDX_MAX_COL < nNumCol)
	{
		CERR << "Out of Bound! NumCol " << nNumCol << " greater than IndexMaxCol " << IDX_MAX_COL << "!" << std::endl;
		return FAILURE;
	}

	if (nIdxCol > IDX_MAX_COL-1)
	{
		CERR << "Out of Bound! ColIdx " << nIdxCol << " greater than IndexMaxCol-1 " << IDX_MAX_COL-1 << "!" << std::endl;
		return FAILURE;
	}

	//Method 1: Current High less the current Low
	//Method 2: Current High less the previous Close (absolute value)
	//Method 3: Current Low less the previous Close (absolute value)
	vTrueRange[0] = mMarketData [0][IDX_HIGH] - mMarketData [0][IDX_LOW];

	for (int i=1; i<nNumRow; i++)
	{
		double dTrueRange = 0.0;
		dTrueRange = max((max((mMarketData[i][IDX_HIGH]-mMarketData [i][IDX_LOW]), fabs(mMarketData[i][IDX_HIGH]-mMarketData[i-1][IDX_CLOSE]))),
						fabs(mMarketData[i][IDX_LOW]-mMarketData[i-1][IDX_CLOSE]));
		vTrueRange[i] = dTrueRange;
	}
	_LOG_DBUG_(PrintArrayDouble(vTrueRange, nNumRow));

	double dSumTR = 0.0;
	for (int i=0; i<nPeriod; i++)
	{
		dSumTR += vTrueRange[i];
	}
	for (int i=0; i<nPeriod; i++)
	{
		vAvgTrueRange[i] = dSumTR / (nPeriod * 1.0);
	}

	for (int i=nPeriod; i<nNumRow; i++)
	{
		vAvgTrueRange[i] = (vAvgTrueRange[i-1] * (nPeriod-1) * 1.0 + vTrueRange[i]) / (nPeriod * 1.0);
	}
	_LOG_DBUG_(PrintArrayDouble(vAvgTrueRange, nNumRow));


	for (int j=0; j<nNumRow; j++)
	{
		mMarketData[j][nIdxCol] = vAvgTrueRange[j];
	}

	vPosDM [0] = 0.0;
	vNegDM [0] = 0.0;
	mMarketData[0][nIdxCol] = 0.0;

	for (int i=1; i<nNumRow; i++)
	{
		_LOG_DBUG_(CDEBUG << "Idx = " << i
							<< ": Curr High = " << mMarketData[i][IDX_HIGH]
							<< ": Prev High = " << mMarketData[i-1][IDX_HIGH]
							<< ": Curr Low = " << mMarketData[i][IDX_LOW]
							<< ": Prev Low = " << mMarketData[i-1][IDX_LOW]
							<< std::endl);

		if ((mMarketData[i][IDX_HIGH]-mMarketData[i-1][IDX_HIGH]) - (mMarketData[i-1][IDX_LOW]-mMarketData[i][IDX_LOW]) > g_dEpsilon)
		{
			vPosDM[i] = max((mMarketData[i][IDX_HIGH]-mMarketData[i-1][IDX_HIGH]), 0.0);
			vNegDM[i] = 0.0;

			if (vPosDM[i] > g_dEpsilon)
			{
				mMarketData[i][nIdxCol] = vPosDM[i] + 2.0 * g_dEpsilon;
			}
			else
			{
				mMarketData[i][nIdxCol] = mMarketData[i-1][nIdxCol];
			}

			_LOG_DBUG_(CDEBUG << "Idx = " << i
										<< ": +DM! -> Pos DM = " << vPosDM[i]
										<< ": Neg DM = " << vNegDM[i]
										<< std::endl);
		}
		else
		{
			vNegDM[i] = max((mMarketData[i-1][IDX_LOW]-mMarketData[i][IDX_LOW]), 0.0);
			vPosDM[i] = 0;

			if (vNegDM[i] > g_dEpsilon)
			{
				mMarketData[i][nIdxCol]= - vNegDM[i] - 2.0 * g_dEpsilon;
			}
			else
			{
				mMarketData[i][nIdxCol] = mMarketData[i-1][nIdxCol];
			}

			_LOG_DBUG_(CDEBUG << "Idx = " << i
										<< ": -DM! -> Pos DM = " << vPosDM[i]
										<< ": Neg DM = " << vNegDM[i]
										<< std::endl);
		}
	}

	return SUCCESS;
}


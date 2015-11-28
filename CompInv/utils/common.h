#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <string>
#include <locale>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

#define 	SUCCESS		1
#define		FAILURE		0


//#define	IDX_SYM		0
//#define	IDX_DATE	1
#define IDX_OPEN	0
#define IDX_HIGH	1
#define	IDX_LOW		2
#define IDX_CLOSE	3
#define	IDX_VOL		4
#define IDX_ADJ		5
#define IDX_MID		6
#define IDX_SEMA	7
#define IDX_MEMA	8
#define IDX_LEMA	9
#define IDX_ADX		10
#define IDX_HIGHX	11
#define IDX_LOWX	12

#define IDX_MAX_COL		IDX_LOWX+1	// Maximum IDX+1
#define IDX_OFFSET	2

#define ADX_PERIOD	14

#define g_dEpsilon	0.00001

#endif

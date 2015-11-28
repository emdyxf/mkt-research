#ifndef _COMMON_LOGGER_H_
#define _COMMON_LOGGER_H_

#ifndef _COMMON_LOGGER_H_
#include "common.h"
#endif

#if (_DEBUG_LEVEL_ == 0 )			// 0 - Info
	#define _LOG_INFO_(a)	a
	#define _LOG_VERB_(a)
	#define _LOG_DBUG_(a)
#else
	#if	(_DEBUG_LEVEL_ == 1 )		// 1 - Verbose
		#define _LOG_INFO_(a)	a
		#define _LOG_VERB_(a)	a
		#define _LOG_DBUG_(a)
	#else								// Else - Full
		#define _LOG_INFO_(a)	a
		#define _LOG_VERB_(a)	a
		#define _LOG_DBUG_(a)	a
	#endif
#endif

#define CERR	cout << "[ERROR] [" << setw(10) << __func__ << "::" << setw(4) << __LINE__ << "] "
#define CWARN	cout << "[WARN] [" << setw(10) << __func__ << "::" << setw(4) << __LINE__ << "] "
#define CINFO	cout << "[INFO] [" << setw(10) << __func__ << "::" << setw(4) << __LINE__ << "] "
#define CDEBUG	cout << "[DEBUG] [" << setw(10) << __func__ << "::" << setw(4) << __LINE__ << "] "

#endif // #ifndef _COMMON_LOGGER_H_

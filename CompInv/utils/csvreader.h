#ifndef _COMMON_LOGGER_H_
#include "common.h"
#endif

#ifndef _COMMON_LOGGER_H_
#include "logger.h"
#endif

#include "csv_parser.hpp"

int ReadDateCount ()
{
	int nDateCount = 0;
	ifstream fInputFile ("./../GE.csv");
	if (!fInputFile.good())	{CERR << "Error opening file!" << std::endl;	return	FAILURE;}

	string sLine;
	while(!fInputFile.eof())
	{
		getline(fInputFile,sLine);
		nDateCount++;
	}
	nDateCount--;

	// minus 1 line for header
	return nDateCount-1;
}

void ReadCSV(double mMarketData [][IDX_MAX_COL], int nNumDate, int nNumTick)
{
//	printf("\n\n\n\n\n\n\n\n\n\n\n Hello Panda!\n\n\n\n\n\n\n\n\n");
//	int nDateCount = 0;
//	nDateCount = ReadDateCount();

//	printf("%d\n\n",nDateCount);
	ifstream fInputFile ("./../GE.csv");
	if (!fInputFile.good())	{CERR << "Error opening file!" << std::endl; return;}


	csv_parser file_parser;

    const char field_terminator = ',';
    const char line_terminator  = '\n';
    const char enclosure_char   = '"';
    const char * filename =  "./../GE.csv";

	file_parser.set_skip_lines(1);
    file_parser.init(filename);
    file_parser.set_enclosed_char(enclosure_char, ENCLOSURE_OPTIONAL);
    file_parser.set_field_term_char(field_terminator);
    file_parser.set_line_term_char(line_terminator);

    int row_count = 1;

	while(file_parser.has_more_rows())
	{
		if (row_count > nNumDate)
		{
			printf("ERROR: Row count %d greater than number of days %d!", row_count, nNumDate);
			//CERR << "Row count " << row_count << "greater than number of days" <<  nNumDate << std::endl;
		}
		unsigned int i = 0;

		/* Get the record */
		csv_row row = file_parser.get_row();

		/* Print out each column in the row */
		for (i = 0; i < row.size(); i++)
		{

			_LOG_DBUG_(printf("COLUMN %02d : %s\n", i + 1U, row[i].c_str()));

			if ( i>1 )
			{
				_LOG_DBUG_(printf("Writing %02f to Matrix Row#%02d Col#%02d!\n", atof(row[i].c_str()), nNumDate-row_count, i-IDX_OFFSET));
				mMarketData[nNumDate-row_count][i-IDX_OFFSET] = atof(row[i].c_str());
			}
		}

		_LOG_DBUG_(printf("====================================================================\n"));
		_LOG_DBUG_(printf("END OF ROW %02d\n", row_count));
		_LOG_DBUG_(printf("====================================================================\n"));

		row_count++;

	}
}

#include "LogFile.h"

const char * FILE_NAME = "logfile.log";

void createLog()
{
	//creating file for writting and reading
	//re-directing out-stream to file
    freopen(FILE_NAME, "w+", stderr);
};

void openLog()
{
	//opening file for writting and reading
	//if doesn't exist yet, create new
	//if does, start from the last record
    freopen(FILE_NAME, "a+", stderr);
};

void closeLog()
{
	fclose(stderr);
};

void writeLog(const string& line)
{
	openLog();
	const char * cline = line.c_str();
    fflush(stderr);
    fprintf(stderr,cline);
    fprintf(stderr, "\n");
	closeLog();
};

void writeLog(const string& card, const string& date, const string& action,
			  const string& sum, const string& state)
{
    openLog();
	char * separator = " : ";
	const char * ccard = card.c_str();//+separator;
	const char * cdate = date.c_str();
	const char * caction = action.c_str();
	const char * csum = sum.c_str();
	const char * cstate = state.c_str();
    fflush(stderr);
	fprintf(stderr, ccard);
	fprintf(stderr, separator);
	fprintf(stderr, cdate);
	fprintf(stderr, separator);
	fprintf(stderr, caction);
	fprintf(stderr, separator);
	fprintf(stderr, csum);
	fprintf(stderr, separator);
	fprintf(stderr, cstate);
    fprintf(stderr, "\n");
	closeLog();
};

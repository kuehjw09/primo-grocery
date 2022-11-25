#include "../include/project_helper.h"

#include <ctime>
#include <time.h>

using namespace std;

const std::string getDateString()
{
	time_t     now = time(0);
	struct tm  tstruct;
	localtime_r(&now, &tstruct);
	return std::string(std::to_string(tstruct.tm_mon+1)+"/"+ std::to_string(tstruct.tm_mday)+"/" + std::to_string(tstruct.tm_year+1900));
}

const std::string getTimeString()
{
	time_t     now = time(0);
	struct tm  tstruct;
	localtime_r(&now, &tstruct);
	return std::string(std::to_string(tstruct.tm_hour) + ":" + std::to_string(tstruct.tm_min) + ":" + std::to_string(tstruct.tm_sec));
}

void clearConsole() {
#ifdef WIN32
#include <windows.h>
	system("cls");
#else
	system("clear");
#endif
}
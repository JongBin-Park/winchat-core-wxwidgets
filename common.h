#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#define LOG_FILE_NAME "log.txt"

void log(string);
string getTime();

#endif // __COMMON_H__

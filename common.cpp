#include "common.h"

using namespace std;

void log(string contents)
{
    string logContents = getTime() + " : " + contents;
    ofstream log;

    log.open( LOG_FILE_NAME, std::ios::app );

    if ( log.is_open() )
    {
        log.write( (logContents + "\n").c_str(), logContents.size() + 1 );
        log.close();
    }

    return;
}

string getTime()
{
    string currentTime;

    int totalSeconds = time(NULL);
    int currentSecond = totalSeconds % 60;
    int totalMinutes = totalSeconds / 60;
    int currentMinute = totalMinutes & 60;
    int totalHours = totalMinutes / 60;
    int currentHour = totalHours % 24 + 9 > 24 ? totalHours % 24 - 15 : totalHours % 24 + 9;

    currentTime = to_string(currentHour) + ":";
    currentTime += to_string(currentMinute) + ":";
    currentTime += to_string(currentSecond);

    return currentTime;
}

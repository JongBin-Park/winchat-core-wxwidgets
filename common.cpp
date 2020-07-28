#include "common.h"

using namespace std;

void log(string contents)
{
    ofstream log;

    log.open( "log.txt", ios::app );

    if ( log.is_open() )
    {
        string logContents = getCurrentTime() + " - " + contents + "\n";
        log.write( logContents.c_str(), logContents.size() + 1 );
        cout << logContents;
        log.close();
    }

    return;
}

string getCurrentTime()
{
    string result = "";

    int totalSeconds = time(NULL);
    int currentSecond = totalSeconds % 60;
    int totalMinutes = totalSeconds / 60;
    int currentMinute = totalMinutes % 60;
    int totalHours = totalMinutes / 60;
    int currentHour = totalHours % 24;

    if ( currentHour > 24 )
    {
        currentHour -= 15;
    }
    else
    {
        currentHour += 9;
    }

    result += to_string(currentHour) + ":";
    result += to_string(currentMinute) + ":";
    result += to_string(currentSecond);

    return result;
}

#include <stdio.h>    //printf(3)
#include <stdlib.h>   //exit(3)
#include <unistd.h>   //fork(3), chdir(3), sysconf(3)
#include <signal.h>   //signal(3)
#include <sys/stat.h> //umask(3)
#include <syslog.h>   //syslog(3), openlog(3), closelog(3)
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#define MAXHOSTNAME 256
#define DESTURL "https://wttr.in/"
#define DESTURLEND "?format=3"
using namespace std;

const char* offices[] = {
    "Brisbane",
    "Canberra",
    "Melbourne",
    "Perth",
    "Sydney",
    "Beijing",
    "Shanghai",
    "Shenzhen",
    "Hong Kong",
    "Bangalore",
    "New%20Delhi",
    "Kolkata",
    "Mumbai",
    "Pune",
    "Jakarta",
    "Tokyo",
    "Nagoya",
    "Osaka",
    "Fukuoka",
    "Seoul",
    "Kuala%20Lumpur",
    "Auckland",
    "Wellington",
    "Makati%20City",
    "Singapore",
    "Taipei",
    "Bangkok",
    "London",
    "Amsterdam",
    "Barcelona",
    "Berlin",
    "Brno",
    "Brussels",
    "Copenhagen",
    "Berlin",
    "Cork",
    "Dublin",
    "Düsseldorf",
    "Farnborough",
    "Frankfurt%20am%20Main",
    "Helsinki",
    "Madrid",
    "Milan",
    "Moscow",
    "Grasbrunn",
    "Neuchâtel",
    "Newcastle%20Upon%20Tyne",
    "Oslo",
    "Prague",
    "Puteaux",
    "Rome",
    "Stockholm",
    "Stuttgart",
    "Cherkasy",
    "Vienna",
    "Warsaw",
    "Waterford",
    "Zürich",
    "Dubai",
    "İstanbul",
    "Ra’anana",
    "Riyadh",
    "Sandton",
    "Buenos%20Aires",
    "Brasília",
    "Fortaleza",
    "Rio%20de%20Janeiro",
    "São%20Paulo",
    "Santiago",
    "Bogota",
    "Ciudad%20de%20México",
    "Monterrey",
    "Lima",
    "Montreal",
    "Toronto",
    "Raleigh",
    "Boston",
    "Ann%20Arbor",
    "Atlanta",
    "Washington",
    "North Charleston",
    "Charlotte",
    "Chicago",
    "San%20Francisco",
    "New%20York",
    "Dallas",
    "Denver",
    "Durham",
    "Huntsville",
    "Los%20Angeles",
    "Mahwah",
    "Minneapolis",
    "Richmond",
    "St.%20Louis",
    "Sunnyvale",
    "McLean",
    "Westford",
    NULL };

int curlUrl( const char* myOffice, size_t myUrlLength )
{
    std::string fullUrl;
    CURL *curl;
    CURLcode res;

    // create a URL from 2 constants and an office string
    fullUrl.append( DESTURL );
    fullUrl.append( myOffice );
    fullUrl.append( DESTURLEND );
    // make a C string of the same size and copy to it
    int fullUrlSize = fullUrl.length();
    char charFullArray[ fullUrlSize + 1 ];
    strcpy( charFullArray,  fullUrl.c_str() );

    // setup curl, grab the combined URL, and clean up
    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, charFullArray);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return res;
} 

int main(int argc, char** argv)
{
    int ttl=999999;
    int delay=10;

    pid_t pid = 0;

    if (argc > 1)
        pid = fork();

    if (pid == 0)
    {
        // child process
        openlog("testapp",LOG_PID,LOG_DAEMON);

        // iterate over the list of Red Hat offices and get the weather for each
        for ( int i=0; offices[i] != NULL; i++ )
        {
            curlUrl( offices[i], sizeof(offices[i]) );
            sleep(delay);
        }

        syslog(LOG_NOTICE,"testapp child process ended");
        closelog();
        return(EXIT_SUCCESS);
    }
    if (pid > 0)
    {
        // parent process
        string filename = "/var/run/testapp.pid";
        ofstream o(filename.c_str());
        o << pid << endl;

        ifstream meminfo;
        meminfo.open("/proc/meminfo");
        meminfo.close();

        openlog("testapp",LOG_PID,LOG_DAEMON);

        /* disabling this due to startup timeout
        do
        {
            syslog(LOG_NOTICE,"daemon ttl %d",ttl);
            sleep(delay);
            ttl-=delay;
        } while ( ttl > 0 );
        syslog(LOG_NOTICE,"daemon ttl expired");*/

        syslog(LOG_NOTICE,"testapp parent process ended");
        closelog();
        return(EXIT_SUCCESS);
    }
}

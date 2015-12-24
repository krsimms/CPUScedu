#include <iostream>
#include <string>
#include "Job.h"
#include "CPUScheduler.h"
using namespace std;

int main()
{
	
    string filename;
    cout << "Enter the job file name (example file is called jobs.txt): ";
    cin >> filename;

    int timeSlice, loadDelay;
    cout << "Enter the load delay and time slice length: ";
    cin >> loadDelay >> timeSlice;
    cout << endl;

    CPUScheduler timeshare(filename, loadDelay, timeSlice);

    while (timeshare.jobsRemaining())
	{
        timeshare.execute();
    }
	
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();

return 0;

}

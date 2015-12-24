#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <queue>
#include "Job.h"
#include "CPUScheduler.h"
using namespace std;

// PRECONDITIONs: filename contains job data, delay >= 0, slice > 0
// POSTCONDITIONs: constructs a CPUScheduler with specified load delay and time slice
CPUScheduler::CPUScheduler(string filename, int delay, int slice)
{
    timeSlice = slice;
    loadDelay = delay;

    sliceTimeRemaining = timeSlice;
    loadTimeRemaining = loadDelay;

    currentTime = 0;

    ifstream jobFile(filename.c_str());
    if (!jobFile) {
        cout << "File not found." << endl;
       exit(1);
    }

    Job nextJob;
    while (nextJob.read(jobFile)) {
        readyQueue.push(nextJob);
    }

    jobFile.close();
}

// Gets true if any jobs remaining in the readyQueue
bool CPUScheduler::jobsRemaining() const
{
    return (readyQueue.size() > 0);
}

// POSTCONDITION: performs one CPU cycle, either loading the next job or executing the current job
void CPUScheduler::execute()
{
    currentTime++;                                         
    
    if (!readyQueue.empty()) {                              
        Job & currentJob = readyQueue.front();              

        if (loadTimeRemaining > 0) {                        
            if (loadTimeRemaining == loadDelay) {
                cout << setw(4) << currentTime << ":   LOAD JOB " << currentJob.getID() 
                     << " (delay = " << loadDelay << ")" << endl;
            }
            loadTimeRemaining--;
        }
        else {                                              
            if (sliceTimeRemaining == timeSlice) {         
                cout << setw(4) << currentTime << ":     START JOB " << currentJob.getID() 
                     << " (time remaining = " << currentJob.getRemainingTime() << ")" << endl;
            }

            JobStatus status = currentJob.execute();        
            sliceTimeRemaining--;                           

            if (status == DONE) {                          
                cout << setw(4) << currentTime+1 << ":       FINISH JOB " 
                     << currentJob.getID() << endl;
                readyQueue.pop();                           
                sliceTimeRemaining = timeSlice;             
                loadTimeRemaining = loadDelay;

            }
            else if (sliceTimeRemaining == 0) {             
                cout << setw(4) << currentTime+1 << ":       TIMEOUT JOB " 
                     << currentJob.getID() << endl;
                Job readyJob = currentJob;
                readyQueue.pop();                          
                readyQueue.push(readyJob);
                sliceTimeRemaining = timeSlice;            
                if (readyQueue.size() > 1) {               
                    loadTimeRemaining = loadDelay;         
                }
            }
        }
    }	
}



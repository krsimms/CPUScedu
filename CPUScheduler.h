#ifndef _CPU_SCHEDULER_
#define _CPU_SCHEDULER_

#include <string>
#include <queue>
#include "Job.h"
using namespace std;

class CPUScheduler 
{
  public:
    CPUScheduler(string filename, int delay, int slice);  // constructor
    bool jobsRemaining() const;                // Returns true if jobs in either queue 
    void execute();                            // Excecutes current job, update queue
  private:
    queue<Job> readyQueue;                     // Jobs ready to be excecuted
    int timeSlice, loadDelay;                  // Lengths of Time slice, loading
    int sliceTimeRemaining, loadTimeRemaining; // Time remaining in job slice, loading                      
    int currentTime;
};

#endif

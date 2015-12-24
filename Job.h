#ifndef _JOB_
#define _JOB_

#include <iostream>
using namespace std;

enum JobStatus {OK, DONE};

class Job                           
{                                   
  public:
    Job(int id = 0, int len = 0);   // constructor

    bool read(istream & istr);      // reads job data from an input stream
    int getID() const;              // Gets the id number of the job
    int getJobLength() const;       // Get the length of the job
    int getRemainingTime() const;   // Get time remaining to execute
    JobStatus execute();            // executes the job, returning its status (OK or DONE)

  private:
    int jobID;                      
    int jobLength;
    int timeRemaining;              
};

#endif

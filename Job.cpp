#include "Job.h"

// PRECONDITIONs: id is unique, len >= 0
// POSTCONDITIONs: constructs a job object, initializes executedSoFar to 0
Job::Job(int id, int len)
{
    jobID = id;
    jobLength = len;    
    timeRemaining = jobLength;
}

// PRECONDITIONs: istr contains job data
// Returns: true if successfully read job data from istr, else false
bool Job::read(istream & istr)
{
    istr >> jobID >> jobLength;
    timeRemaining = jobLength;
    return istr;
}

// Gets ID number of the job
int Job::getID() const
{
    return jobID;
}

// Gets length of the job
int Job::getJobLength() const
{
    return jobLength;
}

// Gets time remaining to be executed
int Job::getRemainingTime() const
{
    return timeRemaining;
}

// PRECONDITIONs: job is not done yet (timeRemaining > 0)
// Returns: status (OK or DONE) after executing the job for a cycle
JobStatus Job::execute()
{
    timeRemaining--;

    if (timeRemaining <= 0) {
        return DONE;
    }
    else {
        return OK;
    }
}

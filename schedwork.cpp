#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, 
            size_t maxShifts, DailySchedule& shed, vector<size_t>& shiftsUsed, 
            size_t day, size_t slot, size_t k);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    
    size_t n = avail.size();
    size_t k = avail[0].size();
    vector<size_t> shiftsUsed(k, 0);
    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));
                                                     // day, slot in day
    return backtrack(avail, dailyNeed, maxShifts, sched, shiftsUsed, 0, 0, k);

}

bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, 
            size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsUsed, 
            size_t day, size_t slot, size_t k) 
{

    // base case: last day AND all slots filled
    if (day == sched.size()) {
        return true;
    }

    // go to nxt day
    if (slot == dailyNeed) {
        return backtrack(avail, dailyNeed, maxShifts, sched, shiftsUsed, day + 1, 0, k);
    }

    // try all workers for this day 
    for (size_t w = 0; w < k; w++) {
        if(!avail[day][w]) continue;

        if (shiftsUsed[w] >= maxShifts) continue; 

        // choose worker
        sched[day][slot] = w;

        shiftsUsed[w]++;

        if (backtrack(avail, dailyNeed, maxShifts, sched, shiftsUsed, day, slot + 1, k)) return true;

        // undo
        shiftsUsed[w]--;
        sched[day][slot] = INVALID_ID;
    }

    return false;
}
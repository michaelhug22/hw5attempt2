#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif


// add or remove necessary headers as you please
#include "schedwork.h"


using namespace std;


// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;




// Add prototypes for any helper functions here
bool backtrack(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, std::vector<std::vector<Worker_T>>& sched, std::vector<Worker_T>& workerShifts, size_t day);


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
    const size_t n = avail.size();
    const size_t k = avail[0].size();
    if (dailyNeed > k || dailyNeed > maxShifts) return false;


    // Initialize empty daily schedule matrix
    sched.resize(n);
    for (size_t i = 0; i < n; ++i) {
        sched[i].resize(dailyNeed);
    }


    // Backtracking algorithm to find valid daily schedule matrix
    std::vector<Worker_T> workerShifts(k);
    return backtrack(avail, dailyNeed, maxShifts, sched, workerShifts, 0);
   
}


bool backtrack(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, std::vector<std::vector<Worker_T>>& sched, std::vector<Worker_T>& workerShifts, size_t day) {
    const size_t n = avail.size();
    const size_t k = avail[0].size();
    if (dailyNeed > k || dailyNeed > maxShifts) return false;


    if (day == n) return true; // All days complete


    std::vector<Worker_T> scheduled;
    for (size_t j = 0; j < k; ++j) {
        if (avail[day][j] && workerShifts[j] < maxShifts) {
            scheduled.push_back(j);
            ++workerShifts[j];
            if (scheduled.size() == dailyNeed) break;
        }
    }
    if (scheduled.size() != dailyNeed) {
        // Backtrack by removing last scheduled worker and trying the next one
        while (!scheduled.empty()) {
            const Worker_T lastWorker = scheduled.back();
            scheduled.pop_back();
            --workerShifts[lastWorker];
            if (backtrack(avail, dailyNeed, maxShifts, sched, workerShifts, day - 1)) {
                // A valid schedule has been found
                scheduled.push_back(lastWorker);
                ++workerShifts[lastWorker];
                break;
            }
        }
        if (scheduled.empty()) return false; // No valid schedule exists
    }
    sched[day] = scheduled;
    return backtrack(avail, dailyNeed, maxShifts, sched, workerShifts, day + 1);
}

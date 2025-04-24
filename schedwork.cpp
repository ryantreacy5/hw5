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
//static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
// ok we will add a prototype to have the recursive function that fills in the schedule and does the backtracking
//void fill
bool fillIn(size_t day, size_t slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, std::vector<int>& worked, DailySchedule& sched);

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
    // need to store the number of days and the number of workers we have and base it on the input matrix
    size_t daysCount = avail.size();
    size_t workerCount = avail[0].size();
  // initialize sched to have the a row count that is the number of days and start them with an empty vector that we put workers into 
    sched = DailySchedule(daysCount, std::vector<Worker_T>());
  // create a vector to track how many shifts each worker has been assigned , where worked[i] stores the # of shifts for worker i
    std::vector<int>worked(workerCount, 0);
  // call recursiviley starting with day 0, slot 0 which is the first worker to assign on the first day
    return fillIn(0,0,avail,dailyNeed, maxShifts, worked, sched);
}

// implement 
bool fillIn(size_t day, size_t slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, std::vector<int>& worked, DailySchedule& sched)
{
  // base case will be if the schedle is filled
  if(day == sched.size())
  {
    return true;
  }

  // for a slot check every worker
  for(size_t worker = 0; worker<avail[0].size(); ++worker)
  {
    // need to check three things to assign: if theyre available that day, if they havent hit max shifts, and if theyr enot already scheduled 
    if(avail[day][worker] && worked[worker] < (int)maxShifts && find(sched[day].begin(), sched[day].end(), worker) == sched[day].end())
    {
      sched[day].push_back(worker); // temporarily assigns the worker to the schedule
      worked[worker]++; // updates the shift count

      size_t nextDay = day;
      //size_t nextWorker = 
      size_t nextSlot = slot+1;

      if(nextSlot == dailyNeed) // if we have filled the daily needs of workers for the current day, we move to the next day and reset it to 0
      {
        nextDay++;
        nextSlot = 0;
      }
      if(fillIn(nextDay, nextSlot, avail, dailyNeed, maxShifts, worked, sched)) // recursivley fill the rest of the schedule 
      {
        return true; // true!
      }
      sched[day].pop_back(); // if the recursion fails, call backtrack removing the worker from the current day and decrementing their shift count 
      worked[worker]--;
    }
  }
  return false; // further backtracking
}


#ifndef EXITBARRIER_HPP_
#define EXITBARRIER_HPP_
#include "Barrier.hpp"

class ExitBarrier : public Barrier {
   public:
    ExitBarrier() : up_(false), exitSPtr_(&EntranceBarrier::carTimeInfo_) {}

    void raise(string info = "") {
        if(info.empty()) { 
            up_ = true;
            return;
        }

        pair<clock_t, clock_t> curTimes = exitSPtr_->at(info);
        clock_t startTime = curTimes.first;
        clock_t endTime = curTimes.second;
        endTime = clock();
        (*exitSPtr_)[info].second = endTime;

        uint32_t duration = endTime - startTime;
        uint32_t curFee = getFee(info);
        cout << endl
             << "Hello, you stayed in the parking lot " << duration / 100 << " hour, "
             << "The cost is " << curFee/1000 << " Euro." << endl;
        up_ = true;

        // Delete current vehicle information from carTimeInfo_
        exitSPtr_->erase(info);
    }

    void lower(string info = "") { up_ = false; }

    uint32_t getFee(string info) {
        pair<clock_t, clock_t> curTimes = exitSPtr_->at(info);
        clock_t startTime = curTimes.first;
        clock_t endTime = curTimes.second;
        uint32_t duration = endTime - startTime;
        uint32_t feecnt = duration * hourlyFee_;
        return feecnt;
    }

   private:
    bool up_;
    // A shared smart pointer pointing to the time of vehicle entry and exit. 
    // There are two smart pointers, one at the entrance and one at the exit
    unordered_map<string, pair<clock_t, clock_t>>* exitSPtr_; 
};

#endif  // EXITBARRIER_HPP_
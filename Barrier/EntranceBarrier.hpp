#ifndef ENTRANCEBARRIER_HPP_
#define ENTRANCEBARRIER_HPP_
#include "Barrier.hpp"

class EntranceBarrier : public Barrier {
    friend class ExitBarrier;

   public:
    EntranceBarrier() : up_(false), entranceSPtr_(&carTimeInfo_) {}

    /**
     * @brief the barrier rises
     * Employees, will not be marked as employees; but foreign visitors will be notified, 
     * because the parking lot charges externally
     *
     */
    void raise(string info = "") {
        if(info.empty()) { 
            up_ = true;
            return;
        }
        cout << endl
             << "Visitors! Please note that this car park costs " << hourlyFee_
             << " Hourly." << endl;
        up_ = true;
    }

    /**
     * @brief barrier down
     *
     */
    void lower(string info = "") {
        if(info.empty()) { 
            up_ = false;
            return;
        }
        pair<clock_t, clock_t> curTimes = (*entranceSPtr_)[info] = pair<clock_t, clock_t>();
        clock_t startTime = curTimes.first;
        clock_t endTime = curTimes.second;
        startTime = clock();
        endTime = 0;
        (*entranceSPtr_)[info].first = startTime;
        (*entranceSPtr_)[info].second = endTime;
        up_ = false;
    }

    uint32_t getFee(string info) {
        pair<clock_t, clock_t> curTimes = entranceSPtr_->at(info);
        clock_t startTime = curTimes.first;
        clock_t endTime = curTimes.second;
        uint32_t duration = endTime - startTime;
        uint32_t feecnt = duration * hourlyFee_;
        return feecnt;
    }

   private:
    static unordered_map<string, pair<clock_t, clock_t>> carTimeInfo_;

    bool up_;
    unordered_map<string, pair<clock_t, clock_t>>* entranceSPtr_;
};



#endif  // ENTRANCEBARRIER_HPP_
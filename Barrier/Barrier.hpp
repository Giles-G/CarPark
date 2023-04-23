#ifndef BARRIER_HPP_
#define BARRIER_HPP_
#include <time.h>
#include <memory>
#include "../Config.hpp"

class Barrier {
   public:
    Barrier(){

    };

    /**
     * @brief raise the barrier
     *
     */
    virtual void raise(string info) {}

    /**
     * @brief lower the barrier
     *
     */
    virtual void lower(string info) {}

    /**
     * @brief Get the cost incurred by the current vehicle in the parking lot
     *
     * @param info
     * @return uint32_t
     */
    virtual uint32_t getFee(string info) { return 0; }

    /**
     * @brief Get the Hourly Fee object
     *
     * @return uint32_t
     */
    uint32_t getHourlyFee() { return hourlyFee_; }

    /**
     * @brief Adjust the parking fee
     *
     */
    bool adjustFee(int fee) {
        if (hourlyFee_ + fee < 0) {
            cout << endl
                 << "Fee adjustment error, it is not allowed to set the hourly parking fee to a value less than 0"
                 << endl;
            return false;
        } else if (hourlyFee_ + fee == 0) {
            cout << endl << "Please note that the current hourly parking fee is 0" << endl;
            hourlyFee_ += fee;
            return true;
        }
        hourlyFee_ += fee;
        return true;
    }

   protected:
    uint32_t hourlyFee_ = 10;

   private:
    bool up_;
};

#endif  // BARRIER_HPP_
#ifndef CARPARK_HPP_
#define CARPARK_HPP_

#include "Barrier/BarrierIncluder.hpp"
#include "Config.hpp"
#include "FullSign/FullSign.hpp"
#include "IDReader/IDReaderIncluder.hpp"
#include "Log/Log.hpp"

enum MODE {
    STAFF,     // STAFF mode
    NUMPLATE,  // NUMPLATE mode
    BARCODE    // Barcode mode
};

class CarPark {
   public:
    /**
     * @brief CarPark constructor, which includes the initialization of CarPark
     * and the initialization of the logging system
     *
     * @param cap Capacity of the parking lot
     */
    CarPark(int cap);

    /**
     * @brief Get the current parking capacity
     * @return Returns the capacity of the parking lot
     */
    uint32_t getCapacity() {
        if (isECHO_)
            cout << "Currently car park capacity is " << capacity_  << endl;
        return capacity_;
    }

    /**
     * @brief Returns the remaining vacancies in the parking lot
     *
     * @return uint32_t
     */
    uint32_t getSpacesLeft() {
        if (isECHO_)
            cout << "Currently remaining " << freeSpaces_ << " parking spaces."
                 << endl;
        return freeSpaces_;
    }

    /**
     * @brief Increase parking space
     * @param increment Need to increase capacity
     */
    void incrementSpaces(unsigned int increment);

    /**
     * @brief
     * @param increment capacity that needs to be reduced
     */
    void decrementSpaces(unsigned int decrease);

    /**
     * @brief Vehicles come in and operate dynamically using dynamic bindings
     * for different types
     *
     */
    void vehicleEntry();

    /**
     * @brief Vehicles depart and operate dynamically using dynamic bindings for
     * different types
     *
     */
    void vehicleLeaves();

    /**
     * @brief mode change
     *
     */
    void modeChange() {
        switch (carMode) {
            case STAFF:
                swichToIDCard();
                break;
            case NUMPLATE:
                swichToNPlate();
                break;
            case BARCODE:
                swichToBarcode();
                break;

            default:
                break;
        }
        return;
    }

   private:
    /**
     * @brief Read employee card or information
     *
     * @return If a null pointer is returned, it means that the information
     * reading failed
     */
    void* readInfo();

    /**
     * @brief Carry out relevant information processing for vehicles that need
     * to leave the parking lot
     *
     * @return string If an empty string is returned, an error occurred
     */
    string leavePark();

    /**
     * @brief Switch to STAFF mode, that is, the sensor is bound to the
     * IDCardReader_ object
     *
     */
    void swichToIDCard() { sensor = &IDCardReader_; }

    /**
     * @brief Switch to NUMPLATE mode, that is, the sensor is bound to the
     * nplateReader_ object
     *
     */
    void swichToNPlate() { sensor = &nplateReader_; }

    /**
     * @brief Convert to BARCODE mode, that is, the sensor is bound to the
     * barcodeReader_ object
     *
     */
    void swichToBarcode() { sensor = &barcodeReader_; }

   public:
    IDReader* sensor;  // Identification device, can identify idcard license
                       // plate number barcode
    MODE carMode = STAFF;

   private:
    uint32_t capacity_;    // Capacity of the parking lot
    uint32_t freeSpaces_;  // free space in parking lot
    FullSign isFull_;      // Is the parking lot full

    bool isECHO_ = false;  // Whether to use echo
    int m_close_log = 0;   // Whether to save the log

    IDCardReader IDCardReader_;
    IDNumberplateReader nplateReader_;
    IDBarcodeReader barcodeReader_;

    EntranceBarrier entbarrier_;
    ExitBarrier exitBarrier_;
};

#endif  // CARPARK_HPP_
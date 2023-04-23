#include "CarPark.hpp"

unordered_map<string, pair<clock_t, clock_t>> EntranceBarrier::carTimeInfo_(
    unordered_map<string, pair<clock_t, clock_t>>{});

CarPark::CarPark(int cap) : capacity_(cap), freeSpaces_(cap) {
    isFull_.SwitchOff();

    IDCard* IDCard1 = new IDCard("Abigail", "9007845", HR);
    IDCard* IDCard2 = new IDCard("Gergely", "9007961", LOG);
    IDCard* IDCard3 = new IDCard("Polyxena", "9008120", TECH);
    IDCard* IDCard4 = new IDCard("James", "9004433", TECH);
    IDCard* IDCard5 = new IDCard("Curry", "9004090", HR);
    list<IDCard*> cards{IDCard1, IDCard2, IDCard3, IDCard4, IDCard5};

    IDCardReader_ = IDCardReader(cards);

    sensor = &IDCardReader_;

    m_close_log = 0;
    isECHO_ = true;
    Log::get_instance()->init("./CarParkLog", m_close_log, 2000, 800000, 800);

    cout << endl;
    cout << "|---------------------------------------------- |" << endl;
    cout << "|        welcome to the parking lot             |" << endl;
    cout << "|  Note: This parking lot charges for visitors  |" << endl;
    cout << "|                                               |" << endl;
    cout << "| author:Zhiqiang Geng       student_id:2200520 |" << endl;
    cout << "|                                               |" << endl;
    cout << "|-----------------------------------------------|" << endl;
    cout << endl;
}

void CarPark::incrementSpaces(unsigned int increment) {
    assert(increment > 0);
    capacity_ += increment;
    freeSpaces_ += increment;
    isFull_.SwitchOff();

    if (isECHO_)
        cout << "The increase is successful, and the capacity is now: "
             << capacity_ << endl;
}

void CarPark::decrementSpaces(unsigned int decrease) {
    assert(decrease > 0);
    if(freeSpaces_ - decrease < 0) {
        cout << "The operation failed, there are still vehicles in the parking lot, please reduce the zoom out value" << endl;
        return;
    }
    capacity_ -= decrease;
    freeSpaces_ -= decrease;
    if(freeSpaces_ == 0)
        isFull_.SwithOn();

    if (isECHO_)
        cout << "The decrease is successful, and the capacity is now: "
             << capacity_ << endl;
}

void* CarPark::readInfo() {
    while (sensor->Read()) {
        cout << endl << "Welcome to the parking lot, the gates are open." << endl;
        IDType* curInfo = static_cast<IDType*>(sensor->getLeast());
        if (curInfo == nullptr) {
            break;
        }

        // Staff access to the parking lot is free
        if (carMode == STAFF) {
            entbarrier_.raise();
            entbarrier_.lower();
            return curInfo;
        }
        entbarrier_.raise(curInfo->getIdentifier());
        entbarrier_.lower(curInfo->getIdentifier());
        return curInfo;
    }

    cout << endl << "Incorrect identity, no access." << endl;
    LOG_ERROR("Incorrect identity, no access.");
    return nullptr;
}

void CarPark::vehicleEntry() {
    if (isFull_.full()) {
        cout << endl << "Sorry, the parking lot is full and traffic is closed." << endl;
        LOG_ERROR("Parking lot is full, no traffic.");
        return;
    }

    switch (carMode) {
        case STAFF: {
            swichToIDCard();
            IDCard* curInfo = static_cast<IDCard*>(readInfo());
            // IDType* curInfo = static_cast<IDCard*>(readInfo());
            if (curInfo == nullptr) {
                return;
            }
            LOG_INFO("The employee vehicle whose employee number is %s enters the parking lot.",
                     curInfo->getIdentifier().c_str());
            break;
        }

        case NUMPLATE: {
            swichToNPlate();
            NumberPlate* curInfo = static_cast<NumberPlate*>(readInfo());
            if (curInfo == nullptr) {
                return;
            }
            LOG_INFO("A vehicle with license plate number %s enters the parking lot.",
                     curInfo->getIdentifier().c_str());
            break;
        }

        case BARCODE: {
            swichToBarcode();
            Barcode* curInfo = static_cast<Barcode*>(readInfo());
            if (curInfo == nullptr) {
                return;
            }
            LOG_INFO("The vehicle with barcode %s enters the parking lot.",
                     curInfo->getIdentifier().c_str());
            break;
        }

        default:
            break;
    }

    freeSpaces_--;
    if (freeSpaces_ == 0)
        isFull_.SwithOn();
}

string CarPark::leavePark() {
    string info = sensor->update();
    if(info.empty())
        return info;
    if (carMode == STAFF) {
        entbarrier_.raise();
    } else {
        exitBarrier_.raise(info);
    }

    exitBarrier_.lower();
    cout << endl << "I wish you a safe journey and look forward to seeing you next time." << endl;

    freeSpaces_++;

    return info;
}

void CarPark::vehicleLeaves() {
    if (freeSpaces_ == capacity_) {
        cout << endl
             << "There are no vehicles in the parking lot, and the vehicle Leaves operation cannot be performed." << endl;
        LOG_ERROR("There are no vehicles in the parking lot, and the vehicle Leaves operation cannot be performed.");
        return;
    }

    // Exiting the parking lot requires external direct recognition, thus choosing from three modes
    switch (carMode) {
        case STAFF: {
            swichToIDCard();
            string curInfo = leavePark();
            if (!curInfo.empty()) {
                LOG_INFO("The employee vehicle whose employee number is %s leaves the parking lot.", curInfo.c_str());
            } else {
                LOG_ERROR("Currently no employee vehicles are included.");
            }
            break;
        }

        case NUMPLATE: {
            swichToNPlate();
            string curInfo = leavePark();
            if (!curInfo.empty()) {
                LOG_INFO("The vehicle with license plate number %s leaves the parking lot.", curInfo.c_str());
            } else {
                LOG_ERROR("Currently no visitor vehicles are included.");
            }

            break;
        }

        case BARCODE: {
            swichToBarcode();
            string curInfo = leavePark();
            if (!curInfo.empty()) {
                LOG_INFO("The vehicle with barcode %s leaves the parking lot.", curInfo.c_str());
            } else {
                LOG_ERROR("Currently no visitor vehicles are included.");
            }
            break;
        }

        default:
            break;
    }
}
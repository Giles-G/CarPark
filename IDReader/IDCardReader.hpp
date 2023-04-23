/************************************
 * @file IDCardReader.hpp
 * @brief 1. Record the identity information of all employees
 *        2. Use the card reader to read the employee's number_
 * *********************************/

#ifndef IDCARDREADER_HPP_
#define IDCARDREADER_HPP_
#include "IDReader.hpp"

enum DEPARTMENT {
    HR,   // human resources department
    LOG,  // logistics department
    TECH  // technology sector
};

/**
 * @brief Employee Identity Card
 */
class IDCard : public IDType {
   public:
    IDCard(string name, string idnumber, DEPARTMENT dpm)
        : name_(name), number_(idnumber), dpm_(dpm) {}

    bool isValid(string code = "") { return true; }

    /**
     * @brief Get ID
     *
     */
    string getIdentifier() { return number_; }

   public:
    string name_;     // name
    string number_;   // card number
    DEPARTMENT dpm_;  // department
};

class IDCardReader : public IDReader {
   public:
    /**
     * @brief Construct a new IDCardReader object
     *
     */
    IDCardReader() {}

    /**
     * @brief Construct a new IDCardReader object
     *
     * @param cards List for initializing employee information
     */
    IDCardReader(list<IDCard*>& cards) : staffIDCards_(cards) {
        /* 
        IDCard* IDCard1 = new IDCard("Abigail", "9007845", HR);
        IDCard* IDCard2 = new IDCard("Gergely", "9007961", LOG);
        IDCard* IDCard3 = new IDCard("Polyxena", "9008120", TECH);
        list<IDCard*> cards{IDCard1, IDCard2, IDCard2}; 
        */
        for (auto card : cards) {
            staffIDCardNumbers_[card->number_] = card;
        }
        cout << endl;
        cout << "Company employee information entry completed!" << endl;
    }

    /**
     * @brief Read current employee card number from hash table
     *
     * @return true Employee card number exists
     * @return false Employee ID does not exist
     */
    bool Read() {
        string number;
        cout << endl << "Please enter the employee number who is currently entering the parking lot: ";
        if (cin >> number) {
            if (isExist_[number]) {
                cout << endl
                     << "The employee's vehicle is already in the parking lot and re-entry is not permitted." << endl;
                return false;
            }
            if (staffIDCardNumbers_.find(number) != staffIDCardNumbers_.end()) {
                isExist_[number] = true;
                return true;
            }
        }
        cout << "employee id not recognized" << endl;
        return false;
    }

    /**
     * @brief Choose to add or delete employees
     *
     * @param opt 0 means the employee drove out of the parking lot, 
     *            1 means delete the employee, 
     *            2 means the newly added employee
     */
    string update(uint16_t opt = 0) {
        if (opt == 1) {
            cout << endl << "Please enter the employee number to be deleted: ";
            string number;
            cin >> number;
            removeEmployee(number);
        } else if (opt == 2) {
            cout << endl
                 << "Please enter the new employee name, number, department in turn: ";
            string name, number;
            int dmp;
            cin >> name >> number >> dmp;
            IDCard* newCard = new IDCard(name, number, (DEPARTMENT)dmp);
            staffIDCards_.push_back(newCard);
            staffIDCardNumbers_[number] = newCard;
        } else if (opt == 0) {
            if (staffIDCards_.empty()) {
                cout << endl << "Currently no employee vehicles are included." << endl;
                return "";
            }

            cout << "Please enter the employee number who will leave the parking lot: ";
            string number;
            cin >> number;

            if (isExist_[number] == false) {
                cout << endl << "Currently no visitor vehicles are included." << endl;
                return "";
            }
            // The next two steps are unnecessary because they require long-term storage
            // staffIDCards_.remove(staffIDCardNumbers_[number]);
            // staffIDCardNumbers_.erase(number);
            isExist_[number] = false;
            return number;
        }

        return "";
    }

    /**
     * @brief Get the IDCard of the employee who recently entered the parking lot
     *
     * @return IDCard*
     */
    void* getLeast() { return staffIDCards_.back(); }

    /**
     * @brief List all employee information
     *
     */
    void showAllElement() {
        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << "All Employee Information : " << endl;
        cout << "NO.  "
             << "name     "
             << "number   "
             << "department "
             << "isExist  " << endl;
        cout << "----------------------------------------" << endl;

        int cnt = 1;
        for (auto card : staffIDCards_) {
            cout << cnt << "."
                 << "   " << card->name_ << "  ";
            cout << card->number_ << "     ";
            cout << card->dpm_ << "      ";
            cout << isExist_[card->number_]
            << endl;
            ++cnt;
        }
        cout << endl;
    }

   private:
    /**
     * @brief Add new employees
     */
    void addNewEmployee(string name, string number, DEPARTMENT dpm) {
        IDCard* newCard = new IDCard(name, number, dpm);
        staffIDCards_.push_back(newCard);
        staffIDCardNumbers_[number] = newCard;
    }

    /**
     * @brief Remove related staff
     * @param number employee's id
     */
    void removeEmployee(string number) {
        IDCard* curCard = staffIDCardNumbers_[number];
        staffIDCards_.remove(curCard);
        staffIDCardNumbers_.erase(number);
    }

   private:
    list<IDCard*> staffIDCards_;  // Store ID cards of all employees currently in the parking lot
    unordered_map<string, IDCard*>
        staffIDCardNumbers_;  // key is the card number of the ID card, and value is the pointer of the ID card
    unordered_map<string, bool> isExist_;  // Are employee vehicles in the parking lot?
};

#endif  // IDCARDREADER_HPP_
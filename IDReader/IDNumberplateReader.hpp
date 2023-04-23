#ifndef IDNUMBERPLATEREADER_HPP_
#define IDNUMBERPLATEREADER_HPP_
#include "IDReader.hpp"

class NumberPlate : public IDType {
   public:
    /**
     * @brief Construct a new NumberPlate object
     */
    NumberPlate(string number) : nplate_(number) {}

    /**
     * @brief Check the validity of NumberPlate
     */
    static bool isValid(string number) { return true; }

    /**
     * @brief Get ID
     * 
     */
    string getIdentifier() {
        return nplate_;
    }

   public:
    string nplate_;
};

class IDNumberplateReader : public IDReader {
   public:
    IDNumberplateReader() = default;

    /**
     * @brief When a vehicle enters, record the license plate number of the vehicle
     *
     * @return true record success
     * @return false NumberPlate format error or record failure
     */
    bool Read() {
        string number;
        cout << "Please enter the Number Plate you want to enter the parking lot : ";
        if (cin >> number) {
            if (!NumberPlate::isValid(number)) {
                cout << "Number Plate format error." << endl;
                return false;
            }
            if(umap_.find(number) != umap_.end()) {
                cout << "vehicle already exists." << endl;
                return false;
            }

            NumberPlate* numplate = new NumberPlate(number);
            nplates_.push_back(numplate);
            umap_[numplate->nplate_] = numplate;
            return true;
        }
        return false;
    }

    /**
     * @brief If a vehicle leaves the parking lot, delete the license plate number of the vehicle from nplates_
     * 
     */
    string update(uint16_t opt = 0) {
        if(nplates_.empty()) {
            cout << endl << "Currently no visitor vehicles are included." << endl;
            return "";
        }

        string number;
        cout << "Please enter the Number Plate that needs to leave the parking lot : ";
        cin >> number;
        if(umap_.find(number) == umap_.end()) {
            cout << endl << "Currently no visitor vehicles are included." << endl;
            return "";
        }
        nplates_.remove(umap_[number]);
        umap_.erase(number);
        return number;
    }

    /**
     * @brief Get the NumberPlate of the most recent vehicle that entered the parking lot
     *
     * @return void*
     */
    void* getLeast() { return nplates_.back(); }

    /**
     * @brief List the license plate numbers of all vehicles in the parking lot
     *
     */
    void showAllElement() {
        cout << endl;
        cout << "All license plates in the parking lot : " << endl;
        cout << "NO.  "
             << "Number Plate" << endl;
        cout << "-----------------------" << endl;

        int cnt = 1;
        for (auto number : nplates_) {
            cout << cnt << "."
                 << "   " << number->nplate_ << endl;
            ++cnt;
        }
        cout << endl;
    }

   private:
    list<NumberPlate*> nplates_;  // Store the license plate numbers of all vehicles currently in the parking lot
    unordered_map<string, NumberPlate*>
        umap_;  // value is the index of NumberPlate in nplates_, key is the license plate number
};

#endif  // IDNUMBERPLATEREADER_HPP_
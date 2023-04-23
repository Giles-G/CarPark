#ifndef IDBARCODEREADER_HPP_
#define IDBARCODEREADER_HPP_
#include "IDReader.hpp"

class Barcode : public IDType {
   public:
    /**
     * @brief Construct a new Barcode object
     */
    Barcode(string code) : bcode_(code) {}

    /**
     * @brief Detecting the validity of barcode
     */
    static bool isValid(string code) { return true; }

    /**
     * @brief Get ID
     * 
     */
    string getIdentifier() {
        return bcode_;
    }

   public:
    string bcode_;
};

class IDBarcodeReader : public IDReader {
   public:
    IDBarcodeReader() = default;

    /**
     * @brief When a vehicle enters, record the Barcode of the vehicle
     *
     * @return true record success
     * @return false Barcode format error or record failure
     */
    bool Read() {
        string bcode;
        cout << endl << "Please enter the Barcode of the vehicle currently entering the parking lot: ";
        if (cin >> bcode) {
            if (!Barcode::isValid(bcode)) {
                cout << "Barcode format error." << endl;
                return false;
            }
            if(umap_.find(bcode) != umap_.end()) {
                cout << "vehicle already exists." << endl;
                return false;
            }
            Barcode* curBurcode = new Barcode(bcode);
            bcodes_.push_back(curBurcode);
            umap_[curBurcode->bcode_] = curBurcode;
            return true;
        }
        return false;
    }

    /**
     * @brief If a vehicle leaves the parking lot, delete the Barcode of the vehicle from bcodes_
     *
     */
    string update(uint16_t opt = 0) {
        if(bcodes_.empty()) {
            cout << endl << "Currently no visitor vehicles are included." << endl;
            return "";
        }
        

        cout << "Please enter the Barcode of the vehicle to leave the parking lot: ";
        string code;
        cin >> code;
        if(umap_.find(code) == umap_.end()) {
            cout << endl << "Currently no visitor vehicles are included." << endl;
            return "";
        }
        bcodes_.remove(umap_[code]);
        umap_.erase(code);
        return code;
    }

    /**
     * @brief Get the Barcode of the vehicle that recently entered the parking lot
     *
     * @return void*
     */
    void* getLeast() { return bcodes_.back(); }

    /**
     * @brief List the barcodes of all vehicles in the parking lot
     *
     */
    void showAllElement() {
        cout << endl;
        cout << "All barcodes in the parking lot : " << endl;
        cout << "NO.  "
             << "Barcode" << endl;
        cout << "-----------------------" << endl;

        int cnt = 1;
        for (auto code : bcodes_) {
            cout << cnt << "."
                 << "   " << code->bcode_ << endl;
            ++cnt;
        }
        cout << endl;
    }

   private:
    list<Barcode*> bcodes_;  // Stores the Barcodes of all vehicles currently in the parking lot
    unordered_map<string, Barcode*>
        umap_;  // value is the index of Barcode in bcodes_, keyBarcode
};

#endif  // IDBARCODEREADER_HPP_
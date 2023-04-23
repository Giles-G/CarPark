#include <unistd.h>
#include "Barrier/BarrierIncluder.hpp"
#include "CarPark.hpp"
#include "IDReader/IDReaderIncluder.hpp"

// using namespace std;

void showOptions() {
    cout << endl;
    cout << "Enter a sequence number from the table below to perform the "
            "action, Instruction number 0 is used to exit"
         << endl;
    cout << "|-----------------------------------------------------|" << endl;
    cout << "| 1.STAFF MODE   | 2.NUMPLATE MODE | 3.BARCODE MODE   |" << endl;
    cout << "|-----------------------------------------------------|" << endl;
    cout << "| 4.vehicleEntry | 5.vehicleLeaves | 6.showAllElement |" << endl;
    cout << "|-----------------------------------------------------|" << endl;
    cout << "| 7.addStaff     | 8.removeStaff   | 9.getCapacity    |" << endl;
    cout << "|-----------------------------------------------------|" << endl;
    cout << "| 10.getLefts    | 11.incrementSps | 12.decrementSps  |" << endl;
    cout << "|-----------------------------------------------------|" << endl;
}

bool isCmdValid(string cmd) {
    // Supports up to two-digit instructions
    if(cmd.size() > 2)
        return false;
    
    for(auto ch : cmd) {
        if(ch < '0' || ch > '9')
            return false;
    }
    return true;
}

void optionSelect(CarPark& plot) {
    showOptions();

    int opt;
    bool shutdown = false;
    while (!shutdown) {
        cout << " -> ";
        string commond;
        cin >> commond;
        if (commond == "help") {
            showOptions();
            continue;
        }
        if(isCmdValid(commond))
            opt = stoi(commond);
        else 
            opt = -1;
        switch (opt) {
            case 0:
                shutdown = true;
                break;

            case 1: {
                plot.carMode = STAFF;
                plot.modeChange();
                break;
            }

            case 2: {
                plot.carMode = NUMPLATE;
                plot.modeChange();
                break;
            }

            case 3: {
                plot.carMode = BARCODE;
                plot.modeChange();
                break;
            }

            case 4:
                plot.vehicleEntry();
                break;

            case 5:
                plot.vehicleLeaves();
                break;

            case 6:
                plot.sensor->showAllElement();
                break;

            case 7: {
                plot.carMode = STAFF;
                plot.modeChange();
                plot.sensor->update(2);
                break;
            }

            case 8: {
                plot.carMode = STAFF;
                plot.modeChange();
                plot.sensor->update(1);
                break;
            }

            case 9:
                plot.getCapacity();
                break;

            case 10:
                plot.getSpacesLeft();
                break;

            case 11: {
                int space = 0;
                cout << "Please enter the size to expand : ";
                cin >> space;
                plot.incrementSpaces(space);
                break;
            }

            case 12: {
                int space = 0;
                cout << "Please enter the size to reduce : ";
                cin >> space;
                plot.incrementSpaces(space);
                break;
            }

            default:
                cout << "Command error, you can enter 'help' to get help"
                     << endl;
                break;
        }
    }
}

int main(int argc, char const* argv[]) {
    int carParkSize = 3;
    CarPark plot = CarPark(carParkSize);

    optionSelect(plot);
    return 0;
}

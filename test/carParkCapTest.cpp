#include <unistd.h>
#include "../Barrier/BarrierIncluder.hpp"
#include "../CarPark.hpp"
#include "../IDReader/IDReaderIncluder.hpp"

int main(int argc, char const *argv[]) {
    // Here test the expansion cap and shrink cap of the parking lot can work normally
    int carParkSize = 3;
    CarPark plot = CarPark(carParkSize);

    plot.carMode = BARCODE;
    plot.modeChange();

    plot.vehicleEntry();
    plot.vehicleEntry();
    plot.vehicleEntry();

    // capacity exceeded
    plot.vehicleEntry();

    // expand
    plot.incrementSpaces(3);

    // try again 
    plot.vehicleEntry();

    // reduce, Prompt reduction too much
    plot.decrementSpaces(4);

    // Try reducing again
    plot.decrementSpaces(2);

    // At this time, the capacity is 4, and it is just full after entering.
    plot.vehicleEntry();

}
#include <unistd.h>
#include "../Barrier/BarrierIncluder.hpp"
#include "../CarPark.hpp"
#include "../IDReader/IDReaderIncluder.hpp"

int main(int argc, char const *argv[])
{
    //Enter the parking lot with vehicles in three different modes

    int carParkSize = 6;
    CarPark plot = CarPark(carParkSize);
    plot.getCapacity();
    plot.getSpacesLeft();

    plot.sensor->showAllElement();
    plot.carMode = STAFF;
    plot.modeChange();
    plot.vehicleEntry();
    plot.vehicleEntry();
    plot.sensor->showAllElement();
    plot.getCapacity();
    plot.getSpacesLeft();

    plot.sensor->showAllElement();
    plot.carMode = NUMPLATE;
    plot.modeChange();
    plot.vehicleEntry();
    plot.vehicleEntry();
    plot.sensor->showAllElement();
    plot.getCapacity();
    plot.getSpacesLeft();

    plot.sensor->showAllElement();
    plot.carMode = BARCODE;
    plot.modeChange();
    plot.vehicleEntry();
    plot.vehicleEntry();
    plot.sensor->showAllElement();
    plot.getCapacity();
    plot.getSpacesLeft();

    return 0;
}
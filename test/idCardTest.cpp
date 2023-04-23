#include <unistd.h>
#include "../Barrier/BarrierIncluder.hpp"
#include "../CarPark.hpp"
#include "../IDReader/IDReaderIncluder.hpp"

int main(int argc, char const *argv[])
{
    int carParkSize = 3;
    CarPark plot = CarPark(carParkSize);

    plot.carMode = STAFF;
    plot.modeChange();

    plot.sensor->showAllElement();
    plot.vehicleEntry();
    plot.vehicleEntry();
    plot.sensor->showAllElement();

    plot.sensor->showAllElement();
    plot.vehicleLeaves();
    plot.vehicleLeaves();
    plot.sensor->showAllElement();
    // Here execute vehicleLeaves one more time to test the error correction ability
    plot.vehicleLeaves();

    // First add an employee, then remove him
    plot.sensor->update(2);
    plot.sensor->showAllElement();
    plot.sensor->update(1);
    plot.sensor->showAllElement();

    return 0;
}



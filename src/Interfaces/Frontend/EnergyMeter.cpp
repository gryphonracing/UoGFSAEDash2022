#include <EnergyMeter.hpp>

using namespace CAN;

void EnergyMeter::generateValues() {
    static float voltage = 620;
    static float current = 0;
    emit newCurrent(current += 3.8f);
    emit newVoltage(voltage -= 2.7f);

    if (voltage <= 480) {
        voltage = 620;
    }
    if (current >= 200) {
        current = 0;
    }
}
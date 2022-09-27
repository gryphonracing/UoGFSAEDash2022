#include <BMS.hpp>

using namespace CAN;

void BMS::generateValues() {
    static uint16_t voltage = 110;
    static uint16_t percent = 0;
    emit newVoltage(static_cast<float>(voltage++) / 10);
    emit newBatteryPercent(static_cast<float>(percent++) / 10);
    if (percent >= 1000) {
        percent = 0;
    }
    if (voltage >= 145) {
        voltage = 110;
    }
    
}
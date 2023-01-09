#include <BMS.hpp>

using namespace CAN;

void BMS::generateValues() {
    static uint16_t voltage = 110;
    static uint16_t current = -6000;
    static uint16_t percent = 0;
    static uint16_t temp = -40;
    emit newAccumulatorOpenVoltage(static_cast<float>(voltage++) / 10);
    emit newAccumulatorSOC(static_cast<float>(percent++) / 10);
    emit newBMSTemp(static_cast<float>(temp++));
    emit newAccumulatorMaxTemp(static_cast<float>(temp++));
    emit newAccumulatorCurrent(static_cast<float>(current++) / 10);
    emit newAccumulatorInstVoltage(static_cast<float>(voltage++) / 10);

    if (temp >= 80) {
        temp = -40;
    }
    if (percent >= 1000) {
        percent = 0;
    }
    if (voltage >= 145) {
        voltage = 110;
    }
    if (current >= 6000) {
        current = -6000;
    }
}
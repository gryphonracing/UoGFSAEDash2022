#include <BMS.hpp>

using namespace CAN;

void BMS::generateValues() {
    static float voltage = 620;
    static float current = 0;
    static float percent = 0;
    static float temp = -40;
    emit newAccumulatorOpenVoltage(voltage += 0.8f);
    emit newAccumulatorSOC(percent += 0.7f);
    emit newBMSTemp(temp += 0.9f);
    emit newAccumulatorMaxTemp(temp += 1.3f);
    emit newAccumulatorCurrent(current += 3.8f);
    emit newAccumulatorInstVoltage(voltage -= 2.7f);

    if (temp >= 80) {
        temp = -40;
    }
    if (percent >= 100) {
        percent = 0;
    }
    if (voltage <= 480) {
        voltage = 620;
    }
    if (current >= 200) {
        current = 0;
    }
}
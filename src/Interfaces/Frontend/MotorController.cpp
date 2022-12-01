#include <MotorController.hpp>

using namespace CAN;

void MotorController::generateValues() {
    static float rpm = 0;
    static float temps = -100;
    static float voltage = 8.00f;
    emit newMotorRPM(rpm);
    emit newCoolantTemp(temps);
    emit newOilTemp(temps);
    emit newMotorTemp(temps);
    emit new12VVoltage(voltage);


    rpm += 1.0f;
    if (rpm >= 32767) {
        rpm = 0;
    }
    temps += 0.1f;
    if (temps >= 100) {
        temps = -100;
    }
    voltage += 0.15f;
    if (voltage >= 14.5f) {
        voltage = 8.00f;
    }
}
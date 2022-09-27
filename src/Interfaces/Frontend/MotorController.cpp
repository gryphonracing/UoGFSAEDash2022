#include <MotorController.hpp>

static void registerMetatypes() {
    qRegisterMetaType<int16_t>("int16_t"); // Pass this type into qml
}
Q_CONSTRUCTOR_FUNCTION(registerMetatypes)

using namespace CAN;

void MotorController::generateValues() {
    static int16_t rpm = -32768;
    static int16_t coolant_temp = -1000;
    static int16_t oil_temp = -1000;
    emit newRPM(rpm++);
    emit newCoolantTemp(static_cast<float>(coolant_temp++) / 10);
    emit newOilTemp(static_cast<float>(oil_temp++) / 10);
    if (rpm == 32767) {
        rpm = -32768;
    }
    if (coolant_temp >= 1000) {
        coolant_temp = -1000;
    }
    if (oil_temp >= 1000) {
        oil_temp = -1000;
    }
}
#include <MotorController.hpp>

using namespace CAN;

void MotorController::generateValues() {
    emit newRPM(52);
    emit newCoolantTemp(108);
    emit newOilTemp(72);
}
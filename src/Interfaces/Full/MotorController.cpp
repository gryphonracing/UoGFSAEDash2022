#include <fmt/core.h>

#include <MotorController.hpp>
#include <converters.hpp>
#include <tools.hpp>

using namespace CAN;


float MotorController::toCelsius(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float MotorController::toLowVoltage(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<100>(low_byte, high_byte);
}

float MotorController::toNm(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float MotorController::toHighVoltage(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float MotorController::toAmps(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float MotorController::toDegrees(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

int16_t MotorController::toRPM(uint8_t low_byte, uint8_t high_byte) {
    return combineTo<int16_t>(low_byte, high_byte);
}

bool MotorController::toBool(uint8_t byte) {
    return static_cast<bool>(byte);
}

float MotorController::toHz(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float MotorController::tokW(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float MotorController::toWebers(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<1000>(low_byte, high_byte);
}

// either 100 or 10000 scale
float MotorController::toProportionalGain100(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<100>(low_byte, high_byte);
}
float MotorController::toProportionalGain10000(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

float MotorController::toIntegralGain(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

float MotorController::toDerivativeGain(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<100>(low_byte, high_byte);
}

float MotorController::toLowpassFilterGain(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

uint16_t MotorController::toCount(uint8_t low_byte, uint8_t high_byte) {
    return combineTo<uint16_t>(low_byte, high_byte);
}

float MotorController::toPSI(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

static void registerMetatypes() {
    qRegisterMetaType<int16_t>("int16_t"); // Pass this type into qml
}
Q_CONSTRUCTOR_FUNCTION(registerMetatypes)

void MotorController::newFrame(const can_frame& frame) {
    switch (CAN::frameId(frame)) {
        // case 0x0A0: // Temps #1
        //     break;

        // case 0x0A1: // Temps #2
        //     break;

    case 0x0A2: { // Temps #3 & Torque Shudder
        fmt::print("Got Temps #3\n");
        auto coolant_temp = toCelsius(frame.data[0], frame.data[1]);
        fmt::print("Coolant Temp: {} C\n", coolant_temp);
        emit newCoolantTemp(coolant_temp);
        fmt::print("Hot Spot Temp: {} C\n", toCelsius(frame.data[2], frame.data[3]));
        fmt::print("Motor Temp: {} C\n", toCelsius(frame.data[4], frame.data[5]));
        fmt::print("Torque Shudder: {} Nm\n", toNm(frame.data[6], frame.data[7]));
        break;
    }

        // case 0x0A3: // Analog Status
        //     break;

    case 0x0A4: { // Digital Input Status
        fmt::print("Got Digital Input\n");
        fmt::print("Forward: {}\n", toBool(frame.data[0]));
        fmt::print("Reverse: {}\n", toBool(frame.data[1]));
        fmt::print("Brake: {}\n", toBool(frame.data[2]));
        fmt::print("Regen Disable: {}\n", toBool(frame.data[3]));
        fmt::print("Ignition: {}\n", toBool(frame.data[4]));
        fmt::print("Start: {}\n", toBool(frame.data[5]));
        fmt::print("Valet: {}\n", toBool(frame.data[6]));
        fmt::print("Input 8: {}\n", toBool(frame.data[7]));
        break;
    }

    case 0x0A5: { // Motor Position Information
        fmt::print("Got Motor Pos Info\n");
        fmt::print("Elec Motor Angle: {} deg\n", toDegrees(frame.data[0], frame.data[1]));
        fmt::print("Motor RPM: {} rpm\n", toRPM(frame.data[2], frame.data[3]));
        fmt::print("Elec Out Freq: {} Hz\n", toHz(frame.data[4], frame.data[5]));
        fmt::print("Delta Resolver: {} deg\n", toDegrees(frame.data[6], frame.data[7]));
        emit newRPM(toRPM(frame.data[2], frame.data[3]));
        break;
    }

        // case 0x0B0: // Fault Codes
        //     break;
    default:
    break;
        // fmt::print("ID: 0x{:02X}, Ext: {}, RTR: {}, Err: {}, Payload: 0x{:02X} 0x{:02X} 0x{:02X} "
        //            "0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}\n",
        //            CAN::frameId(frame),
        //            CAN::frameFormat(frame) == CanFormat::Extended,
        //            CAN::isError(frame),
        //            frame.data[0],
        //            frame.data[1],
        //            frame.data[2],
        //            frame.data[3],
        //            frame.data[4],
        //            frame.data[5],
        //            frame.data[6],
        //            frame.data[7]);
    }
}

void MotorController::newError(const can_frame&) {
    fmt::print("Error\n");
};

void MotorController::newTimeout(){};
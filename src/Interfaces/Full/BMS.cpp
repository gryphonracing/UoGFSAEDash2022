#include <fmt/core.h>

#include <BMS.hpp>
#include <tools.hpp>
#include <converters.hpp>

using namespace CAN;


float BMS::toCelsius(uint8_t byte) {
    return static_cast <float> (*reinterpret_cast<int8_t *>(&byte));
}

float BMS::toStateOfCharge(uint8_t byte) {
    return *reinterpret_cast<int8_t *>(&byte) * 0.5;
}

float BMS::toCurrent(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(high_byte, low_byte);
}

float BMS::toVoltage(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10>(high_byte, low_byte);
}

//Will recieve data from CANbus here
void BMS::newFrame(const can_frame& frame) {

    //For now, just need the pack voltage and pack state of charge
    switch (CAN::frameId(frame)) {

    //Pack voltage and pack state of charge
    case 0x0C0: {
        auto pack_open_voltage = BMS::toVoltage(frame.data[0], frame.data[1]);
        auto pack_state_of_charge = BMS::toStateOfCharge(frame.data[2]);
        emit newAccumulatorOpenVoltage(pack_open_voltage);
        emit newAccumulatorSOC(pack_state_of_charge);
        break;
    }

    //Pack current and instant voltage
    case 0x0C1: {
        auto instant_voltage = toVoltage(frame.data[0], frame.data[1]);
        auto pack_current = toCurrent(frame.data[2], frame.data[3]);
        emit newAccumulatorInstVoltage(instant_voltage);
        emit newAccumulatorCurrent(pack_current);
        break;
    }

    // Cumulator max temp and bms temp
    case 0x0C2: {
        auto max_accumulator_temp = toCelsius(frame.data[0]);
        auto internal_temp = toCelsius(frame.data[1]);
        emit newAccumulatorMaxTemp(max_accumulator_temp);
        emit newBMSTemp(internal_temp);
        break;
    }

    //Any other value, print to console
    default: {
        //fmt::print("Error!, didn't find pack state of charge or voltatge\n");
        // fmt::print("ID: 0x{:02X}, Ext: {}, RTR: {}, Err: {}, Payload: 0x{:02X} 0x{:02X} 0x{:02X} "
        //     "0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}\n",
        //     CAN::frameId(frame),
        //     CAN::frameFormat(frame) == CanFormat::Extended,
        //     CAN::isRemoteTransmissionRequest(frame),
        //     CAN::isError(frame),
        //     frame.data[0],
        //     frame.data[1],
        //     frame.data[2],
        //     frame.data[3],
        //     frame.data[4],
        //     frame.data[5],
        //     frame.data[6],
        //     frame.data[7]);
    }}
}

void BMS::newError(const can_frame&) {
    fmt::print("Error\n");
};

//Callback from when the socket times out
//Doesnt have to be used, but must be declared
void BMS::newTimeout() {};

//void BMS::recieveData() {};
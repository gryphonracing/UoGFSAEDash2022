#include <fmt/core.h>

#include <BMS.hpp>
#include <tools.hpp>
#include <converters.hpp>

using namespace CAN;

//Will recieve data from CANbus here
void BMS::newFrame(const can_frame& frame) {

    //For now, just need the pack voltage and pack state of charge
    switch (CAN::frameId(frame)) {

    //Pack voltage and pack state of charge
    case 0x0C0: {
        auto pack_votage = toVoltage(frame.data[3], frame.data[4]);
        auto state_of_charge = toStateOfCharge(frame.data[5], frame.data[6]);
        fmt::print("Success A\n");
        break;
    }

    //Pack current and heat sink temp (celcius)
    case 0x0C1: {
        auto pack_current = toCurrent(frame.data[3], frame.data[4]);
        auto temperature = toTemperature(frame.data[5], frame.data[6]);
        fmt::print("Success B\n");
        break;
    }

    //Pack peak temp, lowest temp, and heat sink sink temp (celcius)
    case 0x0C2: {
        auto temperature_heat_sink = toTemperature(frame.data[3], frame.data[4]);
        auto temperature_high = toTemperature(frame.data[5], frame.data[6]);
        auto temperature_low = toTemperature(frame.data[7], frame.data[8]);
        fmt::print("Success C\n");
        break;
    }

    //Any other value, print to console
    default:
        fmt::print("Error!, didn't find pack state of charge or voltatge\n");
        fmt::print("ID: 0x{:02X}, Ext: {}, RTR: {}, Err: {}, Payload: 0x{:02X} 0x{:02X} 0x{:02X} "
            "0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}\n",
            CAN::frameId(frame),
            CAN::frameFormat(frame) == CanFormat::Extended,
            CAN::isRemoteTransmissionRequest(frame),
            CAN::isError(frame),
            frame.data[0],
            frame.data[1],
            frame.data[2],
            frame.data[3],
            frame.data[4],
            frame.data[5],
            frame.data[6],
            frame.data[7]);
    }
}

void BMS::newError(const can_frame&) {
    fmt::print("Error\n");
};

//Callback from when the socket times out
//Doesnt have to be used, but must be declared
void BMS::newTimeout() {};

//void BMS::recieveData() {};
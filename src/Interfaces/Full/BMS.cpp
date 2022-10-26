#include <fmt/core.h>

#include <BMS.hpp>
#include <tools.hpp>

using namespace CAN;

//Will recieve data from CANbus here
void BMS::newFrame(const can_frame& frame) {
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

    // ------- <Old code>------
    //PID address exists across two data frames; 2 and 3
    //We combine then and that will give us the address we are checking 
    //in each case
    //PID address values can be found here
    //https://www.orionbms.com/downloads/misc/orionbms_obd2_pids.pdf
    /*switch ( combineTo<uint16_t>(frame.data[2], frame.data[3]) )

    //Pack Voltage check
    case 0xF00D:
        fmt::print("Pack voltage = %u\n", combineTo<uint16_t>(frame.data[4], frame.data[5])

    //Pack state of charge
    case 0xF00F:
        fmt::print("Pack state of charge = %u\n", combineTo<uint16_t>(frame.data[4], frame.data[5])

    default:
        fmt::print("Failed to find address '0xF00D' and '0xF00F'\n");
        fmt::print("Address found = %u\n", combineTo<uint16_t>(frame.data[2], frame.data[3]));
    */
   // ------- </Old code>------

    
    //For now, just need the pack voltage and pack state of charge
    switch (CAN::frameId(frame)) {

    //For now, just need the pack voltage and pack state of charge
    switch (CAN::frameId(frame)) {

    //Pack voltage
    case 0xF00D: {
        auto pack_votage = toVoltage(frame.data[3], frame.data[5]);
        fmt::print("Pack votage: {} C\n", pack_votage);
        //emit newCoolantTemp(coolant_temp);
        break;
    }


    //Pack state of charge
    case 0xF00F: { // Digital Input Status
        auto state_of_charge = toStateOfCharge(frame.data[3], frame.data[5]);
        fmt::print("Pack state of charge (0-100): {} C\n", state_of_charge);
        //emit newCoolantTemp(coolant_temp);
        break;
    }

    //Pack voltage and pack state of charge
    case 0x0C0: {
        auto pack_votage = toVoltage(frame.data[3], frame.data[4]);
        auto state_of_charge = toStateOfCharge(frame.data[5], frame.data[6]);
        fmt::print("Success A");
    }

    //Pack current and heat sink temp (celcius)
    case 0x0C1: {
        auto pack_current = toCurrent(frame.data[3], frame.data[4]);
        auto temperature = toTemperature(frame.data[5], frame.data[6]);
        fmt::print("Success A");
    }

    //Pack peak temp, lowest temp, and heat sink sink temp (celcius)
    case 0x0C2: {
        auto temperature_heat_sink = toTemperature(frame.data[3], frame.data[4]);
        auto temperature_high = toTemperature(frame.data[5], frame.data[6]);
        auto temperature_low = toTemperature(frame.data[7], frame.data[8]);
        fmt::print("Success A");
    }

    //Any other value, print to console
    default:
        fmt::print("Error!, didn't find pack state of charge or voltatge\n")
        fmt::print("ID: 0x{:02X}, Ext: {}, RTR: {}, Err: {}, Payload: 0x{:02X} 0x{:02X} 0x{:02X} "
            "0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}\n",
            CAN::frameId(frame),
            CAN::frameFormat(frame) == CanFormat::Extended,
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

void BMS::newTimeout(){};

void BMS::recieveData() {};
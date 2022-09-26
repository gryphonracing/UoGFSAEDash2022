#include <fmt/core.h>

#include <ECU2019.hpp>
#include <tools.hpp>
#include <converters.hpp>

using namespace CAN::Interfaces;

void ECU2019::startReceiving() {
    this->Interface::startReceiving(
        "can0", ECU2019::filters, ECU2019::timeout); // Get everything
}

void ECU2019::newFrame(const can_frame& frame) {
    switch(frame.can_id){
    case 0x0CFFF048: // RPM, TPS, Fuel Open Time, Ignition Angle
        fmt::print("RPM: {}rpm, TPS: {:.1}%, FOT: {:.1}ms, Ignition Angle: {:.1}deg\n"
            combineTo<uint32_t>(frame.data[0], frame.data[1]),
            convertToSigned<10>(frame.data[2], frame.data[3]),
            convertToSigned<10>(frame.data[4], frame.data[5]),
            convertToSigned<10>(frame.data[6], frame.data[7]),
            );
        break;

    case 0x0CFFF148: // Barometer, MAP, Lambda, Pressure Type
        bool isPSI = static_cast<bool>(combineTo<uint32_t>(frame.data[6], frame.data[7]));
        fmt::print("Pressure: {:.2}{3}, MAP: {:.2}{3}, Lambda: {:.2}uL\n"
            convertToSigned<100>(frame.data[0], frame.data[1]),
            convertToSigned<100>(frame.data[2], frame.data[3]),
            convertToSigned<100>(frame.data[4], frame.data[5]),
            isPSI ? "psi" : "kPa"
            );
        break;

    case 0x0CFFF548: // Battery Voltage, Air Temp, Coolant Temp, Temp Type
        bool isCelsius = static_cast<bool>(combineTo<uint32_t>(frame.data[6], frame.data[7]));
        fmt::print("Voltage: {:.2}V, Air Temp: {:.1}{3}, Coolant Temp: {:.1}{3}\n"
            convertToSigned<100>(frame.data[0], frame.data[1]),
            convertToSigned<10>(frame.data[2], frame.data[3]),
            convertToSigned<10>(frame.data[4], frame.data[5]),
            isCelsius ? 'C' : 'F'
            );
        break;

    default: // Unimplemented
        fmt::print("ID: 0x{:08X}, Ext: {}, RTR: {}, Err: {}, Payload: 0x{:02X} 0x{:02X} 0x{:02X} "
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
        break;
    }
}

void ECU2019::newError(const can_frame& frame) {
    fmt::print("Error\n");
};

void ECU2019::newTimeout() {
    fmt::print("Timeout\n");
};
#include <fmt/core.h>

#include <Dump.hpp>
#include <tools.hpp>

using namespace CAN::Interfaces;

void Dump::startReceiving() {
    this->Interface::startReceiving("vcan0", Dump::filters, Dump::timeout); // Get everything
}

void Dump::newFrame(const can_frame& frame) {
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
}

void Dump::newError(const can_frame& frame) {
    fmt::print("Error\n");
};

void Dump::newTimeout() {
    fmt::print("Timeout\n");
};
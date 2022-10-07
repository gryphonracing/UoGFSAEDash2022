#include <fmt/core.h>

#include <BMS.hpp>
#include <tools.hpp>

const unsigned int _BMSRecieveAddress = 0x7E3;
const unsigned int _BMSsendingAddress = 0x7EB;  //Add 8 to the recieve address to get sending address

using namespace CAN;

void BMS::newFrame(const can_frame& frame) {
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

void BMS::newError(const can_frame&) {
    fmt::print("Error\n");
};

void BMS::newTimeout(){};

void BMS::recieveData() {

}
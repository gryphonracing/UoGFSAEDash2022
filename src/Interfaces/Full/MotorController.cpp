#include <fmt/core.h>

#include "MotorController.hpp"

using namespace CAN::Interface;

MotorController::MotorController() : Interface(150) {}

void MotorController::startReceiving() {
    this->Interface::startReceiving("can0", m_filters); // Get everything
}

void MotorController::newFrame(const can_frame& frame) {
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

    switch (CAN::frameId(frame)) {
    case 0x0A0: // Temps #1
        break;

    case 0x0A1: // Temps #2
        break;

    case 0x0A2: // Temps #3 & Torque Shudder
        break;

    case 0x0A3: // Unused
        break;

    case 0x0A4: // Digital Input Status
        break;

    case 0x0A5: // Motor Position Information
        break;

    case 0x0A6: //  Current Information
        break;

    case 0x0A7: //  Current Information
        break;

    case 0x0A8: //  Current Information
        break;

    case 0x0A9: //  Current Information
        break;

    case 0x0AA: //  Current Information
        break;

    case 0x0AB: //  Current Information
        break;

    case 0x0AC: //  Current Information
        break;

    case 0x0AD: //  Current Information
        break;

    case 0x0AE: //  Current Information
        break;

    case 0x0AF: //  Current Information
        break;

    case 0x0B0: // Fault Codes
        break;
    }
}

void MotorController::newError() {
    fmt::print("Error\n");
};

enum Outputs {
    // 0x0A0 - Temps #1
    ModuleATemp,
    ModuleBTemp,
    ModuleCTemp,
    GateDriverTemp,

    // 0x0A1 - Temps #2
    ControlBoardTemp,
    RTDTemp1,
    RTDTemp2,
    RTDTemp3,

    // 0x0A2 - Temps #3 & Torque Shudder
    CoolantTemp,
    HotSpotTemp,
    MotorTemp,
    TorqueShudder,

    // 0x0A3
    AnalogInput1,
    AnalogInput2,
    AnalogInput3,
    AnalogInput4,
    AnalogInput5,
    AnalogInput6,
    AnalogInput7,
    AnalogInput8,

    // 0x0A4 - Digital Input Status
    ForwardSwitch,
    ReverseSwitch,
    BrakeSwitch,
    RegenDisableSwitch,
    IgnitionSwitch,
    StartSwitch,
    ValetMode,
    DigitalInput8,

    // 0x0A5 - Motor Position Information
    MotorElectricalAngle,
    MotorSpeed,
    InverterFrequency,
    DeltaResolverAngle,

    // 0x0A6 - Current Information
    PhaseACurrent,
    PhaseBCurrent,
    PhaseCCurrent,
    DCBusCurrent
};
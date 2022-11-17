#include <fmt/core.h>

#include <MotorController.hpp>
#include <converters.hpp>
#include <tools.hpp>

void MotorController::newFrame(const can_frame& frame) {
    auto message = can_messages.find(CAN::frameId(frame));
    if (message == messages.end()) return; // Could not find decoding logic for message in the provided DBC

    for (const dbcppp::ISignal& sig : message->Signals()){
        auto signal_dispatch_func = BMS::can_signal_dispatch.find(sig.Name());
        if (signal_dispatch_func == BMS::can_signal_dispatch.end()) continue; // Could not find a signal dispatch function
        emit signal_dispatch_func(sig.RawToPhys(sig.Decode(frame.data))); // Send the data to the front end
    }
}

void MotorController::newError(const can_frame&) {
    fmt::print("Error\n");
};

void MotorController::newTimeout(){};
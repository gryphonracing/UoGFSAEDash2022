#include <fmt/core.h>

#include <BMS.hpp>
#include <tools.hpp>
#include <converters.hpp>

using namespace CAN;

// Will receive data from CANbus here
void BMS::newFrame(const can_frame& frame) {
    auto message = can_messages.find(CAN::frameId(frame));
    if (message == messages.end()) return; // Could not find decoding logic for message in the provided DBC

    for (const dbcppp::ISignal& sig : message->Signals()){
        auto signal_dispatch_func = BMS::can_signal_dispatch.find(sig.Name());
        if (signal_dispatch_func == BMS::can_signal_dispatch.end()) continue; // Could not find a signal dispatch function
        emit signal_dispatch_func(sig.RawToPhys(sig.Decode(frame.data)));
    }
}

// Callback from when the CAN socket receives a CAN frame marked as an error
// Doesn't have to be used, but must be defined
void BMS::newError(const can_frame&) {};

// Callback from when the CAN socket times out
// Doesn't have to be used, but must be defined
void BMS::newTimeout() {};
#include <fmt/core.h>
#include <functional>

#include <BMS.hpp>
#include <tools.hpp>
#include <converters.hpp>

// Callback for when the CAN socket receives a frame
void BMS::newFrame(const can_frame& frame) {
    const auto& message = can_messages.find(CAN::frameId(frame));
    if (message == can_messages.end()) return; // Could not find decoding logic for message in the provided DBC

    for (const dbcppp::ISignal& sig : message->second->Signals()){
        const auto signal_dispatch_func_iter = can_signal_dispatch.find(sig.Name());
        if (signal_dispatch_func_iter == can_signal_dispatch.end()) continue; // Could not find a signal dispatch function
        emit std::invoke(signal_dispatch_func_iter->second, this, sig.RawToPhys(sig.Decode(frame.data))); // Send the data to the front end
    }
}

// Callback for when the CAN socket receives a CAN frame marked as an error
// Doesn't have to be used, but must be defined
void BMS::newError(const can_frame&) {};

// Callback for when the CAN socket times out
// Doesn't have to be used, but must be defined
void BMS::newTimeout() {};
#pragma once

#include <defs.hpp>

namespace CAN {

// Tools for analyzing linux CAN frames
bool isError(const can_frame& frame);
bool isRemoteTransmissionRequest(const can_frame& frame);
CanFormat frameFormat(const can_frame& frame);
canid_t frameId(const can_frame& frame);

} // namespace CAN
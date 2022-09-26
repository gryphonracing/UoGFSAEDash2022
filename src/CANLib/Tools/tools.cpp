#include <cassert>
#include <tools.hpp>

bool CAN::isError(const can_frame& frame) {
    return frame.can_id & CAN_ERR_FLAG;
}

bool CAN::isRemoteTransmissionRequest(const can_frame& frame) {
    return frame.can_id & CAN_RTR_FLAG;
}

CanFormat CAN::frameFormat(const can_frame& frame) {
    if (frame.can_id & CAN_EFF_FLAG) {
        return CanFormat::Extended;
    }
    return CanFormat::Standard;
}

canid_t CAN::frameId(const can_frame& frame) {
    switch (frameFormat(frame)) {
    case CanFormat::Standard:
        return frame.can_id & CAN_SFF_MASK; // 11 LSB
    case CanFormat::Extended:
        return frame.can_id & CAN_EFF_MASK; // 29 LSB
    default:
        break;
    }
    assert(false); // Only 2 formats supported
    return 0;
}
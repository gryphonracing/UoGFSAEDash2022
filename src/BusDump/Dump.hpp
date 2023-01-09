#pragma once

#include <Interface.hpp>

namespace CAN::Interfaces {

class Dump : public Interface {
  public:
    void startReceiving();

  private:
    // As of now, newFrame and newError should be extremely fast functions before emitting more
    // signals
    void newFrame(const can_frame&) override;
    void newError(const can_frame&) override;
    void newTimeout() override;

  private:
    static constexpr uint32_t timeout_ms = 500;
};

} // namespace CAN::Interfaces
#pragma once

#include <Interface.hpp>

namespace CAN::Interfaces {

class ECU2019 : public Interface {
  public:
    ECU2019() = default;
    ~ECU2019() = default;

    void startReceiving();

  private:
    // As of now, newFrame and newError should be extremely fast functions before emitting more
    // signals
    void newFrame(const can_frame&) override;
    void newError(const can_frame&) override;
    void newTimeout() override;

  private:
    static constexpr can_filter filters[] = {
        {
            0x0CFFF048,
            0xFFFFF7FF // Grab all messages from 0CFFF048 to 0CFFF748
        },
        {
            0x0CFFF848,
            0xFFFFFCFF // Grab all messages from 0CFFF848 to 0CFFFB48
        },
        {
            0x0CFFFC48,
            0xFFFFFEFF // Grab all messages from 0CFFFC48 to 0CFFFD48
        },
        {
            0x0CFFFE48,
            0xFFFFFFFF // Grab all messages from 0CFFFE48
        },
        {
            0x0CFFD048,
            0xFFFFFFFF // Grab all messages from 0CFFD048
        }};

    static constexpr uint32_t timeout_ms = 500;
};

} // namespace CAN::Interfaces
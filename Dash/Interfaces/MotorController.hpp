#pragma once

#include <atomic>
#include <cstdint>
#include <thread>
#include <vector>
#include <stdexcept>
#include <future>
#include <memory>
#include <map>
#include <functional>

#include <CANLib/Interface/Interface.hpp>

// https://stackoverflow.com/questions/23454793/whats-the-c-11-way-to-fire-off-an-asynchronous-task-and-forget-about-it
template <class F>
void callAsync(F&& fun) {
    auto fut_ptr = std::make_shared<std::future<void>>();
    *fut_ptr = std::async(std::launch::async, [fut_ptr, fun]() {
        fun();
    });
}


class MotorController : public Interface, public QObject {
    Q_OBJECT
  public:
    MotorController(); 
    ~MotorController() = default;

    void startReceiving();
    void assignCallback(Outputs to_notify_for, std::function<void(float)>);
    void assignCallback(Outputs to_notify_for, std::function<void(bool)>);
    void assignCallback(Outputs to_notify_for, std::function<void(int16_t)>);
    void assignCallback(Outputs to_notify_for, std::function<void(uint16_t)>);

  private:
    // As of now, newFrame and newError should be extremely fast functions before emitting more signals
    void newFrame(const can_frame&) override;
    void newError() override;

  private:
    can_filter m_filters[] = {
        {
            0x0A0, 0xFF0 // Grab all messages from 0xA0 to 0xAF
        },
        {
            0x0B0, 0xFFF // Grab all messages from 0xB0
        }
    };

public:
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
};
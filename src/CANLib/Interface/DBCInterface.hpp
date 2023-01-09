#pragma once

#include <dbcppp/Network.h>

#include <Interface.hpp>
#include <fmt/core.h>
#include <functional>
#include <memory>
#include <tools.hpp>

namespace CAN {

template <class CANNode>
class DBCInterface : public CAN::Interface {
  public:
    DBCInterface(const char* dbc_file)
        : dbc_network(std::move(dbcppp::INetwork::LoadNetworkFromFile(dbc_file)[""])) {
        this->CAN::Interface::startReceiving(
            "can0", CANNode::filters, CANNode::num_of_filters, CANNode::timeout_ms);
        fmt::print("Loaded DBC: {}\n", dbc_file);

        for (const dbcppp::IMessage& msg : dbc_network->Messages()) {
            fmt::print("\tLoaded Message: {}\n", msg.Name());
            can_messages.insert(std::make_pair(msg.Id(), &msg));
            for (const dbcppp::ISignal& sig : msg.Signals()) {
                fmt::print("\t\tLoaded Signal: {} ({})\n", sig.Name(), sig.Unit());
            }
        }
    }
    ~DBCInterface() = default;

  private:
    // As of now, newFrame and newError should be extremely fast functions before emitting more
    // signals
    void newFrame(const can_frame& frame) override {
        const auto& message = can_messages.find(CAN::frameId(frame));
        if (message == can_messages.end())
            return; // Could not find decoding logic for message in the provided DBC

        for (const dbcppp::ISignal& sig : message->second->Signals()) {
            const auto signal_dispatch_func_iter = can_signal_dispatch.find(sig.Name());
            if (signal_dispatch_func_iter == can_signal_dispatch.end())
                continue; // Could not find a signal dispatch function
            std::invoke(signal_dispatch_func_iter->second,
                        dynamic_cast<CANNode*>(this),
                        sig.RawToPhys(sig.Decode(frame.data))); // Send the data to the front end
        }
    }
    void newError(const can_frame&) override {
        fmt::print("Error\n");
    }
    void newTimeout() override{};

  protected:
    std::unique_ptr<dbcppp::INetwork> dbc_network;
    std::unordered_map<uint64_t, const dbcppp::IMessage*> can_messages;
    std::unordered_map<std::string, void (CANNode::*)(float)> can_signal_dispatch;
};

} // namespace CAN
#pragma once

#include <atomic>
#include <thread>

namespace CAN {

class FakeInterface {
  public:
    FakeInterface() = default;
    virtual ~FakeInterface();

    void startReceiving();

  protected:
    void stopReceiving();
    virtual void generateValues() = 0;

  private:
    void readLoop();

  private:
    std::thread m_reading_thread;
    std::atomic<bool> m_should_exit = false;
};

} // namespace CAN
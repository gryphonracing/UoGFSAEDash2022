#include <FakeInterface.hpp>

using namespace CAN;

void FakeInterface::startReceiving() {
    m_reading_thread = std::thread(&FakeInterface::readLoop, this);
}

void FakeInterface::readLoop() {
    while (!this->m_should_exit) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        this->generateValues();
    }
    this->m_should_exit = false;
}

void FakeInterface::stopReceiving() {
    m_should_exit = true;
    if (m_reading_thread.joinable()) {
        m_reading_thread.join();
    }
}

FakeInterface::~FakeInterface() {
    this->stopReceiving();
}
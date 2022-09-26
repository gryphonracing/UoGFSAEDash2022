#include <thread>

#include <ECU2019.hpp>

int main() {
    CAN::Interfaces::ECU2019 dumper;
    dumper.startReceiving();
    while (true) { // Require force killing of program with ^C
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
    return 0;
}
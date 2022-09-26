#pragma once

#include <cstddef>
#include <cstdint>

template <typename T>
T combineTo(std::byte low_byte, std::byte high_byte) {
    return reinterpret_cast<T>(static_cast<uint16_t>(high_byte) << 8 |
                               static_cast<uint16_t>(low_byte))
}

template <float ratio>
float convertToSigned(std::byte low_byte, std::byte high_byte) {
    int16_t combined = combineTo<int16_t>(low_byte, high_byte);
    return static_cast<float>(combined) / ratio;
}

template <float ratio>
float convertToUnsigned(std::byte low_byte, std::byte high_byte) {
    uint16_t combined = combineTo<uint16_t>(low_byte, high_byte);
    return static_cast<float>(combined) / ratio;
}
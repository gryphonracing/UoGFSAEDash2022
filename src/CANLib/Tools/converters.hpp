#pragma once

#include <cstddef>
#include <cstdint>

template <typename T>
T combineTo(uint8_t low_byte, uint8_t high_byte) {
    uint16_t result = (static_cast<uint16_t>(high_byte) << 8) | static_cast<uint16_t>(low_byte);
    return *reinterpret_cast<T*>(&result);
}

template <uint32_t ratio>
float convertToSigned(uint8_t low_byte, uint8_t high_byte) {
    int16_t combined = combineTo<int16_t>(low_byte, high_byte);
    return static_cast<float>(combined) / ratio;
}

template <uint32_t ratio>
float convertToUnsigned(uint8_t low_byte, uint8_t high_byte) {
    uint16_t combined = combineTo<uint16_t>(low_byte, high_byte);
    return static_cast<float>(combined) / ratio;
}
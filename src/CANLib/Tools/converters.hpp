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

float toCelsius(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toLowVoltage(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<100>(low_byte, high_byte);
}

float toNm(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toHighVoltage(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toAmps(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toDegrees(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

int16_t toRPM(std::byte low_byte, std::byte high_byte) {
    return combineTo<int16_t>(low_byte, high_byte);
}

bool toBool(std::byte byte) {
    return static_cast<bool>(byte);
}

float toHz(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float tokW(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toWebers(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<1000>(low_byte, high_byte);
}

// either 100 or 10000 scale
float toProportionalGain1(std::byte low_byte, std::byte high_byte) {
    return convertToUnsigned<100>(low_byte, high_byte);
}
float toProportionalGain2(std::byte low_byte, std::byte high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

float toIntegralGain(std::byte low_byte, std::byte high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

float toDerivativeGain(std::byte low_byte, std::byte high_byte) {
    return convertToUnsigned<100>(low_byte, high_byte);
}

float toLowpassFilterGain(std::byte low_byte, std::byte high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

uint16_t toCount(std::byte low_byte, std::byte high_byte) {
    return combineTo<uint16_t>(low_byte, high_byte);
}

float toPSI(std::byte low_byte, std::byte high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

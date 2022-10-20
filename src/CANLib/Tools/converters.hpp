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

float toCelsius(uint8_t low_byte, uint8_t high_byte);
float toLowVoltage(uint8_t low_byte, uint8_t high_byte);
float toNm(uint8_t low_byte, uint8_t high_byte);
float toHighVoltage(uint8_t low_byte, uint8_t high_byte);
float toAmps(uint8_t low_byte, uint8_t high_byte);
float toDegrees(uint8_t low_byte, uint8_t high_byte);
int16_t toRPM(uint8_t low_byte, uint8_t high_byte);
bool toBool(uint8_t byte);
float toHz(uint8_t low_byte, uint8_t high_byte);
float tokW(uint8_t low_byte, uint8_t high_byte);
float toWebers(uint8_t low_byte, uint8_t high_byte);

// either 100 or 10000 scale
float toProportionalGain100(uint8_t low_byte, uint8_t high_byte);
float toProportionalGain10000(uint8_t low_byte, uint8_t high_byte);
float toIntegralGain(uint8_t low_byte, uint8_t high_byte);
float toDerivativeGain(uint8_t low_byte, uint8_t high_byte);
float toLowpassFilterGain(uint8_t low_byte, uint8_t high_byte);
uint16_t toCount(uint8_t low_byte, uint8_t high_byte);
float toPSI(uint8_t low_byte, uint8_t high_byte);
float toVoltage (uint8_t low_byte, uint8_t high_byte);
float toStateOfCharge (uint8_t low_byte, uint8_t high_byte);
float toCurrent (uint8_t low_byte, uint8_t high_byte);
float toTemperature (uint8_t low_byte, uint8_t high_byte);
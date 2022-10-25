#include <converters.hpp>

float toCelsius(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toLowVoltage(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<100>(low_byte, high_byte);
}

float toNm(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toHighVoltage(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toAmps(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toDegrees(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

int16_t toRPM(uint8_t low_byte, uint8_t high_byte) {
    return combineTo<int16_t>(low_byte, high_byte);
}

bool toBool(uint8_t byte) {
    return static_cast<bool>(byte);
}

float toHz(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float tokW(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

float toWebers(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<1000>(low_byte, high_byte);
}

// either 100 or 10000 scale
float toProportionalGain1(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<100>(low_byte, high_byte);
}
float toProportionalGain2(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

float toIntegralGain(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

float toDerivativeGain(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<100>(low_byte, high_byte);
}

float toLowpassFilterGain(uint8_t low_byte, uint8_t high_byte) {
    return convertToUnsigned<10000>(low_byte, high_byte);
}

uint16_t toCount(uint8_t low_byte, uint8_t high_byte) {
    return combineTo<uint16_t>(low_byte, high_byte);
}

float toPSI(uint8_t low_byte, uint8_t high_byte) {
    return convertToSigned<10>(low_byte, high_byte);
}

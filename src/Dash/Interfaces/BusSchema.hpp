#pragma once

#include <cstdint>

namespace CAN {
    // https://app.box.com/s/vf9259qlaadhzxqiqrt5cco8xpsn84hk/file/27334613044 pg 15 & 16
    namespace MotorController {
        template<typename T>
        T combineTo(byte low_byte, byte high_byte){
            return reinterpret_cast<T>(static_cast<uint16_t>(high_byte) << 8 | static_cast<uint16_t>(low_byte))
        }
        
        template<float ratio>
        float convertToSigned(byte low_byte, byte high_byte){
            int16_t combined = combineTo<int16_t>(low_byte, high_byte);
            return static_cast<float>(combined)/ratio;
        }

        template<float ratio>
        float convertToUnsigned(byte low_byte, byte high_byte){
            uint16_t combined = combineTo<uint16_t>(low_byte, high_byte);
            return static_cast<float>(combined)/ratio;
        }


        float toCelsius(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        float toLowVoltage(byte low_byte, byte high_byte){
            return convertToSigned<100>(low_byte, high_byte);
        }

        float toNm(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        float toHighVoltage(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        float toAmps(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        float toDegrees(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        int16_t toRPM(byte low_byte, byte high_byte){
            return combineTo<int16_t>(low_byte, high_byte);
        }

        bool toBool(byte low_byte, byte high_byte){
            return combineTo<bool>(low_byte, high_byte);
        }

        float toHz(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        float tokW(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }

        float toWebers(byte low_byte, byte high_byte){
            return convertToSigned<1000>(low_byte, high_byte);
        }

        // either 100 or 10000 scale
        float toProportionalGain1(byte low_byte, byte high_byte){
            return convertToUnsigned<100>(low_byte, high_byte);
        }
        float toProportionalGain2(byte low_byte, byte high_byte){
            return convertToUnsigned<10000>(low_byte, high_byte);
        }

        float toIntegralGain(byte low_byte, byte high_byte){
            return convertToUnsigned<10000>(low_byte, high_byte);
        }

        float toDerivativeGain(byte low_byte, byte high_byte){
            return convertToUnsigned<100>(low_byte, high_byte);
        }
        
        float toLowpassFilterGain(byte low_byte, byte high_byte){
            return convertToUnsigned<10000>(low_byte, high_byte);
        }

        uint16_t toCount(byte low_byte, byte high_byte){
            return combineTo<uint16_t>(low_byte, high_byte);
        }

        float toPSI(byte low_byte, byte high_byte){
            return convertToSigned<10>(low_byte, high_byte);
        }
    }
}
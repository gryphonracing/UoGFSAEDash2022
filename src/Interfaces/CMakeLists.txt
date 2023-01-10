if (NOT ${BUILD_FRONTEND})
    return()
endif()

add_library(CANInterfaces)
if (${BUILD_BACKEND})
    target_sources(CANInterfaces PUBLIC
        Full/MotorController.hpp
        Full/EnergyMeter.hpp
        Full/AN400ECU.hpp
        Full/BMS.hpp
    )
    target_include_directories(CANInterfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Full)
    target_link_libraries(CANInterfaces PUBLIC CANLib dbcppp::dbcppp)
else()
    target_sources(CANInterfaces PUBLIC
        Frontend/FakeInterface.hpp
        Frontend/FakeInterface.cpp
        Frontend/MotorController.hpp
        Frontend/MotorController.cpp
        Frontend/EnergyMeter.cpp
        Frontend/EnergyMeter.hpp
        Frontend/BMS.hpp
        Frontend/BMS.cpp
    ) # Currently no fake interfaces
    target_include_directories(CANInterfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Frontend)
endif()
set_target_properties(CANInterfaces PROPERTIES AUTOUIC ON AUTOMOC ON AUTORCC ON)
set_target_properties(CANInterfaces PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>)
target_include_directories(CANInterfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CANInterfaces PUBLIC qt::qt fmt::fmt)
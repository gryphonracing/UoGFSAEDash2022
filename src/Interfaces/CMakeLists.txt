add_library(CANInterfaces)

if (${BUILD_FRONTEND})
    if (${BUILD_BACKEND})
        target_sources(CANInterfaces PUBLIC
            Full/MotorController.hpp
            Full/MotorController.cpp
        )
        target_include_directories(CANInterfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Full)
    else()
        target_sources(CANInterfaces PUBLIC
            Frontend/MotorController.hpp
            Frontend/MotorController.cpp
        ) # Currently no fake interfaces
        target_include_directories(CANInterfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Frontend)
    endif()
    target_link_libraries(CANInterfaces PRIVATE qt::qt)
endif()

if (${BUILD_BACKEND})
    target_sources(CANInterfaces PUBLIC
        Backend/Dump.cpp
        Backend/Dump.hpp
        Backend/ECU2019.cpp
        Backend/ECU2019.hpp
    )
    target_include_directories(CANInterfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Backend)
endif()

set_target_properties(CANInterfaces PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>)

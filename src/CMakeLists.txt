add_subdirectory(Interfaces)

if (${BUILD_BACKEND})
    add_subdirectory(CANLib)
    add_subdirectory(BusDump)
    add_subdirectory(Testing2019)
endif()

if (${BUILD_FRONTEND})
    add_subdirectory(RuntimeQml)
    add_subdirectory(Dash)
endif()

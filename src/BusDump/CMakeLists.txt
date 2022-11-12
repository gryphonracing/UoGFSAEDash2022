set(CODE_FILES
    BusDump.cpp
)

set(HEADER_FILES
)

add_executable(BusDump ${CODE_FILES} ${HEADER_FILES})
set_target_properties(BusDump PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>)
target_link_libraries(BusDump PRIVATE fmt::fmt Threads::Threads CANInterfaces)
target_include_directories(BusDump PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
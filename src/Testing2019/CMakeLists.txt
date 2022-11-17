set(CODE_FILES
    Dump2019.cpp
    ECU2019.cpp
)

set(HEADER_FILES
    ECU2019.hpp
)

add_executable(Dump2019 ${CODE_FILES} ${HEADER_FILES})
set_target_properties(Dump2019 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>)
target_link_libraries(Dump2019 PRIVATE fmt::fmt Threads::Threads CANLib)
target_include_directories(Dump2019 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
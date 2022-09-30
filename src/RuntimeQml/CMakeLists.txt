# https://github.com/GIPdA/runtimeqml

set(CODE_FILES
    RuntimeQml.cpp
)

set(HEADER_FILES
    RuntimeQml.hpp
)

add_library(RuntimeQml ${CODE_FILES} ${HEADER_FILES})
target_link_libraries(RuntimeQml PRIVATE qt::qt)
set_target_properties(RuntimeQml PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>)
target_include_directories(RuntimeQml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
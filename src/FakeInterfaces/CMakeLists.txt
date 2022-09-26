set(CODE_FILES
    MotorController.cpp
)

set(HEADER_FILES
    MotorController.hpp
)

add_library(CarCanInterfaces ${CODE_FILES} ${HEADER_FILES})
set_target_properties(CarCanInterfaces PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>)
target_include_directories(CarCanInterfaces PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
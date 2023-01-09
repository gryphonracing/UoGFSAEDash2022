add_executable(GryphonDash main.cpp qml.qrc)
add_executable(GryphonDash2019 Dash2019.cpp qml.qrc)
set_target_properties(GryphonDash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/2022/$<0:>)
set_target_properties(GryphonDash2019 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/2019/$<0:>)
set_target_properties(GryphonDash PROPERTIES AUTOUIC ON AUTOMOC ON AUTORCC ON)
set_target_properties(GryphonDash2019 PROPERTIES AUTOUIC ON AUTOMOC ON AUTORCC ON)
target_compile_definitions(GryphonDash PRIVATE ROOT_SOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(GryphonDash2019 PRIVATE ROOT_SOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(GryphonDash PRIVATE fmt::fmt qt::qt runtimeqml::runtimeqml CANInterfaces)
target_link_libraries(GryphonDash2019 PRIVATE fmt::fmt qt::qt runtimeqml::runtimeqml CANInterfaces)

# TODO: Add the deployment for linux
if(WIN32)
    set(windeployqt "${QT_BIN_PATH}/windeployqt.exe")
    message(STATUS ${windeployqt})

    add_custom_command(
        TARGET GryphonDash POST_BUILD
        COMMAND "${windeployqt};--qmldir;${CMAKE_CURRENT_SOURCE_DIR};$<TARGET_FILE_DIR:GryphonDash>"
        COMMAND_EXPAND_LISTS)
        
    add_custom_command(
        TARGET GryphonDash2019 POST_BUILD
        COMMAND "${windeployqt};--qmldir;${CMAKE_CURRENT_SOURCE_DIR};$<TARGET_FILE_DIR:GryphonDash>"
        COMMAND_EXPAND_LISTS)
elseif(UNIX AND NOT APPLE)
    message(STATUS "No deployment for Linux, implement.")
elseif(APPLE)
    message(STATUS "No deployment for Apple, implement.")
else()
    message(STATUS "No deployment for unknown platform, implement.")
endif()
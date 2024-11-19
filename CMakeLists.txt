cmake_minimum_required(VERSION 3.10)
project(lowkey)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(lowkey ${SRC_DIR}/main.cpp)

find_package(Boost QUIET REQUIRED COMPONENTS program_options)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()

target_link_libraries(lowkey PUBLIC Boost::program_options)

install(TARGETS lowkey
    RUNTIME DESTINATION /usr/bin
)


install(
    FILES ${SRC_DIR}/battery-monitor.service
    DESTINATION /etc/systemd/user
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
)

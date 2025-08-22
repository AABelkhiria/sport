cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(sport)

set(SERVICES_DIR ${CMAKE_CURRENT_LIST_DIR}/../services)

target_sources(app PRIVATE
    src/main.c
    ${SERVICES_DIR}/ble/src/ble.c
)


target_include_directories(app PRIVATE
    ${SERVICES_DIR}/ble/include
)
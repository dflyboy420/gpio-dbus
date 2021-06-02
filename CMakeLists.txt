cmake_minimum_required (VERSION 3.10)
project (gpio-dbus)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-std=c++1y -g -pthread")
include_directories(include)
include_directories(/usr/include/dbus-1.0)
include_directories(/usr/lib/arm-linux-gnueabihf/dbus-1.0/include)
include_directories(/usr/lib/x86_64-linux-gnu/dbus-1.0/include)

list(APPEND EXTRA_LIBS dbus-1)

add_executable(button button.cpp)
